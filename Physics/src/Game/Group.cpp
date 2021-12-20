#include "Group.h"

Group::Group(glm::vec3 groupPosition, float spawnArea, std::vector<int>& enemyamounts) :
	groupPos(groupPosition),
	spawnArea(spawnArea),
	enemyamounts(enemyamounts)
{}