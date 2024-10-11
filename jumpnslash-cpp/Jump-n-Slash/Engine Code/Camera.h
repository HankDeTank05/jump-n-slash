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
	Camera(sf::View view);
	Camera(const Camera& c) = delete;
	Camera& operator=(const Camera& c) = delete;
	virtual ~Camera();

	void SetCenter(float newCenterX, float newCenterY); // TODO: docs for Camera::SetCenter
	void SetCenter(sf::Vector2f newCenter); // TODO: docs for Camera::SetCenter
	void Move(float centerDeltaX, float centerDeltaY); // TODO: docs for Camera::Move
	sf::Vector2f GetCenter();

	void SetRotation(float rotationDegrees); // TODO: docs for Camera::SetRotation
	void Rotate(float degreesDelta); // TODO: docs for Camera::Rotate
	float GetRotation();

	void SetSize(float newWidth, float newHeight); // TODO: docs for Camera::SetSize
	void SetSize(sf::Vector2f newSize); // TODO:: docs for Camera::SetSize
	void Zoom(float relativeScale); // TODO: docs for Camera::Zoom
	void SetViewport(sf::Vector2f pos, sf::Vector2f size); // TODO: docs for Camera::SetViewport
	void SetViewport(float posX, float posY, sf::Vector2f size); // TODO: docs for Camera::SetViewport
	void SetViewport(sf::Vector2f pos, float width, float height); // TODO: docs for Camera::SetViewport
	void SetViewport(float posX, float posY, float width, float height); // TODO: docs for Camera::SetViewport
	sf::FloatRect GetViewport();

private: // engine-only functions (accessible thru attorney)
	friend class CameraAttorney;
	sf::View GetView();

private:
	sf::View view;
};

#endif