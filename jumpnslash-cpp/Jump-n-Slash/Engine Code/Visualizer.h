#ifndef VISUALIZER_H
#define VISUALIZER_H

#include <list>

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/VertexArray.hpp>

#include "DrawObject.h"

#include "../Game Code/Constants.h"

// forward declarations
class VisualizerCommand;

class Visualizer : public DrawObject // this class is written as a singleton
{
private:
	static Visualizer* pInstance;

	Visualizer();
	Visualizer(const Visualizer& v) = delete;
	Visualizer& operator=(const Visualizer& v) = delete;
	virtual ~Visualizer();

	static Visualizer& Instance();

	using VizCmdList = std::list<VisualizerCommand*>;

public: // public api functions
	/*!
	* \brief	Visualize a point in space for debugging.
	* 
	* This function allows you visualize a world-space position by drawing a dot on screen.
	* 
	* \note		This function may be called anywhere, by anyone. This function does not need to be called inside a draw
	* function, or by an object deriving from DrawObject.
	* 
	* \param[in]	pos		The world-space position at which a dot should be drawn.
	* \param[in]	color	The color of the dot to be drawn (Cyan by default).
	* 
	* \return	Does not return anything.
	* 
	* \section example1 Example 1
	* \code
	* // Player.cpp
	* #include "Player.h"
	* #include "../Engine Code/Visualizer.h"
	* 
	* void Player::Update(float deltaTime)
	* {
	*	Visualizer::VisualizePoint(this->pos);
	* }
	* \endcode
	* 
	* \section example2 Example 2
	* \code
	* // Player.cpp
	* #include "Player.h"
	* #include "../Engine Code/Visualizer.h"
	* 
	* void Player::Update(float deltaTime)
	* {
	*	Visualizer::VisualizePoint(this->pos, sf::Color::Red);
	* }
	* \endcode
	* 
	* \see	Visualizer::VisualizePoint(float x, float y, sf::Color color)
	* 
	* \see	Visualizer::VisualizeCircle
	* \see	Visualizer::VisualizeRect
	* \see	Visualizer::VisualizeSegment
	* \see	Visualizer::VisualizeRay
	* \see	Visualizer::VisualizeLine
	* \see	Visualizer::VisualizeText
	*/
	static void VisualizePoint(sf::Vector2f pos, sf::Color color = VIZ_DEFAULT_COLOR);
	/*!
	* \brief	Visualize a point in space for debugging.
	*
	* This function allows you visualize a world-space position by drawing a dot on screen.
	*
	* \note		This function may be called anywhere, by anyone. This function does not need to be called inside a draw
	* function, or by an object deriving from DrawObject.
	*
	* \param[in]	x		The x-coordinate of the world-space position at which a dot should be drawn.
	* \param[in]	y		The y-coordinate of the world-space position at which a dot should be drawn.
	* \param[in]	color	The color of the dot to be drawn (Cyan by default).
	*
	* \return	Does not return anything.
	*
	* \section example1 Example 1
	* \code
	* // Player.cpp
	* #include "Player.h"
	* #include "../Engine Code/Visualizer.h"
	*
	* void Player::Update(float deltaTime)
	* {
	*	float xPos = 420.69f;
	*	float yPos = 96.024f;
	*	Visualizer::VisualizePoint(xPos, yPos);
	* }
	* \endcode
	*
	* \section example2 Example 2
	* \code
	* // Player.cpp
	* #include "Player.h"
	* #include "../Engine Code/Visualizer.h"
	*
	* void Player::Update(float deltaTime)
	* {
	*	float xPos = 420.69f;
	*	float yPos = 96.024f;
	*	Visualizer::VisualizePoint(xPos, yPos, sf::Color::Red);
	* }
	* \endcode
	*
	* \see	Visualizer::VisualizePoint(sf::Vector2f pos, sf::Color color)
	*
	* \see	Visualizer::VisualizeCircle
	* \see	Visualizer::VisualizeRect
	* \see	Visualizer::VisualizeSegment
	* \see	Visualizer::VisualizeRay
	* \see	Visualizer::VisualizeLine
	* \see	Visualizer::VisualizeText
	*/
	static void VisualizePoint(float x, float y, sf::Color color = VIZ_DEFAULT_COLOR);

