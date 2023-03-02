#include <string>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <vector>
#include <glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtx/matrix_decompose.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <fstream>
#include <string>

class SingleCube {
public:
	std::string name;
	int colors[6];

	SingleCube(std::string name, int colors[], int x, int y, int z);
	std::vector<float> vertices;
	std::vector<float> getVertices();
	glm::mat4 model;
	
	// green, blue, white, yellow, red, orange
	glm::vec3 static_colors[7] = {
		glm::vec3(0.0f, 1.0f, 0.0f),
		glm::vec3(0.0f, 0.0f, 1.0f),
		glm::vec3(1.0f, 1.0f, 1.0f),
		glm::vec3(1.0f, 1.0f, 0.0f),
		glm::vec3(1.0f, 0.0f, 0.0f),
		glm::vec3(1.0f, 0.6f, 0.0f),
		glm::vec3(0.0f, 0.0f, 0.0f)
	};
};

class Cube {
public:
	// order is front back top bottom right left
	// each slice starts at the bottom left and goes across then up.
	int slicesFrontToBack[3][9] = { {0,1,2,3,4,5,6,7,8}, {9, 10,11,12,13,14,15,16,17}, {18,19,20,21,22,23,24,25,26}};
	int slicesRightToLeft[3][9] = { {2,11,20,5,14,23,8,17,26}, {1,10,19,4,13,22,7,16,25}, {0,9,18,3,12,21,6,15,24}};
	int slicesTopToBottom[3][9] = { {6,7,8,15,16,17,24,25,26}, {3,4,5,12,13,14,21,22,23}, {0,1,2,9,10,11,18,19,20}};
	bool animating = false;
	bool shuffling = false;
	std::vector<SingleCube> cubes;
	std::vector<glm::mat4> models;
	std::vector<float> getVertices();
	Cube();

	// 0 up, 1 down, 2 right, 3 left
	void rotateSide(int sliceDir, int slice, int direction);
	void snapRotations();
	bool isSolved();
	void save(std::string filename);
	void load(std::string filename);
	void rotate_face(float angle, float& currentAngle, bool& justStarted, int face, int swipeDir, int& direction, int& sliceDir, int& slice, glm::vec2 intersection, float normalizedYaw);
	void shuffle_rotate_face(int sliceDir, int slice, int direction, float speed, float& currentAngle, bool& justStarted);
private:
	void addSmallCube(std::string name, int color[], int x, int y, int z);
};