#include "Enemy.h"

#include "GLFW/glfw3.h"

#include "Engine/Scene.h"

#include "PlayerCharacter.h"
#include "SceneManager.h"
#include "EnemyAI.h"
#include "Weapons/Basic.h"

static float random(float min, float max)
{
	return (min + static_cast <float> (rand()) /
		(static_cast <float> (RAND_MAX / (max - min))));
}

Enemy::Enemy()
{
	// These are the default enemy settings.
	weapon = new BasicWeapon(this);
	SetModel("cube");
	health = 5;
	tag = "Enemy";

	InitBT();
}

void Enemy::Start()
{
	//weapon = new BasicWeapon(this);
	//health = 3;
	//tag = "Enemy";
	//
	//InitBT();
}

void Enemy::Update(float dt)
{
	if (nextTick < glfwGetTime())
	{
		nextTick += random(0.3f, 2.5f);
		root->Tick();
	}
	MoveTo(destination);
}

void Enemy::InitBT()
{
	root = new CompositeNode();
	root->AddChild(new Fallback());
	Fallback* fb = (Fallback*)root->GetChildren().at(0);

	fb->AddChild(new Leaf(new CloseToPlayer(), new AttackPattern(), this));
	fb->AddChild(new Leaf(new ForceSuccess(), new Wandering(), this));
}

void Enemy::ShootCycle()
{
	if (nextShootTime < glfwGetTime())
	{
		Entity* player = Scene::FindObjectWithTag("Player").get();
		if (player)
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
}

void Enemy::Collision(Collider* other)
{
	if (other->parent->tag == "AllyBullet")
	{
		Bullet* b = (Bullet*)other->parent;
		TakeDamage(b->damage);
		b->Destroy();
	}
}

void Enemy::OnDestroy()
{
	SceneManager::enemiesKilled++;
	delete weapon;
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
	angle *= 180 / 3.14159f;

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
		position -= front * moveSpeed * dt;
	}
}