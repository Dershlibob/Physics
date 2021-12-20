#include "Node.h"

Node* CompositeNode::AddChild(Node* n)
{
	children.push_back(n);
	return children.back();
}
