#include "BigEnemy.h"
#include "Weapons/Basic.h"

void BigEnemy::Start()
{
	weapon = new BasicWeapon(this);
	SetModel("cube");
	health = 10;
	LinearScale(2.0f);
	
	InitBT();
}