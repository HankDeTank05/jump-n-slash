#ifndef SCENE_GRAPH_NODE_ATTORNEY_H
#define SCENE_GRAPH_NODE_ATTORNEY_H

// forward declarations
class SceneGraphNode;
class DrawObject;

class SceneGraphNodeAttorney
{
public:
	class DrawObjectAccess
	{
	private:
		friend class DrawObject;
		static DrawObject* GetDrawObject(SceneGraphNode* pNode);
	};
};

#endif