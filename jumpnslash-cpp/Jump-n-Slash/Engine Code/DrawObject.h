#ifndef DRAW_OBJECT_H
#define DRAW_OBJECT_H

#include <SFML/Graphics.hpp>

#include "RegistrationState.h"
#include "DrawManager.h"

// forward declarations
class DrawRegistrationCommand;
class DrawDeregistrationCommand;

class DrawObject
{
public:
	DrawObject();
	DrawObject(const DrawObject& dob) = delete;
	DrawObject& operator=(const DrawObject& dob) = delete;
	virtual ~DrawObject();

protected:
	/*!
	* \brief	Draw an object.
	* 
	* The function called by the engine to draw an object. This function does nothing by default, and can be overridden by a
	* \c DrawObject -derived class. Any behavior that should occur when drawing an object should go in the overridden function body.
	* 
	* \return	Does not return anything.
	* 
	* \section example Example
	* See the \ref go_drawSystem_exampleCode "Draw System Example Code" section from the
	* \ref CreatingGameObject "Creating a Game Object" tutorial for example code.
	* 
	* \see DrawObject::Render
	* \see DrawObject::RequestDrawRegistration
	* \see DrawObject::RequestDrawDeregistration
	* \see UpdateObject
	* \see InputObject
	* \see AlarmObject
	* \see CollisionObject
	*/
	virtual void Draw();

	/*!
	* \brief	Render a drawable SFML object.
	* 
	* This function renders the \c sf::Drawable object passed to it. The following types are \c sf::Drawable -derived, and therefore may
	* be passed to this function:
	* - \c sf::Shape
	* - \c sf::Sprite
	* - \c sf::Text
	* - \c sf::VertexArray
	* - \c sf::VertexBuffer
	*
	* \note This function is only accessible to classes deriving from \c DrawObject .
	* 
	* \param[in]	drawable	The object to draw.
	* 
	* \return	Does not return anything.
	* 
	* \section example Example
	* The following is an example of how to use the render function.
	* \code
	* // Zelda.h
	* #ifndef ZELDA_H
	* #define ZELDA_H
	* 
	* #include <SFML/Graphics.hpp>
	* 
	* #include "../Engine Code/UpdateObject.h"
	* #include "../Engine Code/DrawObject.h"
	* 
	* class Zelda : public UpdateObject, public DrawObject
	* {
	* public:
	*	Zelda();
	*	Zelda(const Zelda& z) = delete;
	*	Zelda& operator=(const Zelda& z) = delete;
	*	virtual ~Zelda() = default;
	* 
	*	virtual void Update(float deltaTime) override;
	*	virtual void Draw() override;
	* 
	* private:
	*	sf::Sprite* pSprite;
	*	sf::Vector2f pos;
	* }
	* 
	* #endif
	* \endcode
	* \code
	* // Zelda.cpp
	* #include "Zelda.h"
	* 
	* #include "../Engine Code/SpriteManager.h"
	* 
	* Zelda::Zelda()
	*	: pSprite(SpriteManager::GetSprite("zelda sprite")),
	*	pos(2.21f, 19.86f)
	* {
	*	RequestDrawRegistration();
	* }
	* 
	* void Zelda::Update(float deltaTime)
	* {
	*	pSprite->setPosition(pos); // don't forget to set the position before you render!
	* }
	* 
	* void Zelda::Draw()
	* {
	*	Render(*pSprite); // don't forget to dereference the pointer!
	* }
	* \endcode
	* 
	* \see DrawObject::Draw
	* \see DrawObject::RequestDrawRegistration
	* \see DrawObject::RequestDrawDeregistration
	* \see UpdateObject
	* \see InputObject
	* \see AlarmObject
	* \see CollisionObject
	*/
	void Render(sf::Drawable& drawable);

	/*!
	* \brief	Request that the engine draw this object.
	* 
	* Call this function in a \c DrawObject -derived class to let the engine know you would like to begin drawing the object.
	*
	* \note This function is only accessible to classes deriving from \c DrawObject .
	* 
	* \note As the name of this function implies, this puts in a request with the engine for your object to be drawn. The request is
	* processed by the engine on the same frame this function is called, and calls to \c DrawObject::Draw  will begin \b the \b following
	* frame.
	* 
	* \return	Does not return anything.
	* 
	* \section example Example
	* See the \ref go_drawSystem_exampleCode "Draw System Example Code" section from the
	* \ref CreatingGameObject "Creating a Game Object" tutorial for example code.
	* 
	* \see DrawObject::Draw
	* \see DrawObject::Render
	* \see DrawObject::RequestDrawDeregistration
	* \see UpdateObject
	* \see InputObject
	* \see AlarmObject
	* \see CollisionObject
	*/
	void RequestDrawRegistration();
	/*!
	* \brief	Request that the engine stop drawing this object.
	* 
	* Call this function in a \c DrawObject -derived class to let the engien know you would like to stop drawing the object.
	* 
	* \note This function is only accessible to classes deriving from \c DrawObject .
	* 
	* \note As the name of this function implies, this puts in a request with the engine for your object to stop being drawn. The request
	* is processed by the engien on the same frame this fucntion is called, and calls to \c DrawObject::Draw will cease \b the
	* \b following frame.
	* 
	* \return	Does not return anything.
	* 
	* \section example Example
	* See the \ref go_drawSystem_exampleCode "Draw System Example Code" section from the
	* \ref CreatingGameObject "Creating a Game Object" tutorial for example code.
	* 
	* \see DrawObject::Draw
	* \see DrawObject::Render
	* \see DrawObject::RequestDrawRegistration
	* \see UpdateObject
	* \see InputObject
	* \see AlarmObject
	* \see CollisionObject
	*/
	void RequestDrawDeregistration(); 

private:
	friend class DrawObjectAttorney;
	void Register();
	void Deregister();

private:
	RegistrationState regState;
	DrawRegistrationCommand* pRegCmd;
	DrawDeregistrationCommand* pDeregCmd;
	DrawManager::DrawListRef deleteRef;
};

#endif