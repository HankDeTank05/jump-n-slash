#include "DrawManager.h"

#include <cassert>
#include "DrawableObjectAttorney.h"

DrawManager::~DrawManager()
{
	drawList.clear();
}

DrawManager::DrawListRef DrawManager::Register(DrawableObject* pDrawable)
{
	return drawList.insert(drawList.end(), pDrawable);
}

void DrawManager::Deregister(DrawListRef drawListRef)
{
	drawList.erase(drawListRef);
}

void DrawManager::Draw()
{
	for (DrawList::iterator it = drawList.begin(); it != drawList.end(); it++)
	{
		DrawableObjectAttorney::GameLoop::Draw(*it);
	}
}
