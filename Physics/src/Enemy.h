#pragma once

#include <vector>

#include "gtc/quaternion.hpp"
#include "gtx/quaternion.hpp"

#include "Engine/Character.h"
#include "Group.h"

class Weapon;
class PlayerCharacter;

class Enemy : public Character
{
public:

	PlayerCharacter* player;
	State state = State::IDLE;


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
	bool bDestinationReached = true;
	bool isAlive;
	glm::vec3 destination;


	void ShootCycle();
	void MoveTo(glm::vec3 destination);

public:

	glm::quat orientation;
	int lastShootTime, nextShootTime;
	bool bStartMoving = false;
};