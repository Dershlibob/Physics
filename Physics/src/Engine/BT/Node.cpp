#include "Node.h"
#include "Time.h"

void CompositeNode::AddChild(Node* n)
{
	children.push_back(n);
}
