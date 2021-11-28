#include "Enemy.h"

#include "GLFW/glfw3.h"

#include "Engine/Scene.h"

#include "Weapon.h"
#include "PlayerCharacter.h"
#include "SceneManager.h"

static float random(float min, float max)
{
	return (min + static_cast <float> (rand()) /
		(static_cast <float> (RAND_MAX / (max - min))));
}

void Enemy::Start()
{
	player = (PlayerCharacter*)Scene::FindObjectWithTag("Player").get();
	weapon = new BasicWeapon(this);
	health = 3;
	tag = "Enemy";
}

void Enemy::Update(float dt)
{
	if (player)
	{
		float distFromPlayer = glm::length(player->position - position);
		if (distFromPlayer < 30)
		{
			state = State::ATTACKING;
			moveSpeed = 5.0f;
		}
		else
		{
			state = State::IDLE;
			moveSpeed = 2.0f;
		}
	}
}

void Enemy::ShootCycle()
{
	if (nextShootTime < glfwGetTime())
	{
		lastShootTime = glfwGetTime();
		nextShootTime = random(1.0f, 5.0f) + lastShootTime;
		Bullet* bullet = (Bullet*)weapon->Shoot();
		bullet->speed = 8.0f;
		bullet->lifeTime = 2.5f;
		bullet->direction = glm::normalize(position - player->position);
		bullet->tag = "EnemyBullet";
	}
}

void Enemy::Collision(Collider* other)
{
	if (other->parent->tag == "AllyBullet")
	{
		TakeDamage(other->parent->Damage);
		other->parent->Destroy();
	}
}

void Enemy::MoveTo(glm::vec3 dest)
{
	if (glm::length(position - dest) < 0.1)
	{
		bDestinationReached = true;
		return;
	}
	glm::vec3 direction = glm::normalize(position - dest);

	float angle = glm::acos(glm::dot(front, direction));
	angle *= 180 / 3.14159;

	if (angle < 90)
	{
		bStartMoving = true;
	}
	else if (angle > 120)
	{
		bStartMoving = false;
	}

	glm::vec3 cross = glm::cross(front, direction);

	if (bStartMoving == false)
	{
		if (cross.y > 0)
			yaw -= rotSpeed * dt;
		else
			yaw += rotSpeed * dt;
	}
	else
	{
		if (angle > 1.0)
		{
			if (cross.y > 0)
				yaw -= rotSpeed * dt;
			else
				yaw += rotSpeed * dt;
		}

		position -= direction * moveSpeed * dt;
	}
}
