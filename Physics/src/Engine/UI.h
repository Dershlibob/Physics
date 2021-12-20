#pragma once
#include <vector>

#include "glm.hpp"

#include "Window.h"

using namespace std;

class Shader;
class Texture;
class Camera;

struct Vertex
{
	glm::vec3 position;
	glm::vec2 texCoord;
};

class UI
{
public:
	Camera* cam;
	Shader* shader;
	Texture* texture;
	float width, height;

	glm::mat4 model;

	glm::vec3 position;
	glm::mat4 rotation;
	glm::mat4 scale;

	std::vector<UI*> components;
	UI* parent = nullptr;

	int layer = 0;

	UI(Shader*, Texture* texture, float, float, glm::vec3);
	void DrawUI();
	void AddUI(Shader*, Texture* texture, float x, float y, glm::vec3);
	void RemoveUI(int index);
	void SS_to_NDC(); // Screen Space to Normalized Device Coordinates
private:
	bool bIs3D = false;
	std::vector<Vertex> vertices;
	unsigned int indices[6] = { 0, 1, 2, 1, 3, 2 };
	unsigned int va, vb, ib;
};