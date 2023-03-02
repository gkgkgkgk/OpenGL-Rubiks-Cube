#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <fstream>
#include <string>
#include <iostream>
#include <string>
#include "cube.hpp"
#include "camera.hpp"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
int load_shaders(std::string vertexShaderPath, std::string fragmentShaderPath);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
float intersectTriangle(const glm::vec3& rayOrigin, const glm::vec3& rayDirection,
const glm::vec3& v0, const glm::vec3& v1, const glm::vec3& v2, glm::vec3& intersection);
float checkFace(const glm::vec3& rayOrigin, const glm::vec3& rayDirection, glm::vec3 face[], glm::vec3& intersection);
int determineFaceClick(glm::vec3 mouse3D, glm::vec3 rayDirection, glm::vec2& intersection);
void pick_random_action();
void reset_actions();
double deltaTime = 0.0;
bool firstMouse = true;

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 800;
glm::mat4 projection = glm::mat4(1.0f);
glm::mat4 view = glm::mat4(1.0f);
float lastX = SCR_WIDTH / 2.0;
float lastY = SCR_HEIGHT / 2.0;
bool mouseDown = false;
int swipeDir = 0; // 2 up/down 3 right/left 1 front/back
Cube cube;
Camera camera;

glm::vec2 intersection(0.0f);
int face = 0;
int shuffleAmount = -1;
int userShuffleAmount = 5;
float currentAngle = 0.0f;
int sliceDir = 0;
int slice = 0;
int direction = 0;

bool solved = false;
bool justStarted = true;

