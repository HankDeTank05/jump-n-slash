#ifndef DRAW_MANAGER_H
#define DRAW_MANAGER_H

#include <list>

// forward declarations
class DrawObject;

class DrawManager
{
public:
	DrawManager() = default;
	DrawManager(const DrawManager& dm) = delete;
	DrawManager& operator=(const DrawManager& dm) = delete;
	virtual ~DrawManager();

private:
	using DrawList = std::list<DrawObject*>;
public:
	using DrawListRef = DrawList::iterator;

	DrawListRef Register(DrawObject* pDrawable); // TODO: docs for DrawManager::Register
	void Deregister(DrawListRef drawListRef); // TODO: docs for DrawManager::Deregister

	void Draw();

private:
	DrawList drawList;
};

#endif