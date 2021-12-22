#include "SceneManager.h"

#include <GLFW/glfw3.h>

#include "Engine/Model.h"
#include "Engine/Scene.h"
#include "Engine/ModelManager.h"

#include "Enemies/BasicEnemy.h"
#include "Enemies/BigEnemy.h"

int SceneManager::enemiesKilled = 0;

static float random(float min, float max)
{
	return (min + static_cast <float> (rand()) /
		(static_cast <float> (RAND_MAX / (max - min))));
}

void SceneManager::Start()
{
	std::vector<int> e;
	e.push_back(10);
	e.push_back(0);
	Level level;
	level.AddGroup(Group(glm::vec3(0.0f, 0.0f, 0.0f), 20.0f, e));
	
	levels.push_back(level);
}

void SceneManager::Update(float dt)
{
	Level* l = &levels[CurrentLevel];
	std::vector<Group>* groups = l->getGroups();
	for (int i = 0; i < groups->size(); ++i)
	{
		Group* g = &groups->at(i);
		// Spawns the enemies.
		if (g->entitiesSpawned < l->numOfEnemies)
		{
			if (g->nextEntitySpawnTime + l->startTime < glfwGetTime())
			{
				shared_ptr<Enemy> e;
				int randInt;
				do
				{
					randInt = rand() % 2; // number is based on how many enemies exist.
					if (g->enemyamounts[randInt] > 0)
					{
						if (randInt == 0)
						{
							e = Instantiate(BasicEnemy());
						}
						else if (randInt == 1)
						{
							e = Instantiate(BigEnemy());
						}
					}
				} while (g->enemyamounts[randInt] <= 0);

				g->enemyamounts[randInt]--;

				e->position.x = random(g->groupPos.x - g->spawnArea, g->groupPos.x + g->spawnArea);
				e->position.y = 0.0f;
				e->position.z = random(g->groupPos.z - g->spawnArea, g->groupPos.z + g->spawnArea);
				e->yaw = random(0.0f, 360.0f);

				g->nextEntitySpawnTime += random(0, 2);
				++g->entitiesSpawned;
			}
		}
	}
}
