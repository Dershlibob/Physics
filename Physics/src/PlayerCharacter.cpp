#include "PlayerCharacter.h"

#include <iostream>

#include "Engine/Shader.h"
#include "Engine/Window.h"
#include "Engine/Scene.h"
#include "Engine/ModelManager.h"

#include "Enemy.h"

#define PI 3.14159

void PlayerCharacter::Start()
{
	window = Window::getInstance();
	getCamera()->cameraPos.y = 60.0f;
	position = { 0.0f, 0.0f, 0.0f };
	front = { 0.0f, 0.0f, 0.0f };
	tag = "Player";
	health = 100;

	weapons.push_back(new BasicWeapon(this));
	weapons.push_back(new ShotgunWeapon(this));
}

void PlayerCharacter::Update(float dt)
{
	if (glfwGetKey(window->getWindow(), GLFW_KEY_1) == GLFW_PRESS)
	{
		CurrentWeapon = 0;
	}
	if (glfwGetKey(window->getWindow(), GLFW_KEY_2) == GLFW_PRESS)
	{
		CurrentWeapon = 1;
	}
	weapons[CurrentWeapon]->GetFireMode()->FiringMode();

	if (glfwGetKey(window->getWindow(), GLFW_KEY_UP) == GLFW_PRESS)
		velocity -= front * acceleration * dt;
	if (glfwGetKey(window->getWindow(), GLFW_KEY_DOWN) == GLFW_PRESS)
		velocity += front * acceleration * dt;
	if (glfwGetKey(window->getWindow(), GLFW_KEY_LEFT) == GLFW_PRESS)
		yaw -= rotationSpeed * dt;
	if (glfwGetKey(window->getWindow(), GLFW_KEY_RIGHT) == GLFW_PRESS)
		yaw += rotationSpeed * dt;

	right = cross(front, glm::vec3(0.0f, 1.0f, 0.0f));

	if (glm::length(velocity) > maxSpeed)
	{
		velocity = glm::normalize(velocity) * maxSpeed;
	}

	if (position.z > 400)
	{
		position.z = 400;
		velocity.z = 0;
	}
	if (position.z < -400)
	{
		position.z = -400;
		velocity.z = 0;
	}
	if (position.x > 400)
	{
		position.x = 400;
		velocity.x = 0;
	}
	if (position.x < -400)
	{
		position.x = -400;
		velocity.x = 0;
	}

	position += velocity * dt;
	velocity -= velocity * 0.5f * dt;

	getCamera()->cameraPos.x = position.x;
	getCamera()->cameraPos.z = position.z;

	orientation = glm::quatLookAt(front, glm::vec3(0.0f, 1.0f, 0.0f));
}

void PlayerCharacter::Collision(Collider* other)
{
	if (other->parent->tag == "EnemyBullet")
	{
		TakeDamage(other->parent->Damage);
		other->parent->Destroy();
	}
}
