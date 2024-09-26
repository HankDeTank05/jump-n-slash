#ifndef SCENE_ATTORNEY_H
#define SCENE_ATTORNEY_H

#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>

#include "DrawManager.h"
#include "UpdateManager.h"
#include "InputEvent.h"

// forward declarations
class Scene;
class Command;

class SceneAttorney
{
public:
	class GameLoop
	{
	private:
		friend class JumpSlashEngine; // TODO: change this to SceneManager when it's created
		static void Update(Scene* pScene);
		static void Draw(Scene* pScene);
	};

	class Commands
	{
	private:
		friend class UpdatableObject;
		friend class DrawableObject;
		friend class InputObject;
		static void AddCommand(Scene* pScene, Command* pCmd);
	};

	class Update
	{
	private:
		friend class UpdatableObject;
		static UpdateManager::UpdateListRef Register(Scene* pScene, UpdatableObject* pUpdatable);
		static void Deregister(Scene* pScene, UpdateManager::UpdateListRef deleteRef);
	};

	class Draw
	{
	private:
		friend class DrawableObject;
		static DrawManager::DrawListRef Register(Scene* pScene, DrawableObject* pDrawable);
		static void Deregister(Scene* pScene, DrawManager::DrawListRef deleteRef);
	};

	class Input
	{
	private:
		friend class InputObject;
		static void RegisterKey(Scene* pScene, sf::Keyboard::Key key, InputObject* pInputable, KeyEvent eventToReg);
		static void DeregisterKey(Scene* pScene, sf::Keyboard::Key key, InputObject* pInputable, KeyEvent eventToDereg);
		static void RegisterMouseBtn(Scene* pScene, sf::Mouse::Button btn, InputObject* pInputable, MouseEvent eventToReg);
		static void DeregisterMouseBtn(Scene* pScene, sf::Mouse::Button btn, InputObject* pInputable, MouseEvent eventToDereg);
	};
};

#endif