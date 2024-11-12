#ifndef SCENE_GRAPH_NODE_H
#define SCENE_GRAPH_NODE_H

#include <list>

// forward declarations
class DrawObject;

class SceneGraphNode
{
public:
	SceneGraphNode() = delete;
	SceneGraphNode(DrawObject* pDrawable);
	SceneGraphNode(const SceneGraphNode& n) = delete;
	SceneGraphNode& operator=(const SceneGraphNode& n) = delete;
	virtual ~SceneGraphNode() = default;

	using ChildNodeList = std::list<SceneGraphNode*>;

	void AddChild(SceneGraphNode* pChildNode);
	ChildNodeList& GetChildren();

private:
	friend class SceneGraphNodeAttorney;
	DrawObject* GetDrawObject();

	void SetParent(SceneGraphNode* pParentNode);

private:
	DrawObject* pDrawable;
	SceneGraphNode* pParent;
	ChildNodeList children;
};

#endif