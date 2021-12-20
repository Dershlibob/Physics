#include "Weapon.h"

#include <GLFW/glfw3.h>

#include "Engine/Window.h"
#include "Engine/ModelManager.h"
#include "Engine/Scene.h"

#include "Game/PlayerCharacter.h"

float IFireMode::nextShotTime = 0;

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
	{
		cout << "test!" << endl;
	}
}

IFireMode::IFireMode()
{

}

Weapon::Weapon(Entity* _parent)
{
	parent = _parent;
}

void AutomaticMode::FiringMode()
{
	PlayerCharacter* pc = (PlayerCharacter*)Scene::FindObjectWithTag("Player").get();
	if (pc)
	{
		weapon = pc->weapons[pc->CurrentWeapon];

		Window* window = Window::getInstance();
		if (glfwGetKey(window->getWindow(), GLFW_KEY_SPACE) == GLFW_PRESS)
		{
			if (glfwGetTime() > nextShotTime)
			{
				fireTime = glfwGetTime();
				nextShotTime = fireTime + fireInterval;

				Entity* bullet = weapon->Shoot();

				if (bSwitch)
				{
					bullet->position = pc->position - pc->front + (pc->right / 2.0f);
				}
				else
				{
					bullet->position = pc->position - pc->front - (pc->right / 2.0f);
				}
				bSwitch = !bSwitch;
				bullet->tag = "AllyBullet";
			}
		}
	}
}

void SemiautomaticMode::FiringMode()
{
	PlayerCharacter* pc = (PlayerCharacter*)Scene::FindObjectWithTag("Player").get();
	if (pc)
	{
		weapon = pc->weapons[pc->CurrentWeapon];

		Window* window = Window::getInstance();
		if (glfwGetKey(window->getWindow(), GLFW_KEY_SPACE) == GLFW_PRESS)
		{
			if (!bFired)
			{
				bFired = true;

				Entity* bullet = weapon->Shoot();
				bullet->tag = "AllyBullet";
			}
		}
		if (glfwGetKey(window->getWindow(), GLFW_KEY_SPACE) == GLFW_RELEASE)
		{
			bFired = false;
		}
	}
}

