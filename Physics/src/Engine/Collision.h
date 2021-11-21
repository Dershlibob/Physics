#pragma once
#include <string>

class Model;
class Entity;

enum class ColliderType
{
	SPHERICAL,
	RECTANGULAR,
	BOX
};

class Collider
{
private:
	ColliderType colliderType;
	float SphereRadius = 0.0f;
public:

	std::string test = "this is a test";
	Entity* parent;

	Collider(Entity* e, Model*, ColliderType);

	float getRadius()
	{
		return SphereRadius;
	}

	void ScaleRadius(float factor)
	{
		SphereRadius *= factor;
	}
};