#include "UI.h"

#include <iostream>

#include <gl/glew.h>

#include "Scene.h"

#include "Shader.h"
#include "Texture.h"
#include "Camera.h"


UI::UI(Shader* _shader, Texture* texture, float x, float y, glm::vec3 pos):
shader(_shader),
texture(texture),
width(x),
height(y),
position(pos)
{
	cam = Scene::getCamera();
	vertices.resize(4);
	vertices[0].texCoord = { 0.0f, 0.0f };
	vertices[1].texCoord = { 1.0f, 0.0f };
	vertices[2].texCoord = { 0.0f, 1.0f };
	vertices[3].texCoord = { 1.0f, 1.0f };
	rotation = glm::mat4(1.0f);
	scale = glm::mat4(1.0f);
	SS_to_NDC();

	glGenVertexArrays(1, &va);
	glGenBuffers(1, &vb);
	glGenBuffers(1, &ib);

	glBindVertexArray(va);

	glBindBuffer(GL_ARRAY_BUFFER, vb);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ib);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoord));

	glBindVertexArray(0);
}

void UI::DrawUI()
{
	texture->Bind();
	shader->Bind();
	shader->setBool("bIs3D", bIs3D);
	glBindVertexArray(va);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
	for (int i = 0; i < components.size(); ++i)
	{
		components[i]->DrawUI();
	}
}

void UI::AddUI(Shader* s, Texture* texture, float x, float y, glm::vec3 pos)
{
	components.push_back(new UI(s, texture, x, y, pos));
	components.back()->parent = this;
	components.back()->layer = this->layer - 1;
}

void UI::RemoveUI(int index)
{
	components.erase(components.begin() + index);
}

void UI::SS_to_NDC()
{
	glm::vec3 pos, p1, p2;
	if (parent)
	{
		pos = position + parent->position;
		pos = position + parent->position;
	}
	else
	{
		pos = position;
		pos = position;
	}

	p1.x = pos.x - (width / 2);
	p2.x = pos.x + (width / 2);
	p1.y = pos.y - (height / 2);
	p2.y = pos.y + (height / 2);

	p1.x = (p1.x / (WIN_WIDTH / 2)) - 1;
	p2.x = (p2.x / (WIN_WIDTH / 2)) - 1;
	p1.y = (p1.y / (WIN_HEIGHT / 2)) - 1;
	p2.y = (p2.y / (WIN_HEIGHT / 2)) - 1;

	vertices[0].position = { p1.x, p1.y, layer };
	vertices[1].position = { p2.x, p1.y, layer };
	vertices[2].position = { p1.x, p2.y, layer };
	vertices[3].position = { p2.x, p2.y, layer };

	glBindVertexArray(va);

	glBindBuffer(GL_ARRAY_BUFFER, vb);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

	for (int i = 0; i < components.size(); ++i)
	{
		components[i]->SS_to_NDC();
	}
}