#include <iostream>

#include "Camera.h"

#include <GLFW/glfw3.h>

Camera* cam;

void mouse_callback(GLFWwindow* window, double xpos, double ypos);

Camera::Camera()
{

	cam = this;
	view = glm::mat4(1.0f);
	view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

	proj = glm::perspective(glm::radians(45.0f), 640.0f / 480.0f, 0.1f, 1000.0f);

	cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
	cameraDirection = glm::normalize(cameraPos - cameraTarget);

	up = glm::vec3(0.0f, 1.0f, 0.0f);
	cameraRight = glm::normalize(glm::cross(up, cameraDirection));
	cameraUp = glm::cross(cameraDirection, cameraRight);

	cameraPos = glm::vec3(0.0f, 0.0f, 9.0f);

	glm::vec3 front;
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	cameraFront = glm::normalize(front);

	cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
}

void Camera::UpdateCamera()
{
	view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
}

void Camera::ProcessInput(GLFWwindow* window, float dt)
{
	glfwSetCursorPosCallback(window, mouse_callback);
	glm::vec3 right = cross(cameraFront, cameraUp);
	float cameraSpeed = 200.0f;
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
		cameraPos += cameraSpeed * cameraFront * dt;
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
		cameraPos -= cameraSpeed * cameraFront * dt;
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
		cameraPos -= cameraSpeed * right * dt;
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		cameraPos += cameraSpeed * right * dt;
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
		cameraPos -= cameraUp * cameraSpeed * dt;
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
		cameraPos += cameraUp * cameraSpeed * dt;

	glm::vec3 front;
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	cameraFront = glm::normalize(front);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (cam->bMouseFirst)
	{
		cam->lastX = xpos;
		cam->lastY = ypos;
		cam->bMouseFirst = false;
	}
	float xoffset = xpos - cam->lastX;
	float yoffset = cam->lastY - ypos;
	cam->lastX = xpos;
	cam->lastY = ypos;

	float sensitivity = 0.15f;
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	cam->yaw += xoffset;
	cam->pitch += yoffset;
	if (cam->pitch > 89.0f)
		cam->pitch = 89.0f;
	if (cam->pitch < -89.0f)
		cam->pitch = -89.0f;

	cam->yaw = std::fmod((cam->yaw + xoffset), (GLfloat)360.0f);
}