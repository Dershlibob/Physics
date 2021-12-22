#include "BasicEnemy.h"
#include "Game/Weapons/Basic.h"

void BasicEnemy::Start()
{
	weapon = new BasicWeapon(this);
	SetModel("cube");
	health = 2;
	tag = "Enemy";

	InitBT();
}