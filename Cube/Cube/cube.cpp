#include "cube.hpp"

// the center of the cube is (0,0,0)
// order: front back top bottom right left
Cube::Cube() {
	int smallCubeCount = 0;
	int sliceCount = 0;
	// add front face
	for (int i = -1; i < 2; i++) {
		for (int j = -1; j < 2; j++) {
			int colors[] = { 0, 6, 6, 6, 6, 6 };
			if (j == -1) {
				colors[5] = 5;
			}

			if (j == 1) {
				colors[4] = 4;
			}

			if (i == 1) {
				colors[2] = 2;
			}

			if (i == -1) {
				colors[3] = 3;
			}

			this->addSmallCube("rtl", colors, j, i, 1);
		}
	}

	sliceCount = 0;
	// middle slice
	for (int i = -1; i < 2; i++) {
		for (int j = -1; j < 2; j++) {
			int colors[] = { 6, 6, 6, 6, 6, 6 };
			if (j == -1) {
				colors[5] = 5;
			}

			if (j == 1) {
				colors[4] = 4;
			}

			if (i == 1) {
				colors[2] = 2;
			}

			if (i == -1) {
				colors[3] = 3;
			}

			this->addSmallCube("rtl", colors, j, i, 0);
		}
	}

	sliceCount = 0;
	// back slice
	for (int i = -1; i < 2; i++) {
		for (int j = -1; j < 2; j++) {
			int colors[] = { 6, 1, 6, 6, 6, 6 };
			if (j == -1) {
				colors[5] = 5;
			}

			if (j == 1) {
				colors[4] = 4;
			}

			if (i == 1) {
				colors[2] = 2;
			}

			if (i == -1) {
				colors[3] = 3;
			}

			this->addSmallCube("rtl", colors, j, i, -1);
		}
	}
}

