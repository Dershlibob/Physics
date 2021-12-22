#pragma once
#include "Bullet.h"

#include "Engine/ModelManager.h"

class SmallBullet : public Bullet
{
public:
	void Start() override
	{
		SetModel(ModelManager::GetModel("sphere"));
		LinearScale(0.3f);
		damage = 1;
	}
};