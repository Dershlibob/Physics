#pragma once
#include "Bullet.h"

#include "Engine/ModelManager.h"

class BigBullet : public Bullet
{
public:
	float acceleration = 20.0f;
	void Start() override
	{
		SetModel(ModelManager::GetModel("sphere"));
		LinearScale(0.8f);
		lifeTime = 2.5f;
		speed = 0.0f;
		damage = 4;
	}
	void Trajectory(float dt) override
	{
		speed += acceleration * dt;
		position -= direction * speed * dt;
	}
};
