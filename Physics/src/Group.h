#pragma once
#include <vector>
#include "memory"

#include "glm.hpp"

class Enemy;

enum class State
{
	IDLE,
	ATTACKING
};

struct Group
{
public:

	Group(glm::vec3 position, float area, int size);
	glm::vec3 groupPos;

	float spawnArea = 0.0f;
	int groupSize = 0;

	float areaRadius = 0.0f;

	void SetAreaRadius()
	{
		areaRadius = sqrt(enemies.size()) * 5;
	}

	int entitiesSpawned = 0;
	float nextEntitySpawnTime = 0.0f;

	std::vector<std::shared_ptr<Enemy>> enemies;

	void Idle();
	void Attacking();
	void OnEnemyDestroy();
	void Spawn(std::shared_ptr<Enemy> e);
};