#ifndef SCENE_MANAGER_ATTORNEY_H
#define SCENE_MANAGER_ATTORNEY_H

// forward declarations
class Scene;

class SceneManagerAttorney
{
public:
	class Initialization
	{
	private:
		friend class JumpSlashEngine;
		static void InitStartScene();
	};
	class GameLoop
	{
	private:
		friend class JumpSlashEngine;
		static void UpdateCurrentScene(float deltaTime);
		static void DrawCurrentScene();
	};
	class SceneChange
	{
	private:
		friend class SceneChangeCommand;
		static void ChangeScene(Scene* pScene);
	};
	class SceneSuspend
	{
	private:
		friend class SceneSuspendCommand;
		static void SuspendCurrentScene(Scene* pForegroundScene);
	};
	class SceneResume
	{
	private:
		friend class SceneResumeCommand;
		static void ResumeSuspendedScene();
	};
	class Termination
	{
	private:
		friend class JumpSlashEngine;
		static void Terminate();
	};
};

#endif