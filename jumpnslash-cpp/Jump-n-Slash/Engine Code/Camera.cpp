#include "Camera.h"

#include "../Game Code/Constants.h"
#include "EngineAttorney.h"

Camera::Camera(float centerX, float centerY)
	: view(sf::FloatRect(WINDOW_WIDTH, WINDOW_HEIGHT, centerX, centerY))
{
}

Camera::Camera(sf::Vector2f viewSize, sf::Vector2f center)
	: view(viewSize, center)
{
	// do nothing
}

Camera::Camera(sf::View _view)
	: view(_view)
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
	EngineAttorney::GameWindow::SetView(view);
}

void Camera::SetCenter(sf::Vector2f newCenter)
{
	view.setCenter(newCenter);
	EngineAttorney::GameWindow::SetView(view);
}

void Camera::Move(float centerDeltaX, float centerDeltaY)
{
	view.move(centerDeltaX, centerDeltaY);
	EngineAttorney::GameWindow::SetView(view);
}

sf::Vector2f Camera::GetCenter()
{
	return view.getCenter();
}

void Camera::SetRotation(float rotationDegrees)
{
	view.setRotation(rotationDegrees);
	EngineAttorney::GameWindow::SetView(view);
}

void Camera::Rotate(float degreesDelta)
{
	view.rotate(degreesDelta);
	EngineAttorney::GameWindow::SetView(view);
}

float Camera::GetRotation()
{
	return view.getRotation();
}

void Camera::SetSize(float newWidth, float newHeight)
{
	view.setSize(newWidth, newHeight);
	EngineAttorney::GameWindow::SetView(view);
}

void Camera::SetSize(sf::Vector2f newSize)
{
	view.setSize(newSize);
	EngineAttorney::GameWindow::SetView(view);
}

void Camera::Zoom(float relativeScale)
{
	view.zoom(relativeScale);
	EngineAttorney::GameWindow::SetView(view);
}

void Camera::SetViewport(sf::Vector2f pos, sf::Vector2f size)
{
	view.setViewport(sf::FloatRect(pos, size));
	EngineAttorney::GameWindow::SetView(view);
}

void Camera::SetViewport(float posX, float posY, sf::Vector2f size)
{
	view.setViewport(sf::FloatRect(sf::Vector2f(posX, posY), size));
	EngineAttorney::GameWindow::SetView(view);
}

void Camera::SetViewport(sf::Vector2f pos, float width, float height)
{
	view.setViewport(sf::FloatRect(pos, sf::Vector2f(width, height)));
	EngineAttorney::GameWindow::SetView(view);
}

void Camera::SetViewport(float posX, float posY, float width, float height)
{
	view.setViewport(sf::FloatRect(posX, posY, width, height));
	EngineAttorney::GameWindow::SetView(view);
}

sf::FloatRect Camera::GetViewport()
{
	return view.getViewport();
}

sf::View Camera::GetView()
{
	return view;
}
