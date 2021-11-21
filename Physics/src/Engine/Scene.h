#pragma once
#include <vector>
#include <memory>

#include "Entity.h"

class Scene
{
private:
	Scene(){}
	Scene(const Scene&) = delete;
	void operator=(const Scene&) = delete;
private:

	Shader* defaultShader;
	Camera* defaultCam;
	std::vector<shared_ptr<Entity>> Entities;

public:

	int ObjectsStarted = 0;

	static int getObjectsStarted()
	{
		return Scene::get().ObjectsStarted;
	}

	static shared_ptr<Entity> FindObjectWithTag(const string& name)
	{
		std::vector<shared_ptr<Entity>>* e = Scene::GetEntities();
		for (int i = 0; i < e->size(); ++i)
		{
			if (e->at(i)->tag == name)
			{
				return e->at(i);
			}
		}
	}

	static std::vector<shared_ptr<Entity>>* GetEntities()
	{
		return &Scene::get().Entities;
	}

	static void Init(Shader* shader, Camera* cam)
	{
		Scene::get().defaultShader = shader;
		Scene::get().defaultCam = cam;
	}

	static shared_ptr<Entity> Instantiate()
	{
		Scene::GetEntities()->push_back(make_shared<Entity>());

		return Scene::GetEntities()->back();
	}

	template <typename T>
	static shared_ptr<Entity> Instantiate(T)
	{
		Scene::GetEntities()->push_back(make_shared<T>());
		return Scene::GetEntities()->back();
	}

	static int EntityCount()
	{
		return Scene::get().Entities.size();
	}

	static void StartEntity()
	{
		for (int i = Scene::get().ObjectsStarted; i < Scene::get().Entities.size(); ++i)
		{
			Scene::get().Entities[i]->Start();
			Scene::get().Entities[i]->index = Scene::get().ObjectsStarted;
			Scene::get().Entities[i]->bStartFuncCalled = true;
			++Scene::get().ObjectsStarted; // Remember to decrement this value when objects are deleted.
		}
	}

	static void UpdateEntities(double dt)
	{
		for (int i = 0; i < Scene::get().Entities.size(); ++i)
		{
			if (Scene::get().Entities[i]->bStartFuncCalled)
			{
				Scene::get().Entities[i]->index = i;
				Scene::get().Entities[i]->Update(dt);
			}
		}
		Scene::EntityCollisions();
	}

	static void DrawEntities()
	{
		std::vector<shared_ptr<Entity>>* e = Scene::GetEntities();
		for (int i = 0; i < Scene::EntityCount(); ++i)
		{
			if (Scene::get().Entities[i]->bStartFuncCalled)
				e->at(i)->Draw();
		}
	}

	static void FinalDestroy()
	{
		std::vector<shared_ptr<Entity>>* e = Scene::GetEntities();

		for (int i = 0; i < e->size(); ++i)
		{
			if (e->at(i)->bDestroy)
			{
				e->at(i)->index = i;
				e->at(i)->ImmediateDestroy();
			}
		}
	}

	static void EntityCollisions()
	{
		std::vector<shared_ptr<Entity>>* e = Scene::GetEntities();
		for (int i = 0; i < Scene::EntityCount(); ++i)
		{
			shared_ptr<Entity> e = Scene::GetEntities()->at(i);
			if (e->GetCollider())
			{
				e->CheckCollisions();
			}
		}
	}

	static Scene& get();

	static Shader* getShader()
	{
		return Scene::get().defaultShader;
	}

	static Camera* getCamera()
	{
		return Scene::get().defaultCam;
	}
};