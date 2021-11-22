#pragma once

#include <vector>

#include "Engine/Character.h"
#include "gtc/quaternion.hpp"
#include "gtx/quaternion.hpp"

class Weapon;
class PlayerCharacter;

class Enemy : public Character
{
public:

	PlayerCharacter* player;

	bool isAlive;

	void Start()		override;
	void Update(float)  override;
	void Collision(Collider* other) override;

	~Enemy()
	{
		delete weapon;
	}

	Weapon* weapon = nullptr;

	float moveSpeed = 5.0f;
	float rotSpeed = 180.0f;
	glm::vec3 velocity = { 0.0f, 0.0f, 0.0f };

	void MoveTo(glm::vec3 destination);

	void Flocking(std::vector<std::shared_ptr<Enemy>>* enemies);
private:

	glm::vec3 ComputeAlignment(std::vector<std::shared_ptr<Enemy>>* enemies);
	glm::vec3 ComputeCohesion(std::vector<std::shared_ptr<Enemy>>* enemies);
	glm::vec3 ComputeSeparation(std::vector<std::shared_ptr<Enemy>>* enemies);
	float cohesionFactor, separationFactor;
public:

	glm::quat orientation;
	int lastShootTime, nextShootTime;
	bool bStartMoving = false;
};