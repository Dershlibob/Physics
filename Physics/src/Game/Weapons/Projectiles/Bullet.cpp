#include "Bullet.h"

#include "GLFW/glfw3.h"

#include "Engine/ModelManager.h"

#include "Game/PlayerCharacter.h"

Bullet::Bullet()
{
	spawnTime = glfwGetTime();
}

void Bullet::Update(float dt)
{
	position -= direction * speed * dt;
	LifeTime();
}

void Bullet::Collision(Collider* other)
{

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
