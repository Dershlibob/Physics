#pragma once
#include <vector>

class Enemy;

enum class NodeState
{
	SUCCESS,
	RUNNING,
	FAILURE
};

class CompositeNode;

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

	virtual NodeState Tick() = 0;
};

class CompositeNode : public Node
{
	std::vector<Node*> children;
public:
	Node* AddChild(Node* n);

	std::vector<Node*>& GetChildren()
	{
		return children;
	}

	NodeState Tick() override
	{
		for (int i = 0; i < children.size(); ++i)
		{
			children[i]->Tick();
		}
		return NodeState::SUCCESS;
	}

};

class Sequence : public CompositeNode
{
	NodeState Tick() override
	{
		std::vector<Node*> children = GetChildren();
		for (int i = 0; i < children.size(); ++i)
		{
			NodeState result = children[i]->Tick();
			if (result == NodeState::FAILURE || result == NodeState::RUNNING)
			{
				return result;
			}
		}
		return NodeState::SUCCESS;
	}
};

class Fallback : public CompositeNode
{
	NodeState Tick() override
	{
		NodeState result;
		std::vector<Node*> children = GetChildren();
		for (int i = 0; i < children.size(); ++i)
		{
			result = children[i]->Tick();
			if (result == NodeState::SUCCESS)
			{
				return result;
			}
		}
		return result;
	}
};

class Leaf : public CompositeNode
{
public:
	Leaf(Node* Condition, Node* Action, Enemy* e)
	{
		AddChild(Condition);
		AddChild(Action);
		GetChildren().at(0)->SetOwner(e);
		GetChildren().at(1)->SetOwner(e);
	}

	NodeState Tick() override
	{
		NodeState result;
		std::vector<Node*> children = GetChildren();

		result = children[0]->Tick();
		if (result == NodeState::SUCCESS)
		{
			children[1]->Tick();
		}
		return result;
	}
};