#include "Entity.h"
#include "Scene.h"

Entity::Entity()
{
	shader = Scene::getShader();
	cam = Scene::getCamera();
	matScale = glm::mat4(1.0f);
	matRotation = glm::mat4(1.0f);
	position = { 0.0f, 0.0f, 0.0f };
	model = nullptr;
	collider = nullptr;

	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	front = glm::normalize(front);

	Start();
}

Entity::~Entity()
{

}

void Entity::Draw()
{
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	front = glm::normalize(front);

	orientation = glm::quatLookAt(front, glm::vec3(0.0f, 1.0f, 0.0f));
	matRotation = glm::toMat4(orientation);

	matPosition = glm::translate(glm::mat4(1.0f), position);
	transform = matPosition * matRotation * matScale;

	shader->Bind();
	shader->setMat4("u_Model", transform);
	shader->setMat4("u_View", cam->view);
	shader->setMat4("u_Projection", cam->proj);

	if (model)
		model->Draw(*shader);
}

void Entity::CheckCollisions()
{
	for (int i = 0; i < Scene::EntityCount(); ++i)
	{
		shared_ptr<Entity> e = Scene::GetEntities()->at(i);
		if (e->collider)
		{
			if (index != e->index)
			{
				float distance = glm::length(e->position - position);
				if (distance <= e->collider->getRadius() + collider->getRadius())
				{
					Collision(e->collider);
				}
			}
		}
	}
}

void Entity::CreateCollider(ColliderType type)
{	// this function must be called AFTER a model has been set for the entity.
	collider = new Collider(this, model, type);
}

void Entity::ImmediateDestroy(shared_ptr<Entity> e)
{
	vector<shared_ptr<Entity>>* eVec = Scene::GetEntities();

	delete e->collider;
	Scene::get().ObjectsStarted--;
	eVec->erase(eVec->begin() + e->index);
}

void Entity::ImmediateDestroy()
{
	vector<shared_ptr<Entity>>* eVec = Scene::GetEntities();

	delete collider;
	Scene::get().ObjectsStarted--;
	eVec->erase(eVec->begin() + index);
}

void Entity::Destroy()
{
	bDestroy = true;
}

void Entity::Destroy(shared_ptr<Entity> e)
{
	e->bDestroy = true;
}

void Entity::CalcFront()
{
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	front = glm::normalize(front);
}