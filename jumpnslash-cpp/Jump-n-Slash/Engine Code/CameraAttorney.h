#ifndef CAMERA_ATTORNEY_H
#define CAMERA_ATTORNEY_H

#include <SFML/Graphics/View.hpp>

// forward declarations
class Camera;

class CameraAttorney
{
public:
	class View
	{
	private:
		friend class CameraManager;
		static sf::View GetView(Camera* pCam);
	};
};

#endif