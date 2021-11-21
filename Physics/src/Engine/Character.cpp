#include "Character.h"

void Character::TakeDamage(const int damage)
{
	health -= damage;
	cout << tag << " health left: " << health << endl;
	if (health <= 0)
	{
		Destroy();
	}
}