void Cube::rotateSide(int sliceDir, int slice, int direction) {
	int indexMap[27];
	for (int i = 0; i < 27; i++) {
		indexMap[i] = i;
	}

	// 1 IS CLOCKWISE
	if (sliceDir == 2) {
		if (direction == -1) {
			indexMap[slicesTopToBottom[slice][0]] = slicesTopToBottom[slice][6];
			indexMap[slicesTopToBottom[slice][1]] = slicesTopToBottom[slice][3];
			indexMap[slicesTopToBottom[slice][2]] = slicesTopToBottom[slice][0];
			indexMap[slicesTopToBottom[slice][3]] = slicesTopToBottom[slice][7];
			indexMap[slicesTopToBottom[slice][4]] = slicesTopToBottom[slice][4];
			indexMap[slicesTopToBottom[slice][5]] = slicesTopToBottom[slice][1];
			indexMap[slicesTopToBottom[slice][6]] = slicesTopToBottom[slice][8];
			indexMap[slicesTopToBottom[slice][7]] = slicesTopToBottom[slice][5];
			indexMap[slicesTopToBottom[slice][8]] = slicesTopToBottom[slice][2];
		}
		else if (direction == 1) {
			indexMap[slicesTopToBottom[slice][0]] = slicesTopToBottom[slice][2];
			indexMap[slicesTopToBottom[slice][1]] = slicesTopToBottom[slice][5];
			indexMap[slicesTopToBottom[slice][2]] = slicesTopToBottom[slice][8];
			indexMap[slicesTopToBottom[slice][3]] = slicesTopToBottom[slice][1];
			indexMap[slicesTopToBottom[slice][4]] = slicesTopToBottom[slice][4];
			indexMap[slicesTopToBottom[slice][5]] = slicesTopToBottom[slice][7];
			indexMap[slicesTopToBottom[slice][6]] = slicesTopToBottom[slice][0];
			indexMap[slicesTopToBottom[slice][7]] = slicesTopToBottom[slice][3];
			indexMap[slicesTopToBottom[slice][8]] = slicesTopToBottom[slice][6];
		}
	}
	else if (sliceDir == 3) {
		if (direction == -1) {
			indexMap[slicesRightToLeft[slice][0]] = slicesRightToLeft[slice][6];
			indexMap[slicesRightToLeft[slice][1]] = slicesRightToLeft[slice][3];
			indexMap[slicesRightToLeft[slice][2]] = slicesRightToLeft[slice][0];
			indexMap[slicesRightToLeft[slice][3]] = slicesRightToLeft[slice][7];
			indexMap[slicesRightToLeft[slice][4]] = slicesRightToLeft[slice][4];
			indexMap[slicesRightToLeft[slice][5]] = slicesRightToLeft[slice][1];
			indexMap[slicesRightToLeft[slice][6]] = slicesRightToLeft[slice][8];
			indexMap[slicesRightToLeft[slice][7]] = slicesRightToLeft[slice][5];
			indexMap[slicesRightToLeft[slice][8]] = slicesRightToLeft[slice][2];
		}
		else if (direction == 1) {
			indexMap[slicesRightToLeft[slice][0]] = slicesRightToLeft[slice][2];
			indexMap[slicesRightToLeft[slice][1]] = slicesRightToLeft[slice][5];
			indexMap[slicesRightToLeft[slice][2]] = slicesRightToLeft[slice][8];
			indexMap[slicesRightToLeft[slice][3]] = slicesRightToLeft[slice][1];
			indexMap[slicesRightToLeft[slice][4]] = slicesRightToLeft[slice][4];
			indexMap[slicesRightToLeft[slice][5]] = slicesRightToLeft[slice][7];
			indexMap[slicesRightToLeft[slice][6]] = slicesRightToLeft[slice][0];
			indexMap[slicesRightToLeft[slice][7]] = slicesRightToLeft[slice][3];
			indexMap[slicesRightToLeft[slice][8]] = slicesRightToLeft[slice][6];
		}
	}
	else if (sliceDir == 1) {
		if (direction == -1) {
			indexMap[slicesFrontToBack[slice][0]] = slicesFrontToBack[slice][6];
			indexMap[slicesFrontToBack[slice][1]] = slicesFrontToBack[slice][3];
			indexMap[slicesFrontToBack[slice][2]] = slicesFrontToBack[slice][0];
			indexMap[slicesFrontToBack[slice][3]] = slicesFrontToBack[slice][7];
			indexMap[slicesFrontToBack[slice][4]] = slicesFrontToBack[slice][4];
			indexMap[slicesFrontToBack[slice][5]] = slicesFrontToBack[slice][1];
			indexMap[slicesFrontToBack[slice][6]] = slicesFrontToBack[slice][8];
			indexMap[slicesFrontToBack[slice][7]] = slicesFrontToBack[slice][5];
			indexMap[slicesFrontToBack[slice][8]] = slicesFrontToBack[slice][2];
		}
		else if (direction == 1) {
			indexMap[slicesFrontToBack[slice][0]] = slicesFrontToBack[slice][2];
			indexMap[slicesFrontToBack[slice][1]] = slicesFrontToBack[slice][5];
			indexMap[slicesFrontToBack[slice][2]] = slicesFrontToBack[slice][8];
			indexMap[slicesFrontToBack[slice][3]] = slicesFrontToBack[slice][1];
			indexMap[slicesFrontToBack[slice][4]] = slicesFrontToBack[slice][4];
			indexMap[slicesFrontToBack[slice][5]] = slicesFrontToBack[slice][7];
			indexMap[slicesFrontToBack[slice][6]] = slicesFrontToBack[slice][0];
			indexMap[slicesFrontToBack[slice][7]] = slicesFrontToBack[slice][3];
			indexMap[slicesFrontToBack[slice][8]] = slicesFrontToBack[slice][6];
		}
	}

	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 3; j++) {
			slicesFrontToBack[j][i] = indexMap[slicesFrontToBack[j][i]];
			slicesRightToLeft[j][i] = indexMap[slicesRightToLeft[j][i]];
			slicesTopToBottom[j][i] = indexMap[slicesTopToBottom[j][i]];
		}
	}
}