	/*!
	* \brief	Visualize a circle for debugging.
	* 
	* This function allows you to visualize a circle in world-space for debugging purposes.
	* 
	* \param[in]	pos				The position of the center of the circle in world-space.
	* \param[in]	radius			The radius of the circle, in pixels.
	* \param[in]	color			The color of the circle to be drawn (Cyan by default).
	* \param[in]	showCenter		Whether or not to visualize the center point of the circle (\c true by default).
	* 
	* \return	Does not return anything.
	* 
	* \section example1 Example 1
	* \code
	* // Player.cpp
	* #include "Player.h"
	* #include "../Engine Code/Visualizer.h"
	* 
	* void Player::Update(float deltaTime)
	* {
	*	// visualize a distance from the center of the player sprite
	*	float distance = 100.f;
	*	Visualizer::VisualizeCircle(pos + sf::Vector2f(TILE_SIZE_F/2.f, TILE_SIZE_F/2.f), distance);
	* }
	* \endcode
	*/
	static void VisualizeCircle(sf::Vector2f pos, float radius, sf::Color color = VIZ_DEFAULT_COLOR, bool showCenter = true); // TODO: docs for Visualizer::VisualizeCircle

	static void VisualizeRect(sf::Vector2f pos, sf::Vector2f size, sf::Color color = VIZ_DEFAULT_COLOR); // TODO: docs for Visualizer::VisualizeRect
	
	static void VisualizeSegment(sf::Vector2f pos0, sf::Vector2f pos1, sf::Color color = VIZ_DEFAULT_COLOR, bool visualizeEndpoints = false); // TODO: docs for Visualizer::VisualizeSegment

	static void VisualizeRay(sf::Vector2f pos, sf::Vector2f dir, sf::Color color = VIZ_DEFAULT_COLOR);

	static void VisualizeLine(sf::Vector2f pos0, sf::Vector2f pos1, sf::Color color = VIZ_DEFAULT_COLOR);
	
	// TODO: add an option for a backdrop behind the text in case it is difficult to read

	static void VisualizeText(sf::String str, sf::Vector2f pos, sf::Color color = VIZ_DEFAULT_COLOR, int sizeInPix = VIZ_DEFAULT_TEXT_SIZE); // TODO: docs for Visualizer::VisualizeText
	static void VisualizeText(sf::String str, sf::Vector2i pos, sf::Color color = VIZ_DEFAULT_COLOR, int sizeInPix = VIZ_DEFAULT_TEXT_SIZE); // TODO: docs for Visualizer::VisualizeText

private: // engine-only api functions
	friend class VisualizerAttorney;
	static void ProcessCommands();

	static void ShowPoint(sf::Vector2f pos, sf::Color color);
	static void ShowCircle(sf::Vector2f pos, float radius, sf::Color color, bool showCenter);
	static void ShowRect(sf::Vector2f pos, sf::Vector2f size, sf::Color color);
	static void ShowSegment(sf::Vector2f pos0, sf::Vector2f pos1, sf::Color color);
	static void ShowText(sf::String str, sf::Vector2f pos, sf::Color color, int sizeInPix);

	static void Terminate();

private: // private api backend functions
	void privVisualizePoint(sf::Vector2f pos, sf::Color color);
	void privVisualizeCircle(sf::Vector2f pos, float radius, sf::Color color, bool showCenter);
	void privVisualizeRect(sf::Vector2f pos, sf::Vector2f size, sf::Color color);
	void privVisualizeSegment(sf::Vector2f pos0, sf::Vector2f pos1, sf::Color color, bool visualizeEndpoints);
	void privVisualizeText(sf::String str, sf::Vector2f pos, sf::Color color, int sizeInPix);

	void privProcessCommands();

	void privShowPoint(sf::Vector2f pos, sf::Color color);
	void privShowCircle(sf::Vector2f pos, float radius, sf::Color color, bool showCenter);
	void privShowRect(sf::Vector2f pos, sf::Vector2f size, sf::Color color);
	void privShowSegment(sf::Vector2f pos0, sf::Vector2f pos1, sf::Color color);
	void privShowText(sf::String str, sf::Vector2f pos, sf::Color color, int sizeInPix);

private: // member variables
	VizCmdList cmdList;
	sf::CircleShape* pCircle;
	sf::RectangleShape* pRect;
	sf::Text* pText;
};

#endif