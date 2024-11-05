#include "SceneGraphNode.h"

SceneGraphNode::SceneGraphNode(DrawObject* _pDrawable)
	: pDrawable(_pDrawable),
	pParent(nullptr),
	children()
{
	// do nothing
}

void SceneGraphNode::AddChild(SceneGraphNode* pChildNode)
{
	children.push_back(pChildNode);
	pChildNode->SetParent(this);
}

SceneGraphNode::ChildNodeList& SceneGraphNode::GetChildren()
{
	return children;
}

DrawObject* SceneGraphNode::GetDrawObject()
{
	return pDrawable;
}

void SceneGraphNode::SetParent(SceneGraphNode* pParentNode)
{
	assert(pParent == nullptr); // crash if you're trying to replace an existing parent
	pParent = pParentNode;
}