void Cube::snapRotations() {
	for (int i = 0; i < 27; i++) {
		float angleX, angleY, angleZ;
		glm::extractEulerAngleXYZ(models[i], angleX, angleY, angleZ);
		glm::vec3 eulerAngles = glm::vec3(angleX, angleY, angleZ);
		glm::vec3 rotationAngles = glm::degrees(eulerAngles);

		for (int j = 0; j < 3; j++){
			float angle = rotationAngles[j];
			float positiveAngle = angle + ((angle < 0) ? 360.0f : 0.0f);
			float remainder = fmod(positiveAngle, 90.0f);
			float difference = 0.0f;

			if (remainder < 45.0f)
			{
				difference = -remainder;
			}
			else
			{
				difference = 90.0f - remainder;
			}

			rotationAngles[j] = (int)round(positiveAngle + difference);
		}

		rotationAngles = glm::radians(rotationAngles);
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f));
		glm::vec3 translationVector = glm::vec3((int)round(models[i][3][0]), (int)round(models[i][3][1]), (int)round(models[i][3][2]));
		model = glm::translate(model, translationVector);
		glm::mat4 rotationMatrix = glm::eulerAngleXYZ(rotationAngles.x, rotationAngles.y, rotationAngles.z);
		model = model * rotationMatrix;


		models[i] = model;
	}
}

std::vector<float> Cube::getVertices() {
	std::vector<float> allVertices;
	for (int i = 0; i < 27; i++) {
		SingleCube subcube = cubes[i];
		std::vector<float> subcubeVertices = subcube.getVertices();
		allVertices.insert(allVertices.end(), subcubeVertices.begin(), subcubeVertices.end());
	}

	return allVertices;
}

void Cube::addSmallCube(std::string name, int colors[], int x, int y, int z) {
	glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(x, y, z));
	SingleCube cube = SingleCube(name, colors, x, y, z);
	cubes.push_back(cube);
	models.push_back(model);
}

void Cube::save(std::string filename) {
	std::ofstream file(filename, std::ios::binary);
	if (!file) {
		std::cerr << "Error: Unable to open file for writing: " << filename << std::endl;
		return;
	}

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 9; j++) {
			file << slicesFrontToBack[i][j] << std::endl;
		}
	}

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 9; j++) {
			file << slicesRightToLeft[i][j] << std::endl;
		}
	}

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 9; j++) {
			file << slicesTopToBottom[i][j] << std::endl;
		}
	}

	for (int m = 0; m < 27; m++) {
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				file << models[m][j][i] << std::endl;
			}
		}
	}

	file.close();
}

void Cube::load(std::string filename) {
	std::ifstream file(filename, std::ios::binary);
	if (!file) {
		std::cerr << "Error: Unable to open file for reading: " << filename << std::endl;
	}
	
	std::string line;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 9; j++) {
			std::getline(file, line);
			slicesFrontToBack[i][j] = std::stoi(line);
		}
	}

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 9; j++) {
			std::getline(file, line);
			slicesRightToLeft[i][j] = std::stoi(line);
		}
	}

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 9; j++) {
			std::getline(file, line);
			slicesTopToBottom[i][j] = std::stoi(line);
		}
	}

	for (int m = 0; m < 27; m++) {
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				std::getline(file, line);
				models[m][j][i] = std::stof(line);
			}
		}
	}

	file.close();
}

