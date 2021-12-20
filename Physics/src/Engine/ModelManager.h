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

	static std::vector<Model*>& GetModels()
	{
		return ModelManager::get().models;
	}

	static Model* GetModel(std::string name)
	{
		auto m = ModelManager::GetModels();
		for (int i = 0; i < m.size(); ++i)
		{
			if (m.at(i)->GetName() == name)
			{
				return m.at(i);
			}
		}
		std::cout << "Model name '" << name << "' doesn't exist" << std::endl;
		return nullptr;
	}

	static Model* LoadModel(std::string location)
	{
		ModelManager::GetModels().push_back(new Model(location));

		return ModelManager::GetModels().back();
	}

	static ModelManager& get()
	{
		static ModelManager instance;

		return instance;
	}
};