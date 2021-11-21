#pragma once
#include <iostream>

#include "glm.hpp"
#include "gtc/quaternion.hpp"
#include "gtx/quaternion.hpp"

#include "Model.h"
#include "Camera.h"
#include "Collision.h"


class Scene;
class ShotType;

class Entity
{
private:
	Model* model;
	Shader* shader;
	Camera* cam;
	ShotType* st;
	Collider* collider;

public:
	int health = 100;
	int Damage = 1;

	bool bDestroy = false;
	bool bStartFuncCalled = false;

	static float dt;

	int index = 0;
	string tag = "NULL";

	void CreateCollider(ColliderType type);
	Collider* GetCollider(){ 
		if (collider)
			return collider;
		else
			return nullptr;
	}

	Entity();
	virtual ~Entity();

	virtual void Start() {}
	virtual void Update(float dt) {}
	virtual void Collision(Collider* other) {}

	void Draw();
	void CheckCollisions();

	void Destroy();
	void Destroy(shared_ptr<Entity> e);
	void ImmediateDestroy(shared_ptr<Entity> e);
	void ImmediateDestroy();

	template <typename T>
	shared_ptr<Entity> Instantiate(T)
	{ // Must be a class derived from the Entity class.
		vector<shared_ptr<Entity>>* e = Scene::GetEntities();
		e->push_back(make_shared<T>());
	
		return e->back();
	}

	template <typename T>
	shared_ptr<Entity> Instantiate(T, Model* model, glm::vec3 _position)
	{ // Must be a class derived from the Entity class.
		vector<shared_ptr<Entity>>* e = Scene::GetEntities();
		e->push_back(make_shared<T>());
		e->back()->position = _position;
		if (model)
		{
			e->back()->SetModel(model);
		}
		return e->back();
	}

	void SetModel(Model* m)
	{
		model = m;
		CreateCollider(ColliderType::SPHERICAL); // Temporary
	}

	void LinearScale(float scale)
	{
		matScale = glm::scale(glm::mat4(1.0f), glm::vec3(scale));
		collider->ScaleRadius(scale);
	}

	Camera* getCamera()
	{
		return cam;
	}

	float pitch = 0.0f, yaw = -90.0f;

	void CalcFront();

	glm::vec3 position;
	glm::vec3 front;

	glm::quat orientation;

private:
	glm::mat4 matPosition;
	glm::mat4 matRotation;
	glm::mat4 matScale;

	glm::mat4 transform;
	glm::mat4 mvp;
};