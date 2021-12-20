#pragma once
#include "Weapon.h"

#include "Projectiles/BigBullet.h"

struct ShotgunWeapon : public Weapon
{
	ShotgunWeapon(Entity* _parent) :
		Weapon(_parent)
	{
		SetFireMode(new SemiautomaticMode());
	}

	Entity* Shoot() override
	{
		BigBullet* e = (BigBullet*)Scene::Instantiate(BigBullet()).get();
		e->position = parent->position;
		e->direction = parent->front;

		return e;
	}
};