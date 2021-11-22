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
	cohesionFactor = 1, separationFactor = 1;
}

void Enemy::Update(float dt)
{
	if (player)
	{
		if (glm::length(player->position - position) < 50)
		{
			if (nextShootTime < glfwGetTime())
			{
				if (weapon) // temporary hopefully
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

void Enemy::Flocking(std::vector<std::shared_ptr<Enemy>>* enemies)
{
	glm::vec3 alignment  =  ComputeAlignment(enemies);
	glm::vec3 cohesion   =  ComputeCohesion(enemies);
	glm::vec3 separation =  ComputeSeparation(enemies);

	glm::vec3 destination = glm::normalize(-position);

	velocity = 
		//(cohesion * cohesionFactor) + 
		(separation * separationFactor) + destination;

	MoveTo((velocity * moveSpeed) + position);
}

glm::vec3 Enemy::ComputeAlignment(std::vector<std::shared_ptr<Enemy>>* enemies)
{
	glm::vec3 v(0.0f);
	int groupSize = enemies->size();

	for (std::shared_ptr<Enemy> e : *enemies)
	{
		if (e->index != index)
		{
			v.x += e->velocity.x;
			v.z += e->velocity.z;
		}
	}

	if (glm::length(v) < 0.01f)
	{
		return glm::vec3(0.0f);
	}

	v.x /= groupSize;
	v.z /= groupSize;
	v = glm::normalize(v);

	return v;
}

glm::vec3 Enemy::ComputeCohesion(std::vector<std::shared_ptr<Enemy>>* enemies)
{
	glm::vec3 v(0.0f);
	int groupSize = enemies->size();
	float distance = 0;			
	//shared_ptr<Enemy> e = *enemies->at(0).use_count();

	for (int i = 0; i < enemies->size(); ++i)
	{
		Enemy* e = enemies->at(i).get();
		if (e->index != index)
		{
			{
				float d = glm::length(e->position - position) - (e->GetCollider()->getRadius() + GetCollider()->getRadius());
				if (d > 1.5f && d < 2.0f)
				{
					if (d > distance)
					{
						distance = d;
					}
					v.x += e->position.x;
					v.z += e->position.z;
				}
			}
		}
	}
	if (glm::length(v) < 0.01f)
	{
		return glm::vec3(0.0f);
	}

	if (distance > 10.0f)
	{
		distance = 10.0f;
	}
	cohesionFactor = distance;


	v.x /= groupSize;
	v.z /= groupSize;
	v = glm::vec3(v.x - position.x, 0.0f, v.z - position.z);
	v = glm::normalize(v);

	return v;
}

glm::vec3 Enemy::ComputeSeparation(std::vector<std::shared_ptr<Enemy>>* enemies)
{
	glm::vec3 v(0.0f);
	int groupSize = enemies->size();
	float distance = INT_MAX;

	for (std::shared_ptr<Enemy> e : *enemies)
	{
		if (e->index != index)
		{
			float d = glm::length(e->position - position) - (e->GetCollider()->getRadius() + GetCollider()->getRadius());
			if (d < 1.0f)
			{
				if (d < distance)
				{
					distance = d;
				}
				v.x += e->position.x - position.x;
				v.z += e->position.z - position.z;
			}
		}
	}
	if (glm::length(v) < 0.01f)
	{
		return glm::vec3(0.0f);
	}
	if (distance < 0.1)
		separationFactor = 20;
	else
		separationFactor = 1 / distance;

	v.x /= groupSize;
	v.z /= groupSize;
	v = glm::normalize(v);

	v.x *= -1;
	v.z *= -1;

	return v;
}

void Enemy::MoveTo(glm::vec3 dest)
{
	if (glm::length(position - dest) < 0.1)
		return;
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
