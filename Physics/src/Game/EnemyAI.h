#pragma once

#include "Engine/BT/Node.h"
#include "Enemy.h"

static float random(float min, float max);

/*
*	Conditions
*/

class CloseToPlayer : public Node
{
public:
	NodeState Tick() override
	{
		Entity* pc = Scene::FindObjectWithTag("Player").get();
		if (pc)
		{
			float distToPlayer = glm::length(Owner()->position - pc->position);
			if (distToPlayer < 30)
			{
				return NodeState::SUCCESS;
			}
		}
		return NodeState::FAILURE;
	}
};

class ForceSuccess : public Node
{
public:
	NodeState Tick() override
	{
		return NodeState::SUCCESS;
	}
};

/*
*	Actions
*/

class AttackPattern : public Node
{
public:
	NodeState Tick() override
	{
		Entity* pc = Scene::FindObjectWithTag("Player").get();
		if (pc)
		{
			float distToPlayer = glm::length(Owner()->position - pc->position);
			glm::vec3 d = glm::normalize(Owner()->position - pc->position);

			float offset = random(-20.0f, 20.0f);
			offset = offset * 3.14159 / 180.0f;

			float dx = d.x * cos(offset) - d.z * sin(offset);
			float dz = d.x * sin(offset) + d.z * cos(offset);
			d = glm::vec3(dx, 0.0f, dz);
			Owner()->desiredDir = d;

			if (distToPlayer < 10)
			{
				Owner()->bFleeing = true;
				Owner()->ShootCycle();
			}
			else if (distToPlayer > 25)
			{
				Owner()->bFleeing = false;
			}
			if (Owner()->bFleeing)
			{
				Owner()->destination = Owner()->desiredDir * 30.0f;
			}
			else
			{
				Owner()->destination = -Owner()->desiredDir * 30.0f;
			}
			return NodeState::SUCCESS;
		}
		return NodeState::FAILURE;
	}
};

class Wandering : public Node
{
public:
	int number = 10;
	NodeState Tick() override
	{
		if (Owner()->bDestinationReached)
		{
			glm::vec3 dest;
			dest = glm::normalize(glm::vec3(random(-1.0f, 1.0f), 0.0f, random(-1.0f, 1.0f)));
			dest *= random(0.0f, 30.0f);
			if (dest.x < -400.0f || dest.x > 400.0f)
			{
				dest.x *= -1;
			}
			if (dest.z < -400.0f || dest.z > 400.0f)
			{
				dest.z *= -1;
			}
			dest += Owner()->position;
			Owner()->destination = dest;
			Owner()->bDestinationReached = false;
		}
		else
		{
			Owner()->MoveTo(Owner()->destination);
		}
		return NodeState::SUCCESS;
	}
};
