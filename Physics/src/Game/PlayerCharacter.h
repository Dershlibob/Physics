#pragma once

#include "GLFW/glfw3.h"
#include "glm.hpp"

#include "Engine/Character.h"
#include "Engine/Camera.h"
#include "Engine/Model.h"
#include "Weapons/Weapon.h"

class Window;

class PlayerCharacter : public Character
{
public:

	Window* window;

	vector<Weapon*> weapons;
	int CurrentWeapon = 0;

	void Start()					override;
	void Update(float dt)			override;
	void Collision(Collider* other) override;
	void OnDestroy() override;

	float shootTime = 0.0f, shootInterval = 1.0f;



	bool done = false;
};
