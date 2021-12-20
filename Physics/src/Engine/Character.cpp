#include "Character.h"

void Character::TakeDamage(const int damage)
{
	health -= damage;
	if (health <= 0)
	{
		Destroy();
	}
}