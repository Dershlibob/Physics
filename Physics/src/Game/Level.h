#pragma once
#include <vector>

#include "Group.h"

struct Level
{
	Level();
	void AddGroup(Group g);
	std::vector<Group>* getGroups()
	{
		return &groups;
	}

	int numOfEnemies = 0;
	float startTime = 0.0f;
private:
	std::vector<Group> groups;
};