#pragma once
#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"

#include "Mesh.h"
#include "Shader.h"

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
	vector<ModelTexture> textures_loaded;
	string directory;
	string name;
	void loadModel(string path);
	void processNode(aiNode* node, const aiScene* scene);
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);
	vector<ModelTexture> loadMaterialTextures(aiMaterial* mat, aiTextureType type,
		string typeName);
	unsigned int TextureFromFile(const char* path, const string& directory);
};