SingleCube::SingleCube(std::string _name, int _colors[], int x, int y, int z) {
	this->vertices.clear();
	this->name = _name;
	for (int i = 0; i < 6; i++) {
		this->colors[i] = _colors[i];
	}

	this->model = glm::translate(glm::mat4(1.0f), glm::vec3(x, y, z));
	float v[] = {
		// The order is location, color, texture coordinate.
		// Front
		// first triangle
		  0.5f,  0.5f,  0.5f, static_colors[colors[0]][0], static_colors[colors[0]][1], static_colors[colors[0]][2], 1.0f, 1.0f,  // top right
		  0.5f, -0.5f,  0.5f, static_colors[colors[0]][0], static_colors[colors[0]][1], static_colors[colors[0]][2], 1.0f, 0.0f,// bottom right
		  -0.5f,  0.5f,  0.5f, static_colors[colors[0]][0], static_colors[colors[0]][1], static_colors[colors[0]][2], 0.0f, 1.0f,// top left 
		  // second triangle
			0.5f, -0.5f,  0.5f, static_colors[colors[0]][0], static_colors[colors[0]][1], static_colors[colors[0]][2], 1.0f, 0.0f,// bottom right
		   -0.5f, -0.5f,  0.5f, static_colors[colors[0]][0], static_colors[colors[0]][1], static_colors[colors[0]][2], 0.0f, 0.0f,// bottom left
		   -0.5f,   0.5f, 0.5f, static_colors[colors[0]][0], static_colors[colors[0]][1], static_colors[colors[0]][2], 0.0f, 1.0f,// top left

		   // back
			0.5f,   0.5f, -0.5f, static_colors[colors[1]][0], static_colors[colors[1]][1], static_colors[colors[1]][2], 1.0f, 1.0f,  // top right
			0.5f, -0.5f, -0.5f, static_colors[colors[1]][0], static_colors[colors[1]][1], static_colors[colors[1]][2], 1.0f, 0.0f,// bottom right
		   -0.5f,   0.5f, -0.5f, static_colors[colors[1]][0], static_colors[colors[1]][1], static_colors[colors[1]][2], 0.0f, 1.0f,// top left 
		   // second triangle
			0.5f, -0.5f, -0.5f, static_colors[colors[1]][0], static_colors[colors[1]][1], static_colors[colors[1]][2], 1.0f, 0.0f,// bottom right
		   -0.5f, -0.5f, -0.5f, static_colors[colors[1]][0], static_colors[colors[1]][1], static_colors[colors[1]][2], 0.0f, 0.0f,// bottom left
		   -0.5f,   0.5f, -0.5f, static_colors[colors[1]][0], static_colors[colors[1]][1], static_colors[colors[1]][2], 0.0f, 1.0f,// top left

		   // Top
			0.5f,   0.5f, 0.5f, static_colors[colors[2]][0], static_colors[colors[2]][1], static_colors[colors[2]][2], 1.0f, 1.0f,  // top right
			0.5f,  0.5f, -0.5f, static_colors[colors[2]][0], static_colors[colors[2]][1], static_colors[colors[2]][2], 1.0f, 0.0f,// bottom right
		   -0.5f,   0.5f, 0.5f, static_colors[colors[2]][0], static_colors[colors[2]][1], static_colors[colors[2]][2], 0.0f, 1.0f,// top left 
		   // second triangle
			0.5f,  0.5f, -0.5f, static_colors[colors[2]][0], static_colors[colors[2]][1], static_colors[colors[2]][2], 1.0f, 0.0f,// bottom right
		   -0.5f,  0.5f, -0.5f, static_colors[colors[2]][0], static_colors[colors[2]][1], static_colors[colors[2]][2], 0.0f, 0.0f,// bottom left
		   -0.5f,  0.5f, 0.5f, static_colors[colors[2]][0], static_colors[colors[2]][1], static_colors[colors[2]][2], 0.0f, 1.0f,// top left

		   // Bottom
			0.5f,  -0.5f, 0.5f, static_colors[colors[3]][0], static_colors[colors[3]][1], static_colors[colors[3]][2], 1.0f, 1.0f,  // top right
			0.5f, -0.5f, -0.5f, static_colors[colors[3]][0], static_colors[colors[3]][1], static_colors[colors[3]][2], 1.0f, 0.0f,// bottom right
		   -0.5f,  -0.5f, 0.5f, static_colors[colors[3]][0], static_colors[colors[3]][1], static_colors[colors[3]][2], 0.0f, 1.0f,// top left 
		   // second triangle
			 0.5f, -0.5f, -0.5f, static_colors[colors[3]][0], static_colors[colors[3]][1], static_colors[colors[3]][2], 1.0f, 0.0f,// bottom right
		   -0.5f, -0.5f, -0.5f, static_colors[colors[3]][0], static_colors[colors[3]][1], static_colors[colors[3]][2], 0.0f, 0.0f,// bottom left
		   -0.5f, -0.5f, 0.5f, static_colors[colors[3]][0], static_colors[colors[3]][1], static_colors[colors[3]][2], 0.0f, 1.0f,// top left

		   // right
			0.5f,  0.5f, 0.5f, static_colors[colors[4]][0], static_colors[colors[4]][1], static_colors[colors[4]][2], 1.0f, 1.0f,  // top right
			0.5f, -0.5f, 0.5f, static_colors[colors[4]][0], static_colors[colors[4]][1], static_colors[colors[4]][2], 1.0f, 0.0f,// bottom right
			0.5f,  0.5f, -0.5f, static_colors[colors[4]][0], static_colors[colors[4]][1], static_colors[colors[4]][2], 0.0f, 1.0f,// top left 
			// second triangle
			0.5f, -0.5f, 0.5f, static_colors[colors[4]][0], static_colors[colors[4]][1], static_colors[colors[4]][2], 1.0f, 0.0f,// bottom right
			 0.5f, -0.5f, -0.5f, static_colors[colors[4]][0], static_colors[colors[4]][1], static_colors[colors[4]][2], 0.0f, 0.0f,// bottom left
			 0.5f,  0.5f, -0.5f, static_colors[colors[4]][0], static_colors[colors[4]][1], static_colors[colors[4]][2], 0.0f, 1.0f,// top left

			 // left
			 -0.5f,  0.5f, 0.5f, static_colors[colors[5]][0], static_colors[colors[5]][1], static_colors[colors[5]][2], 1.0f, 1.0f,  // top right
			 -0.5f, -0.5f, 0.5f, static_colors[colors[5]][0], static_colors[colors[5]][1], static_colors[colors[5]][2], 1.0f, 0.0f,// bottom right
			 -0.5f,  0.5f, -0.5f, static_colors[colors[5]][0], static_colors[colors[5]][1], static_colors[colors[5]][2], 0.0f, 1.0f,// top left 
			 // second triangle
			 -0.5f, -0.5f, 0.5f, static_colors[colors[5]][0], static_colors[colors[5]][1], static_colors[colors[5]][2], 1.0f, 0.0f,// bottom right
			 -0.5f, -0.5f, -0.5f, static_colors[colors[5]][0], static_colors[colors[5]][1], static_colors[colors[5]][2], 0.0f, 0.0f,// bottom left
			  -0.5f,  0.5f, -0.5f, static_colors[colors[5]][0], static_colors[colors[5]][1], static_colors[colors[5]][2], 0.0f, 1.0f// top left
	};

	unsigned verticesArraySize = sizeof(v) / sizeof(GLfloat);
	vertices.insert(vertices.end(), &(v[0]), &(v[verticesArraySize]));
}

