#include "BasicEnemy.h"
#include "Weapons/Basic.h"

void BasicEnemy::Start()
{
	weapon = new BasicWeapon(this);
	SetModel("cube");
	health = 5;
	tag = "Enemy";

	InitBT();
}