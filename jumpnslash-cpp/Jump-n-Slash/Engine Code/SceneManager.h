#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H

#include <stack>

// forward declarations
class Scene;
class SceneCommand;
class SceneChangeCommand;
class SceneChangeNullCommand;
class SceneSuspendCommand;
class SceneResumeCommand;
class Camera;

class SceneManager // this class is written as a singleton
{
private:
	static SceneManager* pInstance;

	SceneManager();
	SceneManager(const SceneManager& sm) = delete;
	SceneManager& operator=(const SceneManager& sm) = delete;
	virtual ~SceneManager();

	static SceneManager& Instance();

public: // api functions
	// TODO: docs for SceneManager::SetStartScene
	static void SetStartScene(Scene* pStartScene); 
	// TODO: docs for SceneManager::GetCurrentScene
	static Scene* GetCurrentScene(); 
	// TODO: docs for SceneManager::GetCurrentCamera
	static Camera* GetCurrentCamera(); 
	// TODO: docs for SceneManager::SetNextSceneChange
	static void SetNextSceneChange(Scene* pNextScene); 
	// TODO: docs for SceneManager::SetNextSceneSuspend
	static void SetNextSceneSuspend(Scene* pNextScene);
	// TODO: docs for SceneManager::SetNextSceneResume
	static void SetNextSceneResume();

private: // engine-only api functions
	friend class SceneManagerAttorney;
	static void InitStartScene();

	// TODO: docs for SceneManager::ChangeScene
	static void ChangeScene(Scene* pScene);
	// TODO: docs for SceneManager::SuspendCurrentScene
	static void SuspendCurrentScene(Scene* pForegroundScene); 
	// TODO: docs for SceneManager::ResumeSuspendedScene
	static void ResumeSuspendedScene();

	// TODO: docs for SceneManager::UpdateCurrentScene
	static void UpdateCurrentScene(float deltaTime);
	// TODO: docs for SceneManager::DrawCurrentScene
	static void DrawCurrentScene();

	static void Terminate();

private: // private api backend functions
	void privSetStartScene(Scene* pStartScene);
	Scene* privGetCurrentScene();
	Camera* privGetCurrentCamera();
	void privSetNextSceneChange(Scene* pNextScene);
	void privSetNextSceneSuspend(Scene* pNextScene);
	void privSetNextSceneResume();

	void privInitStartScene();

	void privChangeScene(Scene* pScene);
	void privSuspendCurrentScene(Scene* pForegroundScene);
	void privResumeSuspendedScene();

	void privUpdateCurrentScene(float deltaTime);
	void privDrawCurrentScene();

private: // member variables
	Scene* pCurrentScene; // TODO: docs for member variable
	SceneChangeCommand* pChangeCmd; // TODO: docs for member variable
	SceneChangeNullCommand* pDontChangeCmd; // TODO: docs for member variable
	SceneSuspendCommand* pSuspendCmd; // TODO: docs for member variable
	SceneResumeCommand* pResumeCmd; // TODO: docs for member variable
	SceneCommand* pCmdToExe; // TODO: docs for member variable
	std::stack<Scene*> suspensionStack; // TODO: docs for member variable
};

#endif