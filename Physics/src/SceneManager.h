#pragma once
#include <memory>

#include "Engine/Entity.h"
#include "Engine/ModelManager.h"
#include "Group.h"

class Enemy;

struct Level
{
	Level();

	vector<Group> groups;
	float startTime = 0.0f;
};

class SceneManager : public Entity
{
private:
	vector<Level> levels;
	int CurrentLevel = 0;

public:

	SceneManager()
	{

	}

	void Start();
	void Update(float dt);

	bool done = false;

};