#ifndef SCENE_ATTORNEY_H
#define SCENE_ATTORNEY_H

#include "DrawManager.h"
#include "UpdateManager.h"

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
};

#endif