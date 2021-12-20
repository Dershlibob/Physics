#include "Minimap.h"
#include <memory>

#include "GLFW/glfw3.h"

#include "Engine/Scene.h"
#include "Engine/Texture.h"

#include "PlayerCharacter.h"

Minimap::Minimap(Shader* shader, Texture* texture, float x, float y, glm::vec3 pos):
	UI(shader, texture, x, y, pos)
{
	t1 = new Texture("enemy.png");
}

void Minimap::Update()
{
	if (lastUpdate + interval < glfwGetTime())
	{
		PlayerCharacter* pc = (PlayerCharacter*)Scene::FindObjectWithTag("Player").get();
		lastUpdate = glfwGetTime();
		components.clear();
		if (pc)
		{
			for (int i = 0; i < Scene::GetEntities()->size(); ++i)
			{
				shared_ptr<Entity> e = Scene::GetEntities()->at(i);
				if (e->tag == "Enemy")
				{
					glm::vec3 pos(0.0f);

					pos.x = (pc->position.x - e->position.x) * zoom;
					pos.y = (pc->position.z - e->position.z) * zoom;
					pos.y *= -1;
					AddUI(shader, t1, 5.0f, 5.0f, pos);
				}
			}
		}
	}
}