#include "SceneGraphNodeAttorney.h"

#include "SceneGraphNode.h"

DrawObject* SceneGraphNodeAttorney::DrawObjectAccess::GetDrawObject(SceneGraphNode* pNode)
{
    return pNode->GetDrawObject();
}
