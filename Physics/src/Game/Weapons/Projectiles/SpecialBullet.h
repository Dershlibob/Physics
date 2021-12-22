#pragma once
#include "Bullet.h"
#include <math.h>
#include "Engine/ModelManager.h"

class SpecialBullet : public Bullet
{
	glm::vec3 right;
	glm::vec3 prePosition;
public:
	bool bNegative = false;

	void Start() override
	{
		SetModel(ModelManager::GetModel("sphere"));
		LinearScale(0.3f);
		lifeTime = 0.6f;
		damage = 1;
		right = glm::cross(direction, glm::vec3(0.0f, 1.0f, 0.0f));
		prePosition = position;
	}

	void Trajectory(float dt) override
	{
		glm::vec3 osc;
		if (bNegative)
		{
			osc = right * sin(((float)glfwGetTime() - spawnTime) / -0.2f) * 3.0f;
		}
		else
		{
			osc = right * sin(((float)glfwGetTime() - spawnTime) / 0.2f) * 3.0f;
		}

		prePosition -= direction * speed * dt;
		position = osc + prePosition;
	}
};