bool Cube::isSolved() {
	int groups[6][9] = { {0,1,2,3,4,5,6,7,8}, {18,19,20,21,22,23,24,25,26}, {2,11,20,5,14,23,8,17,26}, {0,9,18,3,12,21,6,15,24}, {6,7,8,15,16,17,24,25,26}, {0,1,2,9,10,11,18,19,20} };
	int solved[6] = { 0,0,0,0,0,0 };

	for (int i = 0; i < 6; i++) {
		int match_front = 0;
		int match_back = 0;
		int match_top = 0;
		int match_bottom = 0;
		int match_right = 0;
		int match_left = 0;

		for (int j = 0; j < 9; j++) {
			for (int k = 0; k < 9; k++) {
				if (slicesFrontToBack[0][j] == groups[i][k]) {
					match_front++;
				}
				if (slicesFrontToBack[2][j] == groups[i][k]) {
					match_back++;
				}

				if (slicesTopToBottom[0][j] == groups[i][k]) {
					match_top++;
				}
				if (slicesTopToBottom[2][j] == groups[i][k]) {
					match_bottom++;
				}

				if (slicesRightToLeft[0][j] == groups[i][k]) {
					match_right++;
				}
				if (slicesRightToLeft[2][j] == groups[i][k]) {
					match_left++;
				}
			}
		}
		
		if (match_front == 9 || match_back == 9 || match_top == 9 || match_bottom == 9 || match_right == 9 || match_left == 9) {
			solved[i] = 1;
		}

	}

	for (int i = 0; i < 6; i++) {
		if (solved[i] == 0) {
			return false;
		}
	}

	return true;
}

