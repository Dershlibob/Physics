#pragma once

#include <vector>
#include <memory>

#include "gtc/quaternion.hpp"
#include "gtx/quaternion.hpp"

#include "Engine/BT/Node.h"
#include "Engine/Character.h"

#include "Game/Group.h"
#include "Game/Weapons/Weapon.h"

class PlayerCharacter;

class Enemy : public Character
{
public:
	CompositeNode* root;
	Weapon* weapon = nullptr;
	Enemy();

	bool bFleeing = false;

	void Start()		override;
	void Update(float)  override;
	void Collision(Collider* other) override;
	void OnDestroy() override;

	float moveSpeed = 5.0f;
	float rotSpeed = 90.0f;
	glm::vec3 velocity = { 0.0f, 0.0f, 0.0f };
	bool bDestinationReached = true;
	bool isAlive;

	glm::vec3 destination;
	glm::vec3 desiredDir;

	void ShootCycle();
	void MoveTo(glm::vec3 destination);

public:
	void InitBT();

	glm::quat orientation;
	int lastShootTime, nextShootTime;
	bool bStartMoving = false;

	float nextTick = 0.0f;
};