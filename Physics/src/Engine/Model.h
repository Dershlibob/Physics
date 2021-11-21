#pragma once

#include "Mesh.h"
#include "Shader.h"

#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"
#include "Camera.h"

class Model
{

public:
	Model(std::string path)
	{
		loadModel(path);
	}
	void Draw(Shader& shader);

	string GetName()
	{
		return name;
	}

	vector<Mesh>* GetMeshes()
	{
		return &meshes;
	}

private:
	vector<Mesh> meshes;
	vector<Texture> textures_loaded;
	string directory;
	string name;
	void loadModel(string path);
	void processNode(aiNode* node, const aiScene* scene);
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);
	vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type,
		string typeName);
	unsigned int TextureFromFile(const char* path, const string& directory);
};