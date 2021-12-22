#pragma once

#include "Weapon.h"

#include "Projectiles/SpecialBullet.h"

class SpecialWeapon : public Weapon
{
public:
	SpecialWeapon(Entity* _parent) :
		Weapon(_parent)
	{
		SetFireMode(new AutomaticMode());
	}

	Entity* Shoot() override
	{
		SpecialBullet* e1 = (SpecialBullet*)Scene::Instantiate(SpecialBullet()).get();
		SpecialBullet* e2 = (SpecialBullet*)Scene::Instantiate(SpecialBullet()).get();

		e1->position = parent->position;
		e1->direction = parent->front;
		e1->bNegative = false;
		e1->tag = "AllyBullet";

		e2->position = parent->position;
		e2->direction = parent->front;
		e2->bNegative = true;
		e2->tag = "AllyBullet";

		return e1;
	}
};