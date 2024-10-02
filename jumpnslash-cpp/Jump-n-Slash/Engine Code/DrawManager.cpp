#include "DrawManager.h"

#include <cassert>
#include "DrawObjectAttorney.h"

DrawManager::~DrawManager()
{
	drawList.clear();
}

DrawManager::DrawListRef DrawManager::Register(DrawObject* pDrawable)
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
		DrawObjectAttorney::GameLoop::Draw(*it);
	}
}
