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

	Entity* Shoot() override
	{
		SmallBullet* e = (SmallBullet*)Scene::Instantiate(SmallBullet()).get();
		e->position = parent->position;
		e->direction = parent->front;

		return e;
	}
};