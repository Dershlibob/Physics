#pragma once
#include "Engine/Entity.h"

class PlayerCharacter;

class Bullet : public Entity
{
public:
	Bullet();

	~Bullet()
	{
	}

	void Update(float dt)			override;
	void Collision(Collider* other) override;

	void SetDirection(PlayerCharacter* p);
	void LifeTime();

	glm::vec3 direction;

	float spawnTime = 0.0f;
	float lifeTime = 1.5f;
	float speed = 20.0f;
	int damage = 1;
};