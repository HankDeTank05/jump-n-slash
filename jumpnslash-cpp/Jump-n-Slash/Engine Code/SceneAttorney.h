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
		static void Update(Scene* pScene, float deltaTime);
		static void Draw(Scene* pScene);
	};

	class Commands
	{
	private:
		friend class UpdateObject;
		friend class DrawObject;
		friend class InputObject;
		static void AddCommand(Scene* pScene, Command* pCmd);
	};

	class Update
	{
	private:
		friend class UpdateObject;
		static UpdateManager::UpdateListRef Register(Scene* pScene, UpdateObject* pUpdatable);
		static void Deregister(Scene* pScene, UpdateManager::UpdateListRef deleteRef);
	};

	class Draw
	{
	private:
		friend class DrawObject;
		static DrawManager::DrawListRef Register(Scene* pScene, DrawObject* pDrawable);
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
		static void RegisterMouseCursor(Scene* pScene, InputObject* pInputable);
		static void DeregisterMouseCursor(Scene* pScene, InputObject* pInputable);
	};
};

#endif