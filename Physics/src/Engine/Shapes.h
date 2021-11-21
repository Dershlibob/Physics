#pragma once
#include <vector>

#include "glm.hpp"

#include "Shader.h"
#include "Camera.h"

enum class shapes
{
	CUBE
};

class Shape
{
private:
	shapes shape;
	Shader* shader;
	Camera* cam;

public:
	Shape(shapes shape, Shader* shader, Camera* cam);
	void Draw(float dt);

	glm::vec3 scale = { 1.0f, 1.0f, 1.0f };
	float angle = 0.0f;
	glm::mat4 model;
	glm::mat4 mvp;
	std::vector<unsigned int> indices;
	std::vector<float> vertices;
	unsigned int vao, vbo, ibo;

	void SetPosition(glm::vec3 pos) { position = pos; }
	glm::vec3 GetPosition() { return position; }
	Shader* GetShader() { return shader; }
private:
	glm::vec3 position = { 0.0f, 0.0f, 0.0f };

};

static std::vector<float> CubeVertices = {
	// front
	-1.0, -1.0,  1.0,
	 1.0, -1.0,  1.0,
	 1.0,  1.0,  1.0,
	-1.0,  1.0,  1.0,
	// back
	-1.0, -1.0, -1.0,
	 1.0, -1.0, -1.0,
	 1.0,  1.0, -1.0,
	-1.0,  1.0, -1.0
};
static std::vector<unsigned int> CubeIndices = {
	0, 1, 2,
	2, 3, 0,
	// right
	1, 5, 6,
	6, 2, 1,
	// back
	7, 6, 5,
	5, 4, 7,
	// left
	4, 0, 3,
	3, 7, 4,
	// bottom
	4, 5, 1,
	1, 0, 4,
	// top
	3, 2, 6,
	6, 7, 3
}; 