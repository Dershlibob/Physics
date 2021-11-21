#include "Collision.h"
#include "Model.h"
#include "Entity.h"

Collider::Collider(Entity* e, Model* model, ColliderType type = ColliderType::SPHERICAL):
	colliderType(type)
{
	parent = e;
	if (colliderType == ColliderType::SPHERICAL)
	{
		for (int i = 0; i < model->GetMeshes()->size(); ++i)
		{
			for (int j = 0; j < model->GetMeshes()->at(i).vertices.size(); ++j)
			{
				glm::vec3 v = model->GetMeshes()->at(i).vertices[j].Position;
				if (SphereRadius < glm::length(v))
				{
					SphereRadius = glm::length(v);
				}
			}
		}
	}
}