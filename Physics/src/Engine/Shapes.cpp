#include <GL/glew.h>
#include "Shapes.h"
#include <iostream>

Shape::Shape(shapes shape, Shader* shader, Camera* cam):
shape(shape),
shader(shader),
cam(cam)
{
	if (shape == shapes::CUBE)
	{
		vertices = CubeVertices;
		indices = CubeIndices;
	}
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ibo);

	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float) , &vertices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
}

void Shape::Draw(float dt)
{
	angle = std::fmod(angle + 3.14 * dt, (GLfloat)360);
	model = glm::translate(glm::mat4(1.0f), position);
	model = glm::rotate(model, angle, glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::scale(model, scale);

	mvp = cam->proj * cam->view * model;
	glBindVertexArray(vao);

	shader->Bind();
	shader->setMat4("u_Model", model);
	shader->setMat4("u_View", cam->view);
	shader->setMat4("u_Projection", cam->proj);

	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}