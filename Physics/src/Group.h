#pragma once
#include <vector>

#include "glm.hpp"

class Enemy;

struct Group
{
	Group(glm::vec3 position, float area, int size);

	glm::vec3 groupPos;
	float spawnArea = 0;
	int groupSize = 0;

	int entitiesSpawned = 0;
	float nextEntitySpawnTime = 0.0f;

	std::vector<Enemy*> enemies;
};