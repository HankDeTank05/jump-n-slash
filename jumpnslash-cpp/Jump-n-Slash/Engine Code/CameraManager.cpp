#include "CameraManager.h"

#include <SFML/Window.hpp>

#include "EngineAttorney.h"
#include "CameraAttorney.h"
#include "Camera.h"

CameraManager::CameraManager()
	: pDefaultCam(new Camera(EngineAttorney::GameWindow::GetWindow().getDefaultView())),
	pCurrentCam(pDefaultCam)
{
	// do nothing
}

CameraManager::~CameraManager()
{
	delete pDefaultCam;
}

void CameraManager::SetCurrentCamera(Camera* pCam)
{
	pCurrentCam = pCam;
	EngineAttorney::GameWindow::GetWindow().setView(CameraAttorney::View::GetView(pCurrentCam));
}

Camera* CameraManager::GetCurrentCamera()
{
	return pCurrentCam;
}
