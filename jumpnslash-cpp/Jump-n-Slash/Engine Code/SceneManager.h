#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H

// forward declarations
class Scene;
class SceneCommand;
class SceneChangeCommand;
class SceneChangeNullCommand;
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
	static void SetStartScene(Scene* pStartScene); // TODO: docs for SceneManager::SetStartScene
	static Scene* GetCurrentScene(); // TODO: docs for SceneManager::GetCurrentScene
	static Camera* GetCurrentCamera(); // TODO: docs for SceneManager::GetCurrentCamera
	static void SetNextScene(Scene* pNextScene); // TODO: docs for SceneManager::SetNextScene

private: // engine-only api functions
	friend class SceneManagerAttorney;
	static void InitStartScene();

	static void ChangeScene(Scene* pScene);

	static void UpdateCurrentScene(float deltaTime);
	static void DrawCurrentScene();

	static void Terminate();

private: // private api backend functions
	void privSetStartScene(Scene* pStartScene);
	Scene* privGetCurrentScene();
	Camera* privGetCurrentCamera();
	void privSetNextScene(Scene* pNextScene);

	void privInitStartScene();

	void privChangeScene(Scene* pScene);

	void privUpdateCurrentScene(float deltaTime);
	void privDrawCurrentScene();

private: // member variables
	Scene* pCurrentScene;
	SceneChangeCommand* pChangeCmd;
	SceneChangeNullCommand* pDontChangeCmd;
	SceneCommand* pCmdToExe;
};

#endif