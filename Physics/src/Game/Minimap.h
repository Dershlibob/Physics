#pragma once
#include "Engine/UI.h"

class Texture;

class Minimap : public UI
{
public:
	Minimap(Shader*, Texture* texture, float x, float y, glm::vec3);
	
	Texture* t1;
	float lastUpdate = 0.0f;
	float interval = 1.0f;
	float zoom = 0.5f;
	void Update();
};