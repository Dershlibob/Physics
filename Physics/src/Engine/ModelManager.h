#pragma once
#include <iostream>
#include <vector>

#include "Model.h"

class ModelManager
{
private:

	ModelManager(){}

	ModelManager(const ModelManager&) = delete;
	void operator=(const ModelManager&) = delete;

	std::vector<Model*> models;

public:

	static std::vector<Model*>& getModels()
	{
		return ModelManager::get().models;
	}

	static Model* getModel(std::string name)
	{
		for (int i = 0; i < ModelManager::getModels().size(); ++i)
		{
			if (ModelManager::getModels().at(i)->GetName() == name)
			{
				return ModelManager::getModels().at(i);
			}
		}
		std::cout << "Model name '" << name << "' doesn't exist" << std::endl;
		return nullptr;
	}

	static Model* LoadModel(std::string location)
	{
		ModelManager::getModels().push_back(new Model(location));

		return ModelManager::getModels().back();
	}

	static ModelManager& get()
	{
		static ModelManager instance;

		return instance;
	}
};