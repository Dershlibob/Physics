#include "Bullet.h"

#include "GLFW/glfw3.h"

#include "Engine/ModelManager.h"

#include "Game/PlayerCharacter.h"

Bullet::Bullet()
{
	spawnTime = glfwGetTime();
	//tag = "AllyBullet";
}

void Bullet::Update(float dt)
{
	Trajectory(dt);
	LifeTime();
}

void Bullet::Trajectory(float dt)
{
	position -= direction * speed * dt;
}

void Bullet::LifeTime()
{
	if (spawnTime + lifeTime < glfwGetTime())
	{
		Destroy();
	}
}

void Bullet::SetDirection(PlayerCharacter* p)
{
	direction = p->front;
}
