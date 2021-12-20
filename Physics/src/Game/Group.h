#pragma once
#include "glm.hpp"
#include <vector>

struct Group
{
public:
	Group(glm::vec3 position, float area, std::vector<int>& enemyamounts);
	std::vector<int> enemyamounts;
	glm::vec3 groupPos;
	float spawnArea = 0.0f;
	int entitiesSpawned = 0;
	float nextEntitySpawnTime = 0.0f;
};