#pragma once
#include "Entity.h"

class Character : public Entity
{
public:
	glm::vec3 velocity;
	float acceleration = 15.0f;
	float maxSpeed = 18.0f;
	float rotationSpeed = 180.0f;
	int health = 100;

	void TakeDamage(const int damage);
};