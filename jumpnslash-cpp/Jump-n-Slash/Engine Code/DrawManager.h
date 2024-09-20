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

	// TODO: documentation for DrawManager::Register
	DrawListRef Register(DrawableObject* pDrawable);
	// TODO: documentation for DrawManager::Deregister
	void Deregister(DrawListRef drawListRef);

	void Draw();

private:
	DrawList drawList;
};

#endif