#include "Camera.h"

#include "../Game Code/Constants.h"

Camera::Camera(float centerX, float centerY)
	: view(sf::FloatRect(WINDOW_WIDTH, WINDOW_HEIGHT, centerX, centerY))
{
}

Camera::Camera(sf::Vector2f viewSize, sf::Vector2f center)
	: view(viewSize, center)
{
	// do nothing
}

Camera::~Camera()
{
	// do nothing (for now?)
}

void Camera::SetCenter(float newCenterX, float newCenterY)
{
	view.setCenter(newCenterX, newCenterY);
}

void Camera::Move(float centerDeltaX, float centerDeltaY)
{
	view.move(centerDeltaX, centerDeltaY);
}

void Camera::SetRotation(float rotationDegrees)
{
	view.setRotation(rotationDegrees);
}

void Camera::Rotate(float degreesDelta)
{
	view.rotate(degreesDelta);
}

void Camera::SetSize(float viewWidth, float viewHeight)
{
	view.setSize(viewWidth, viewHeight);
}

void Camera::Zoom(float relativeScale)
{
	view.zoom(relativeScale);
}

void Camera::SetViewport(float screenX, float screenY, float screenWidth, float screenHeight)
{
	view.setViewport(sf::FloatRect(screenX, screenY, screenWidth, screenHeight));
}
