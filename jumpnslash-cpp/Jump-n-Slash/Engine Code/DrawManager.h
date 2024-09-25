#ifndef DRAW_MANAGER_H
#define DRAW_MANAGER_H

#include <list>

// forward declarations
class DrawableObject;

class DrawManager
{
public:
	DrawManager() = default;
	DrawManager(const DrawManager& dm) = delete;
	DrawManager& operator=(const DrawManager& dm) = delete;
	virtual ~DrawManager();

private:
	using DrawList = std::list<DrawableObject*>;
public:
	using DrawListRef = DrawList::iterator;

	DrawListRef Register(DrawableObject* pDrawable); // TODO: documentation for DrawManager::Register
	void Deregister(DrawListRef drawListRef); // TODO: documentation for DrawManager::Deregister

	void Draw();

private:
	DrawList drawList;
};

#endif