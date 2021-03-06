#pragma once

#include "glm.hpp"

#include "Engine/ModelManager.h"
#include "Engine/Scene.h"

#include "Projectiles/Bullet.h"

struct Weapon;

struct IFireMode
{
	Weapon* weapon;
	virtual void FiringMode() = 0;

	float fireTime = 0.0f;
	float fireInterval = 0.2f;
	static float nextShotTime;

	bool bCanFire = true;
};

struct AutomaticMode : public IFireMode
{
	bool bSwitch = true;

	void FiringMode() override;
};

struct SemiautomaticMode : public IFireMode
{
	bool bFired = false;
	void FiringMode() override;
};

struct Weapon
{
private:
	IFireMode* fireMode = nullptr;

public:
	
	Weapon(Entity* _parent);

	Entity* parent;

	void SetFireMode(IFireMode* m)
	{
		delete fireMode;
		fireMode = m;
	}

	IFireMode* GetFireMode()
	{
		return fireMode;
	}

	virtual Entity* Shoot() = 0;
};


