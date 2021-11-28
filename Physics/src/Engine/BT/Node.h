#pragma once
#include <vector>

enum class State
{
	SUCCESS,
	RUNNING,
	FAILURE
};

class CompositeNode;

class Enemy
{
public:
	CompositeNode* root;
	bool bIsAlive = false;

};

class Node
{
	Enemy* owner = nullptr;
public:

	void SetOwner(Enemy* e)
	{
		owner = e;
	}

	Enemy* Owner()
	{
		return owner;
	}

	virtual State Tick() = 0;
};

class CompositeNode : public Node
{
	std::vector<Node*> children;
public:
	void AddChild(Node* n);

	std::vector<Node*>& GetChildren()
	{
		return children;
	}

	State Tick() override
	{
		for (int i = 0; i < children.size(); ++i)
		{
			children[i]->Tick();
		}
		return State::SUCCESS;
	}

};

class Sequence : public CompositeNode
{
	State Tick() override
	{
		std::vector<Node*> children = GetChildren();
		for (int i = 0; i < children.size(); ++i)
		{
			State result = children[i]->Tick();
			if (result == State::FAILURE || result == State::RUNNING)
			{
				return result;
			}
		}
		return State::SUCCESS;
	}
};

class Fallback : public CompositeNode
{
	State Tick() override
	{
		State result;
		std::vector<Node*> children = GetChildren();
		for (int i = 0; i < children.size(); ++i)
		{
			result = children[i]->Tick();
			if (result == State::SUCCESS)
			{
				return result;
			}
		}
		return result;
	}
};

class Leaf : public CompositeNode
{
	Enemy* Owner;
public:

	Leaf(Node* Condition, Node* Action, Enemy* e)
	{
		Owner = e;
		AddChild(Condition);
		AddChild(Action);
		GetChildren().at(0)->SetOwner(e);
		GetChildren().at(1)->SetOwner(e);
	}

	State Tick() override
	{
		State result;
		std::vector<Node*> children = GetChildren();

		result = children[0]->Tick();
		if (result == State::SUCCESS)
		{
			children[1]->Tick();
		}
		return result;
	}
};