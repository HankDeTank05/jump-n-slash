#include "DrawManager.h"
#include <cassert>

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
	// TODO: empty function DrawManager::Draw
	assert(false);
}
