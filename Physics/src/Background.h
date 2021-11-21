#pragma once
#include <vector>

#include "Engine/Shader.h"
#include "Engine/Camera.h"

class Background
{
private:
	Camera* camera;
	Shader* shader;
	unsigned amount = 0;
	float distance;

public:

	std::vector<float> vertices;
	std::vector<unsigned int> indices;
	std::vector<glm::mat4> modelMatrices;

	Background(Camera* cam, Shader* shader, unsigned amount);
	glm::mat4 mvp;
	void Populate();
	void Draw();
	glm::vec3 scale;

	unsigned int vao, vbo, ibo, vboInstanced;
};

static std::vector<float> CubeVert = {
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

static std::vector<unsigned int> CubeInd = {
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


static std::vector<float> SquareVert = {
	// front
	-1.0, -1.0,  1.0,
	 1.0, -1.0,  1.0,
	 1.0,  1.0,  1.0,
	-1.0,  1.0,  1.0,
};

static std::vector<unsigned int> SquareInd = {
	0, 1, 2,
	2, 3, 0,
};
