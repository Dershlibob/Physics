#include "Background.h"

#include <GL/glew.h>

#include <iostream>

#include <cstdlib>
#include <ctime>

#define PI 3.14159f

static float random(float min, float max)
{
	return (min + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (max - min))));
}

Background::Background(Camera* cam, Shader* shader, unsigned count):
	camera(cam),
	shader(shader),
	amount(count)
{
	vertices = SquareVert;
	indices = SquareInd;
	scale = glm::vec3(1.0f);
	modelMatrices.reserve(amount);
	Populate();

	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ibo);
	glGenBuffers(1, &vboInstanced);

	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	glBindBuffer(GL_ARRAY_BUFFER, vboInstanced);
	glBufferData(GL_ARRAY_BUFFER, amount * sizeof(glm::mat4), &modelMatrices[0], GL_STATIC_DRAW);
	
	std::size_t vec4Size = sizeof(glm::vec4);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void*)0);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void*)(1 * vec4Size));
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void*)(2 * vec4Size));
	glEnableVertexAttribArray(4);
	glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void*)(3 * vec4Size));

	glVertexAttribDivisor(1, 1);
	glVertexAttribDivisor(2, 1);
	glVertexAttribDivisor(3, 1);
	glVertexAttribDivisor(4, 1);

	glBindVertexArray(0);
}

void Background::Populate()
{
	shader->Bind();
	shader->setVec3("u_Colour", glm::vec3(1.0f, 1.0f, 1.0f));

	glm::vec3 offset;

	int multiplier = 1;
	for (int i = 0; i < amount; ++i)
	{
		if (i < amount * 1 / 3)
			multiplier = 1;
		if (i >= amount * 1 / 3 && i < amount * 2 / 3)
			multiplier = 2;
		else if (i >= amount * 2 / 3)
			multiplier = 3;
		offset.x = random(-500, 500);
		offset.y = -4.5 * 5 - (20 * multiplier);
		offset.z = random(-500, 500);
		glm::mat4 model = glm::translate(glm::mat4(1.0f), offset);
		model = glm::rotate(model, -PI / 2, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		modelMatrices.push_back(model);
	}
}

void Background::Draw()
{


	shader->Bind();
	shader->setMat4("u_View", camera->view);
	shader->setMat4("u_Projection", camera->proj);

	glBindVertexArray(vao);
	glDrawElementsInstanced(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0, amount);
	glBindVertexArray(0);
}