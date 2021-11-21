#include "Bullet.h"
#include "Engine/ModelManager.h"

#include "PlayerCharacter.h"
#include "GLFW/glfw3.h"

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

void BigBullet::Start()
{
	SetModel(ModelManager::getModel("sphere"));
	LinearScale(0.8f);
	speed = 25;
}

void SmallBullet::Start()
{
	SetModel(ModelManager::getModel("sphere"));
	LinearScale(0.3f);
}