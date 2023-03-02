#include "camera.hpp"

Camera::Camera() {

}

void Camera::updateCameraPos(float x, float y) {
	float sensitivity = 0.25f;
	float xoffset = x*sensitivity;
	float yoffset = y*sensitivity;

	yaw += xoffset;
	pitch -= yoffset;
	normalizedYaw = (int(yaw) % 360 + 360) % 360;

	// make sure that when pitch is out of bounds, screen doesn't get flipped
	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;

	glm::vec3 target = glm::vec3(0.0f);
	cameraPos.x = target.x + radius * cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	cameraPos.y = target.y + radius * sin(glm::radians(pitch));
	cameraPos.z = target.z + radius * sin(glm::radians(yaw)) * cos(glm::radians(pitch));
}