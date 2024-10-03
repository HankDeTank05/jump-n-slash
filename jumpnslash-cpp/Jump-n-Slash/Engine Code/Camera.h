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

	void SetCenter(float newCenterX, float newCenterY); // TODO: documentation for Camera::SetCenter
	void Move(float centerDeltaX, float centerDeltaY); // TODO: documentation for Camera::Move
	void SetRotation(float rotationDegrees); // TODO: documentation for Camera::SetRotation
	void Rotate(float degreesDelta); // TODO: documentation for Camera::Rotate
	void SetSize(float viewWidth, float viewHeight); // TODO: documentation for Camera::SetSize
	void Zoom(float relativeScale); // TODO: documentation for Camera::Zoom
	void SetViewport(float screenX, float screenY, float screenWidth, float screenHeight); // TODO: documentation for Camera::SetViewport

private:
	sf::View view;
};

#endif