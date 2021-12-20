#pragma once
#include <string>
#include <vector>

#include "glm.hpp"
#include "gtc\matrix_transform.hpp"

#include "Shader.h"

using namespace std;

struct ModelVertex
{
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TexCoords;
};

struct ModelTexture
{
	unsigned int id;
	string type;
	string path;
};

class Mesh
{
public:
	vector<ModelVertex> vertices;
	vector<unsigned int> indices;
	vector<ModelTexture> textures;

	Mesh(vector<ModelVertex> vertices, vector<unsigned int> indices,
		vector<ModelTexture> textures);
	void Draw(Shader& shader);
private:
	unsigned int VAO, VBO, EBO;

	void setupMesh();
};