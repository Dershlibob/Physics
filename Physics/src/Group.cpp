#include "Group.h"

#include "GLFW/glfw3.h"

#include "Enemy.h"
#include "Bullet.h"

static float random(float min, float max)
{
	return (min + static_cast <float> (rand()) /
		(static_cast <float> (RAND_MAX / (max - min))));
}

Group::Group(glm::vec3 groupPosition, float spawnArea, int groupSize) :
	groupPos(groupPosition),
	spawnArea(spawnArea),
	groupSize(groupSize)
{}

void Group::Idle()
{
	for (int i = 0; i < enemies.size(); ++i)
	{
		Enemy* e = enemies[i].get();
		if (e->state == State::IDLE)
		{
			if (e->bDestinationReached)
			{
				e->destination = glm::normalize(glm::vec3(random(-1.0f, 1.0f), 0.0f, random(-1.0f, 1.0f)));
				e->destination *= random(0.0f, areaRadius);
				e->destination += groupPos;
				e->bDestinationReached = false;
			}
			else
			{
				e->MoveTo(e->destination);
			}
		}
	}
}

void Group::Attacking()
{
	for (int i = 0; i < enemies.size(); ++i)
	{
		Enemy* e = enemies[i].get();
		if (e->state == State::ATTACKING)
		{
			e->ShootCycle();
		}
	}
}

void Group::Spawn(std::shared_ptr<Enemy> e)
{
	enemies.push_back(e);
	SetAreaRadius();
}

void Group::OnEnemyDestroy()
{
	SetAreaRadius();
}