int main()
{
	// initialize camera and cube
	cube = Cube();
	camera = Camera();

	// initialize glfw and glew
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Rubiks Cube", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		return -1;
	}

	// load shaders
	int programID = load_shaders("./vert.vertexshader", "./frag.fragmentshader");
	
	glEnable(GL_DEPTH_TEST);

	// get cube vertices, load them into a vbo
	std::vector<float> vertices = cube.getVertices();
	GLsizei _numberOfVertices;
	_numberOfVertices = static_cast<GLsizei>(cube.getVertices().size());
	GLsizeiptr vertexSize = _numberOfVertices * sizeof(GLfloat);

	unsigned int VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);


	// the vbo has 3 positions for a vertex, 3 positions for a color, and 2 positions for a texture coordinate
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertexSize, vertices.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);


	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetMouseButtonCallback(window, mouse_button_callback);
	glfwSetKeyCallback(window, key_callback);

	pick_random_action();

	// initialize UI
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 330 core");
	ImFont* bigFont = ImGui::GetIO().Fonts->AddFontFromFileTTF("Roboto-Bold.ttf", 32.0f);
	ImFont* smallFont = ImGui::GetIO().Fonts->AddFontFromFileTTF("Roboto-Bold.ttf", 18.0f);

	double prevTime = glfwGetTime();
	while (!glfwWindowShouldClose(window))
	{
		double currentTime = glfwGetTime();
		deltaTime = currentTime - prevTime;
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			glfwSetWindowShouldClose(window, true);

		glClearColor(0.25f, 0.25f, 0.25f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		
		glUseProgram(programID);

		projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
		const float radius = 10.0f;

		view = glm::lookAt(camera.cameraPos, glm::vec3(0.0f), camera.cameraUp);
		glm::mat4 model = glm::mat4(1.0f);

		glUniformMatrix4fv(glGetUniformLocation(programID, "projection"), 1, GL_FALSE, &projection[0][0]);
		glUniformMatrix4fv(glGetUniformLocation(programID, "view"), 1, GL_FALSE, &view[0][0]);
		glBindVertexArray(VAO);

		if (shuffleAmount >= 0) { // if the cube still needs to be shuffled
			if (cube.shuffling) { // if the cube is already shuffling
				cube.shuffle_rotate_face(sliceDir, slice, direction, 5.0f * deltaTime, currentAngle, justStarted);  // rotate the face
				if (abs(currentAngle) >= 90.0f) { // if its hit the 90 degree mark, stop shuffling
					cube.shuffling = false;
					reset_actions();
				}
			}
			else {
				cube.shuffling = true;
				currentAngle = 0;
				cube.snapRotations();
				cube.rotateSide(sliceDir, slice, direction);
				solved = cube.isSolved();
				pick_random_action();

				shuffleAmount -= 1;

				if (shuffleAmount < 0) {
					cube.animating = false;
					cube.shuffling = false;
				}
			}
		}
		else if (cube.animating == true) { // if the cube is currently animating, rotate the face. animating happens after the user lets go of a swipe.

			int sign = (currentAngle >= 0 ? 1 : -1);

			if (abs(currentAngle) < 15) {
				sign = -sign;
			}

			cube.rotate_face(sign * 5.0f * deltaTime, currentAngle, justStarted, face, swipeDir, direction, sliceDir, slice, intersection, camera.normalizedYaw);

			if (abs(currentAngle) < 5.0f || abs(currentAngle) >= 90.0f) {
				cube.snapRotations();
				if (abs(currentAngle) >= 90.0f) {
					cube.rotateSide(sliceDir, slice, direction);
				}

				solved = cube.isSolved();

				cube.animating = false;
				currentAngle = 0;
				swipeDir = 0;
			}
		}

		// load each model and draw each subcube
		for (int i = 0; i < 27; i++) {
			glUniformMatrix4fv(glGetUniformLocation(programID, "model"), 1, GL_FALSE, &cube.models[i][0][0]);
			glDrawArrays(GL_TRIANGLES, 36 * i, 36);
		}

		// render ui
		ImGui::SetNextWindowBgAlpha(0.0f);
		ImGui::SetNextWindowPos(ImVec2(0, 0));
		ImGui::SetNextWindowSize(ImVec2(800, 100));
		ImGuiWindowFlags flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoBringToFrontOnFocus;

		ImGui::Begin("Rubiks Cube OpenGL", NULL, flags);
		ImGui::PushFont(smallFont);
		ImGui::Text(("Amount to Shuffle (Use left and right arrow keys to adjust, space to shuffle): " + std::to_string(userShuffleAmount)).c_str());
		ImGui::Text("(Press down to save the cube, and up to upload the last cube.)");
		ImGui::PopFont();


		if (solved && !justStarted) {
			ImGui::PushFont(bigFont);
			ImGui::Text("The cube is solved!");
			ImGui::PopFont();
		}

		ImGui::End();

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		glfwSwapBuffers(window);
		glfwPollEvents();

		prevTime = currentTime;
	}

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwTerminate();
	return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

int load_shaders(std::string vertexShaderPath, std::string fragmentShaderPath) {
	std::string vertexShaderCode;
	std::ifstream vertexShaderStream(vertexShaderPath, std::ios::in);
	if (vertexShaderStream.is_open()) {
		std::string Line = "";
		while (getline(vertexShaderStream, Line))
			vertexShaderCode += "\n" + Line;
		vertexShaderStream.close();
	}
	else {
		std::cout << "Impossible to open " << vertexShaderPath << ".\n";
		return 0;
	}

	char const* vertexShaderSource = vertexShaderCode.c_str();

	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	// check for shader compile errors
	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	// fragment shader
	std::string fragmentShaderCode;
	std::ifstream fragmentShaderStream(fragmentShaderPath, std::ios::in);
	if (fragmentShaderStream.is_open()) {
		std::string Line = "";
		while (getline(fragmentShaderStream, Line))
			fragmentShaderCode += "\n" + Line;
		fragmentShaderStream.close();
	}
	else {
		std::cout << "Impossible to open " << fragmentShaderPath << ".\n";
		return 0;
	}

	char const* fragmentShaderSource = fragmentShaderCode.c_str();

	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	// check for shader compile errors
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	// link shaders
	unsigned int shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	// check for linking errors
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	return shaderProgram;
}

void pick_random_action() {
	slice = (rand() % 2);
	sliceDir = 1 + (rand() % 2);
	direction = rand() % 2;

	if (direction == 0) {
		direction = -1;
	}
}

void reset_actions() {
	int sliceDir = 0;
	int slice = 0;
	int direction = 0;
}

void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
	float xpos = static_cast<float>(xposIn);
	float ypos = static_cast<float>(yposIn);

	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS) // right click for rotating camera
	{
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

		if (firstMouse)
		{
			lastX = xpos;
			lastY = ypos;
			firstMouse = false;
		}

		float xoffset = xpos - lastX;
		float yoffset = lastY - ypos;
		lastX = xpos;
		lastY = ypos;

		camera.updateCameraPos(xoffset, yoffset);
	}
	else if (mouseDown) { // left click for changing the cube
		if (firstMouse)
		{
			lastX = xpos;
			lastY = ypos;
			firstMouse = false;
		}
		float xoffset = xpos - lastX;
		float yoffset = lastY - ypos;
		lastX = xpos;
		lastY = ypos;

		if (swipeDir == 0 && face >= 0) {
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
			if (abs(xoffset) > 10) {
				swipeDir = 1;
			}
			else if (abs(yoffset) > 10) {
				swipeDir = 2;
			}
		}
		else {
			float offset = yoffset;

			if (swipeDir == 1) {
				offset = -xoffset;
			}

			if (abs(currentAngle) <= 90.0f) {
				cube.rotate_face(offset * 0.25f * deltaTime, currentAngle, justStarted, face, swipeDir, direction, sliceDir, slice, intersection, camera.normalizedYaw);
			}
		}
	}
	else {
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		lastX = -1;
		lastY = -1;
		firstMouse = true;
	}
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	if (!cube.shuffling && !cube.animating) {
		if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
		{
			mouseDown = true;

			double xpos, ypos;
			glfwGetCursorPos(window, &xpos, &ypos);

			int width, height;
			glfwGetWindowSize(window, &width, &height);

			glm::vec3 mouse3D = glm::unProject(
				glm::vec3(xpos, height - ypos, 0.0f),
				view,
				projection,
				glm::vec4(0, 0, width, height)
			);

			glm::vec3 rayDir = glm::normalize(mouse3D - camera.cameraPos);
			face = determineFaceClick(mouse3D, rayDir, intersection);
			if (face == -1) {
				swipeDir = 0;
			}
		}

		if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
		{
			mouseDown = false;
			cube.animating = true;
		}
	}
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_LEFT && action == GLFW_PRESS)
	{
		if(userShuffleAmount > 0)
			userShuffleAmount--;
	}
	else if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS)
	{
		userShuffleAmount++;
	}
	else if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
	{
		if (!cube.animating && !cube.shuffling) {
			shuffleAmount = userShuffleAmount;
			cube.shuffling = true;
		}
	}
	else if (key == GLFW_KEY_DOWN && action == GLFW_PRESS)
	{
		if (!cube.animating && !cube.shuffling) {
			cube.save("cube.state");
		}
	}
	else if (key == GLFW_KEY_UP && action == GLFW_PRESS)
	{
		if (!cube.animating && !cube.shuffling) {
			cube.load("cube.state");
		}
	}
}

