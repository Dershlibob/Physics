#include "SceneManager.h"

#include <GLFW/glfw3.h>

#include "Engine/Model.h"
#include "Engine/Scene.h"
#include "Engine/ModelManager.h"

#include "Enemy.h"

static float random(float min, float max)
{
	return (min + static_cast <float> (rand()) /
		(static_cast <float> (RAND_MAX / (max - min))));
}

Level::Level()
{
	startTime = glfwGetTime();
}

void SceneManager::Start()
{
	Level level;

	level.groups.push_back(Group(glm::vec3(-25.0f, 0.0f, -10.0f), 20.0f, 5));

	levels.push_back(level);
}

void SceneManager::Update(float dt)
{
	Level* l = &levels[CurrentLevel];
	for (int i = 0; i < l->groups.size(); ++i)
	{
		Group* g = &l->groups[i];
		if (g->entitiesSpawned < g->groupSize)
		{
			if (g->nextEntitySpawnTime + l->startTime < glfwGetTime())
			{
				g->nextEntitySpawnTime += random(0, 2);
				shared_ptr<Enemy> e = Instantiate(Enemy());
				e->SetModel(ModelManager::getModel("cube"));
				e->position.x = random(position.x - g->spawnArea, position.x + g->spawnArea);
				e->position.y = 0.0f;
				e->position.z = random(position.z - g->spawnArea, position.z + g->spawnArea);
				e->yaw = random(0.0f, 360.0f);
				g->enemies.push_back(e);

				++g->entitiesSpawned;
			}
		}
		if (g->enemies.size() > 1)
		{
			for (int j = 0; j < g->enemies.size(); ++j)
			{
				if (g->enemies[j].use_count() == 1)
				{
					g->enemies.erase(g->enemies.begin() + j);
				}
				else
				{
					g->enemies[j]->Flocking(&g->enemies);
				}
			}
		}
	}
}
