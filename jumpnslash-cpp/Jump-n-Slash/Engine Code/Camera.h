#ifndef CAMERA_H
#define CAMERA_H

#include <SFML/Graphics/View.hpp>
#include <SFML/System/Vector2.hpp>

class Camera
{
public:
	Camera() = delete;
	Camera(float centerX, float centerY);
	Camera(sf::Vector2f size, sf::Vector2f center);
	Camera(const Camera& c) = delete;
	Camera& operator=(const Camera& c) = delete;
	virtual ~Camera();

	void SetCenter(float newCenterX, float newCenterY); // TODO: docs for Camera::SetCenter
	void Move(float centerDeltaX, float centerDeltaY); // TODO: docs for Camera::Move
	void SetRotation(float rotationDegrees); // TODO: docs for Camera::SetRotation
	void Rotate(float degreesDelta); // TODO: docs for Camera::Rotate
	void SetSize(float viewWidth, float viewHeight); // TODO: docs for Camera::SetSize
	void Zoom(float relativeScale); // TODO: docs for Camera::Zoom
	void SetViewport(float screenX, float screenY, float screenWidth, float screenHeight); // TODO: docs for Camera::SetViewport

private:
	sf::View view;
};

#endif