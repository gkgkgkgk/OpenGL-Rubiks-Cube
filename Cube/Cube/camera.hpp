#include <glm/glm.hpp>

class Camera {
public:
	glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 10.0f);
	glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
	float yaw = 90.0f;
	float pitch = 0.0f;
	float normalizedYaw = (int(yaw) % 360 + 360) % 360;
	float radius = 10.0f;

	Camera();
	void updateCameraPos(float x, float y);
};