int determineFaceClick(glm::vec3 mouse3D, glm::vec3 rayDirection, glm::vec2& intersection) {
	// create planes for each face of the cube, and then use them to determine which intersects with the raycast
	glm::vec3 frontFace[] = {
			glm::vec3(1.5f, 1.5f, 1.5f),
			glm::vec3(-1.5f, 1.5f, 1.5f),
			glm::vec3(1.5f, -1.5f, 1.5f),
			glm::vec3(1.5f, -1.5f, 1.5f),
			glm::vec3(-1.5f, 1.5f, 1.5f),
			glm::vec3(-1.5f, -1.5f, 1.5f)
	};

	glm::vec3 backFace[] = {
			glm::vec3(1.5f, 1.5f, -1.5f),
			glm::vec3(-1.5f, 1.5f, -1.5f),
			glm::vec3(1.5f, -1.5f, -1.5f),
			glm::vec3(1.5f, -1.5f, -1.5f),
			glm::vec3(-1.5f, 1.5f, -1.5f),
			glm::vec3(-1.5f, -1.5f, -1.5f)
	};

	glm::vec3 rightFace[] = {
			glm::vec3(1.5f, 1.5f, 1.5f),
			glm::vec3(1.5f, -1.5f, 1.5f),
			glm::vec3(1.5f, -1.5f, -1.5f),
			glm::vec3(1.5f, 1.5f, 1.5f),
			glm::vec3(1.5f, -1.5f, -1.5f),
			glm::vec3(1.5f, 1.5f, -1.5f)
	};

	glm::vec3 leftFace[] = {
			glm::vec3(-1.5f, 1.5f, 1.5f),
			glm::vec3(-1.5f, -1.5f, 1.5f),
			glm::vec3(-1.5f, -1.5f, -1.5f),
			glm::vec3(-1.5f, 1.5f, 1.5f),
			glm::vec3(-1.5f, -1.5f, -1.5f),
			glm::vec3(-1.5f, 1.5f, -1.5f)
	};

	glm::vec3 topFace[] = {
			glm::vec3(-1.5f, 1.5f, -1.5f),
			glm::vec3(-1.5f, 1.5f, 1.5f),
			glm::vec3(1.5f, 1.5f, 1.5f),
			glm::vec3(-1.5f, 1.5f, -1.5f),
			glm::vec3(1.5f, 1.5f, 1.5f),
			glm::vec3(1.5f, 1.5f, -1.5f)
	};

	glm::vec3 bottomFace[] = {
			glm::vec3(-1.5f, -1.5f, -1.5f),
			glm::vec3(-1.5f, -1.5f, 1.5f),
			glm::vec3(1.5f, -1.5f, 1.5f),
			glm::vec3(-1.5f, -1.5f, -1.5f),
			glm::vec3(1.5f, -1.5f, 1.5f),
			glm::vec3(1.5f, -1.5f, -1.5f)
	};
	glm::vec3 intersection3d = glm::vec3(0.0f);
	float intersections[] = {
		checkFace(mouse3D, rayDirection, frontFace, intersection3d),
		checkFace(mouse3D, rayDirection, backFace, intersection3d),
		checkFace(mouse3D, rayDirection, topFace, intersection3d),
		checkFace(mouse3D, rayDirection, bottomFace, intersection3d),
		checkFace(mouse3D, rayDirection, rightFace, intersection3d),
		checkFace(mouse3D, rayDirection, leftFace, intersection3d)
	};

	int size = sizeof(intersections) / sizeof(intersections[0]);

	float minVal = intersections[0];
	int minIndex = 0;

	

	for (int i = 1; i < size; i++) {
		if (intersections[i] < minVal && intersections[i] >= 0.0f) {
			minVal = intersections[i];
			minIndex = i;
		}
	}

	if (minVal >= 100.0f) {
		return -1;
	}

	switch (minIndex) {
	case 0:
		checkFace(mouse3D, rayDirection, frontFace, intersection3d);
		intersection = glm::vec2(intersection3d.x, intersection3d.y);
		break;
	case 1:
		checkFace(mouse3D, rayDirection, backFace, intersection3d);
		intersection = glm::vec2(intersection3d.x, intersection3d.y);
		break;
	case 2:
		checkFace(mouse3D, rayDirection, topFace, intersection3d);
		intersection = glm::vec2(intersection3d.x, intersection3d.z);
		break;
	case 3:
		checkFace(mouse3D, rayDirection, bottomFace, intersection3d);
		intersection = glm::vec2(intersection3d.x, intersection3d.z);
		break;
	case 4:
		checkFace(mouse3D, rayDirection, rightFace, intersection3d);
		intersection = glm::vec2(intersection3d.z, intersection3d.y);
		break;
	case 5:
		checkFace(mouse3D, rayDirection, leftFace, intersection3d);
		intersection = glm::vec2(intersection3d.z, intersection3d.y);
		break;
	}

	 
	return minIndex;
}

