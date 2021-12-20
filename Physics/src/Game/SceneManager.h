#pragma once
#include <memory>

#include "Engine/Entity.h"
#include "Engine/ModelManager.h"

#include "Level.h"

class Enemy;

class SceneManager : public Entity
{
public:
	vector<Level> levels;
	int CurrentLevel = 0;

	static int enemiesKilled;

	SceneManager()
	{

	}

	void Start();
	void Update(float dt);

	bool done = false;

private:
	int spawnType = 0;
};