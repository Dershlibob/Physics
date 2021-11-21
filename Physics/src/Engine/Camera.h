#pragma once

#include "glm.hpp"
#include "gtc\matrix_transform.hpp"

struct GLFWwindow;

class Camera
{
public:
	glm::mat4 view;
	glm::mat4 proj;

	glm::vec3 cameraPos;
	glm::vec3 cameraUp;
	glm::vec3 cameraFront;

	glm::vec3 cameraTarget;
	glm::vec3 cameraDirection;

	glm::vec3 up;
	glm::vec3 cameraRight;

	Camera();
	
	void UpdateCamera();
	void ProcessInput(GLFWwindow* window, float dt);

	float yaw = 90.0f;
	float pitch = -89.0f;
	float lastX = 0.0f, lastY = 0.0f;
	bool bMouseFirst = true;

private:

};