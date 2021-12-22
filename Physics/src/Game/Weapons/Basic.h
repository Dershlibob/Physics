#pragma once
#include "Weapon.h"

#include "Engine/Scene.h"

#include "Projectiles/SmallBullet.h"

struct BasicWeapon : public Weapon
{
	BasicWeapon(Entity* _parent) :
		Weapon(_parent)
	{
		SetFireMode(new AutomaticMode());
	}
	bool bSwitch = false;

	Entity* Shoot() override
	{
		SmallBullet* e = (SmallBullet*)Scene::Instantiate(SmallBullet()).get();
		e->position = parent->position;
		e->direction = parent->front;
		if (bSwitch)
		{
			e->position = parent->position - parent->front + (parent->right / 2.0f);
		}
		else
		{
			e->position = parent->position - parent->front - (parent->right / 2.0f);
		}
		bSwitch = !bSwitch;
		return e;
	}
};