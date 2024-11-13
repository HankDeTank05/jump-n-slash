#ifndef MENU_SCENE_H
#define MENU_SCENE_H

// engine includes
#include "../Engine Code/Scene.h"

// forward declarations
class Menu;
class MenuManager;

class MenuScene : public Scene
{
public:
	MenuScene();
	MenuScene(const MenuScene& ms) = delete;
	MenuScene& operator=(const MenuScene& ms) = delete;
	virtual ~MenuScene();

	virtual void Init() = 0;
	virtual void End() = 0;

protected:
	MenuManager* GetMenuManager();
	void SetStartingMenu(Menu* pStartingMenu);

protected:
	MenuManager* pMenuMgr; // MenuScene class DOES OWN this pointer
};

#endif