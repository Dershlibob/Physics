#include "BigEnemy.h"
#include "Game/Weapons/Basic.h"

void BigEnemy::Start()
{
	weapon = new BasicWeapon(this);
	SetModel("cube");
	health = 6;
	LinearScale(4.0f);
	InitBT();
}