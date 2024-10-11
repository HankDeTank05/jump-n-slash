#include "CameraAttorney.h"

#include "Camera.h"

sf::View CameraAttorney::View::GetView(Camera* pCam)
{
    return pCam->GetView();
}
