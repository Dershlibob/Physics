#include "Scene.h"

Scene& Scene::get()
{
	static Scene instance;
	return instance;
}