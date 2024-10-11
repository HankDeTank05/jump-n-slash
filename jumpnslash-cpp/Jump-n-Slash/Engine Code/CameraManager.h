#ifndef CAMERA_MANAGER_H
#define CAMERA_MANAGER_H

// forward declarations
class Camera;

class CameraManager
{
public:
	CameraManager();
	CameraManager(const CameraManager& cm) = delete;
	CameraManager& operator=(const CameraManager& cm) = delete;
	virtual ~CameraManager();

	void SetCurrentCamera(Camera* pCam);
	Camera* GetCurrentCamera();

private:
	Camera* pDefaultCam;
	Camera* pCurrentCam;
};

#endif