std::vector<float> SingleCube::getVertices() {
	return vertices;
}

void Cube::rotate_face(float angle, float& currentAngle, bool& justStarted, int face, int swipeDir, int& direction, int& sliceDir, int& slice, glm::vec2 intersection, float normalizedYaw) {
	justStarted = false;
	// front back top bottom right left 0 1 2 3 4 5
	// swipedir: 2 up/down 1 right/left
	currentAngle += glm::degrees(angle);

	int index = 0;
	int angle_direction = -1;
	if (face == 0 || face == 1) {
		if (swipeDir == 1) {
			index = 2 - floor(intersection.y + 1.5f);
			for (int i = 0; i < 9; i++) {
				glm::mat4 model = models[slicesTopToBottom[index][i]];
				glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), -angle, glm::vec3(0.0f, 5.0f, 0.0f));
				model = rotation * model;
				models[slicesTopToBottom[index][i]] = model;
			}

			direction = abs(angle) / angle;
			sliceDir = 2;
			slice = index;
		}
		else if (swipeDir == 2) {
			if (face == 1) {
				angle_direction = 1;
			}
			index = 2 - floor(intersection.x + 1.5f);
			for (int i = 0; i < 9; i++) {
				glm::mat4 model = models[slicesRightToLeft[index][i]];
				glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), angle_direction * angle, glm::vec3(5.0f, 0.0f, 0.0f));
				model = rotation * model;
				models[slicesRightToLeft[index][i]] = model;
			}

			direction = abs(angle) / -angle * angle_direction;
			sliceDir = 3;
			slice = index;
		}
	}
	else if (face == 4 || face == 5) {
		if (swipeDir == 1) {
			index = 2 - floor(intersection.y + 1.5f);
			for (int i = 0; i < 9; i++) {
				glm::mat4 model = models[slicesTopToBottom[index][i]];
				glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), -angle, glm::vec3(0.0f, 5.0f, 0.0f));
				model = rotation * model;
				models[slicesTopToBottom[index][i]] = model;
			}

			direction = abs(angle) / angle;
			sliceDir = 2;
			slice = index;
		}
		else if (swipeDir == 2) {
			if (face == 4) {
				angle_direction = 1;
			}
			index = 2 - floor(intersection.x + 1.5f);
			for (int i = 0; i < 9; i++) {
				glm::mat4 model = models[slicesFrontToBack[index][i]];
				glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), angle_direction * angle, glm::vec3(0.0f, 0.0f, 5.0f));
				model = rotation * model;
				models[slicesFrontToBack[index][i]] = model;
			}

			direction = abs(angle) / -angle * angle_direction;
			sliceDir = 1;
			slice = index;
		}
	}
	else if (face == 2 || face == 3) {
		if ((normalizedYaw > 45 && normalizedYaw < 135) || (normalizedYaw > 225 && normalizedYaw < 315)) {
			if (swipeDir == 1) { // DONE
				if ((normalizedYaw > 225 && normalizedYaw < 315)) {
					angle_direction = -1;
				}
				else {
					angle_direction = 1;
				}
				index = 2 - floor(intersection.y + 1.5f);
				for (int i = 0; i < 9; i++) {
					glm::mat4 model = models[slicesFrontToBack[index][i]];
					glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), angle_direction * angle, glm::vec3(0.0f, 0.0f, 5.0f));
					model = rotation * model;
					models[slicesFrontToBack[index][i]] = model;
				}

				direction = abs(angle) / angle * -angle_direction;
				sliceDir = 1;
				slice = index;
			}
			else if (swipeDir == 2) { // DONE
				if ((normalizedYaw > 225 && normalizedYaw < 315)) {
					angle_direction = 1;
				}
				index = 2 - floor(intersection.x + 1.5f);
				for (int i = 0; i < 9; i++) {
					glm::mat4 model = models[slicesRightToLeft[index][i]];
					glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), angle_direction * angle, glm::vec3(5.0f, 0.0f, 0.0f));
					model = rotation * model;
					models[slicesRightToLeft[index][i]] = model;
				}

				direction = abs(angle) / -angle * angle_direction;
				sliceDir = 3;
				slice = index;
			}
		}
		else {
			if (swipeDir == 1) { // DONE
				if ((normalizedYaw > 135 && normalizedYaw < 215)) {
					angle_direction = -1;
				}
				else {
					angle_direction = 1;
				}

				if (face == 3) {
					angle_direction *= -1;
				}

				index = 2 - floor(intersection.x + 1.5f);
				for (int i = 0; i < 9; i++) {
					glm::mat4 model = models[slicesRightToLeft[index][i]];
					glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), angle_direction * angle, glm::vec3(5.0f, 0.0f, 0.0f));
					model = rotation * model;
					models[slicesRightToLeft[index][i]] = model;
				}

				direction = abs(angle) / angle * -angle_direction;
				sliceDir = 3;
				slice = index;
			}
			else if (swipeDir == 2) { // DONE
				if ((normalizedYaw > 135 && normalizedYaw < 215)) {
					angle_direction = -1;
				}
				else {
					angle_direction = 1;
				}

				index = 2 - floor(intersection.y + 1.5f);
				for (int i = 0; i < 9; i++) {
					glm::mat4 model = models[slicesFrontToBack[index][i]];
					glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), angle_direction * angle, glm::vec3(0.0f, 0.0f, 5.0f));
					model = rotation * model;
					models[slicesFrontToBack[index][i]] = model;
				}

				direction = abs(angle) / -angle * angle_direction;
				sliceDir = 1;
				slice = index;
			}
		}
	}
}

void Cube::shuffle_rotate_face(int sliceDir, int slice, int direction, float speed, float& currentAngle, bool& justStarted) {
	justStarted = false;
	currentAngle += glm::degrees(direction * speed);
	if (sliceDir == 1) {
		for (int i = 0; i < 9; i++) {
			glm::mat4 model = models[slicesFrontToBack[slice][i]];
			glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), -direction * speed, glm::vec3(0.0f, 0.0f, 5.0f));
			model = rotation * model;
			models[slicesFrontToBack[slice][i]] = model;
		}
	}
	else if (sliceDir == 2) {
		for (int i = 0; i < 9; i++) {
			glm::mat4 model = models[slicesTopToBottom[slice][i]];
			glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), -direction * speed, glm::vec3(0.0f, 5.0f, 0.0f));
			model = rotation * model;
			models[slicesTopToBottom[slice][i]] = model;
		}
	}
	else if (sliceDir == 3) {
		for (int i = 0; i < 9; i++) {
			glm::mat4 model = models[slicesRightToLeft[slice][i]];
			glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), -direction * speed, glm::vec3(5.0f, 0.0f, 0.0f));
			model = rotation * model;
			models[slicesRightToLeft[slice][i]] = model;
		}
	}
}