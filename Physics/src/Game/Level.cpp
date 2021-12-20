#include "Level.h"
#include <iostream>
#include "GLFW/glfw3.h"

Level::Level()
{
	startTime = glfwGetTime();
}

void Level::AddGroup(Group g)
{
	groups.push_back(g);
	for (int i = 0; i < groups.size(); ++i)
	{
		for (int j = 0; j < groups[i].enemyamounts.size(); ++j)
		{
			numOfEnemies += groups[i].enemyamounts[j];
		}
	}
	std::cout << "num: " << numOfEnemies << std::endl;
}
