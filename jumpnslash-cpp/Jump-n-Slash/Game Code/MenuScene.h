#ifndef MENU_SCENE_H
#define MENU_SCENE_H

#include <list>

#include <SFML/Graphics/RectangleShape.hpp>

#include "../Engine Code/Scene.h"

// forward declarations
class Menu;

class MenuScene : public Scene
{
public:
	MenuScene() = default;
	MenuScene(const MenuScene& ms) = delete;
	MenuScene& operator=(const MenuScene& ms) = delete;
	virtual ~MenuScene() = default;

	virtual void Init() = 0;
	virtual void End() = 0;

protected:
	Menu* pMenu;
};

#endif