float checkFace(const glm::vec3& rayOrigin, const glm::vec3& rayDirection, glm::vec3 face[], glm::vec3& intersection) {
	float t1 = intersectTriangle(rayOrigin, rayDirection, face[0], face[1], face[2], intersection);
	float t2 = intersectTriangle(rayOrigin, rayDirection, face[3], face[4], face[5], intersection);
	
	if (t1 < 0 && t2 < 0) {
		return -1.0f;
	}
	else if (t1 < 0) {
		return t2;
	}
	else if (t2 < 0) {
		return t1;
	}
	else {
		if (t1 < t2) {
			return t1;
		}
		else {
			return t2;
		}
	}
}

// https://en.wikipedia.org/wiki/M%C3%B6ller%E2%80%93Trumbore_intersection_algorithm
// This function returns the distance of the intersection
float intersectTriangle(const glm::vec3& rayOrigin, const glm::vec3& rayDirection,
	const glm::vec3& v0, const glm::vec3& v1, const glm::vec3& v2, glm::vec3 &intersection) {
	const float EPSILON = 0.000001f;
	float t, u, v;
	glm::vec3 edge1, edge2, h, s, q;
	float a, f;

	edge1 = v1 - v0;
	edge2 = v2 - v0;

	h = glm::cross(rayDirection, edge2);
	a = glm::dot(edge1, h);

	if (a > -EPSILON && a < EPSILON) {
		return false;
	}

	f = 1.0f / a;
	s = rayOrigin - v0;
	u = f * glm::dot(s, h);

	if (u < 0.0f || u > 1.0f) {
		return 100.0f;
	}

	q = glm::cross(s, edge1);
	v = f * glm::dot(rayDirection, q);

	if (v < 0.0f || u + v > 1.0f) {
		return 100.0f;
	}

	t = f * glm::dot(edge2, q);

	if (t > EPSILON) {
		float w = 1.0f - u - v;
		intersection = rayOrigin + rayDirection * t;
		return t;
	}

	return 100.0f;
}