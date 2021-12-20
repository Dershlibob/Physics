#pragma once
#include "Bullet.h"

#include "Engine/ModelManager.h"

class BigBullet : public Bullet
{
public:
	void Start() override
	{
		SetModel(ModelManager::GetModel("sphere"));
		LinearScale(0.8f);
		speed = 25;
		damage = 4;
	}
};
