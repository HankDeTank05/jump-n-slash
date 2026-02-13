#ifndef DRAW_OBJECT_H
#define DRAW_OBJECT_H

// library includes
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transform.hpp>
#include <SFML/Graphics/Vertex.hpp>

// engine includes
#include "RegistrationState.h"
#include "DrawManager.h"

// forward declarations
class DrawRegistrationCommand;
class DrawDeregistrationCommand;
class Sprite;

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
	// TODO: docs for DrawObject::Render(sprite)
	void Render(Sprite* pSprite);
	/*!
	* \brief	Render a SFML drawable with a transform.
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
	* \param[in]	tform	A \c sf::Transform. 
	* 
	* \return	Does not return anything.
	* 
	* \see DrawObject::Draw
	* \see DrawObject::RequestDrawRegistration
	* \see DrawObject::RequestDrawDeregistration
	* \see UpdateObject
	* \see InputObject
	* \see AlarmObject
	* \see CollisionObject
	*/
	void Render(const sf::Drawable& drawable, const sf::Transform& tform);
	/*!
	* \brief	Render a primitive by passing in a vertex array.
	*
	* \note This function is only accessible to classes deriving from \c DrawObject .
	* 
	* \note Vertices are rendered with \c sf::Lines .
	*
	* \param[in]	array	An sf::Vertex array. 
	* 
	* \param[in]	count	Number of vertices in the array as an integer. 
	*
	* \return	Does not return anything.
	*
	* \see DrawObject::Draw
	* \see DrawObject::RequestDrawRegistration
	* \see DrawObject::RequestDrawDeregistration
	* \see UpdateObject
	* \see InputObject
	* \see AlarmObject
	* \see CollisionObject
	*/
	void Render(sf::Vertex* array, int vtexCount);

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
	* is processed by the engine on the same frame this fucntion is called, and calls to \c DrawObject::Draw will cease \b the
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

	//void DrawChildren();

private:
	/*!
	* \brief	This \c DrawObject 's currrent state in the draw system.
	* 
	* An enum representing this \c DrawObjects current state within the draw system, 
	* either Pending Registration, Currently Registered, Pending Deregistration, or Currently Deregistered. 
	* 
	* \see	DrawManager
	*/
	RegistrationState regState;
	/*!
	* \brief	This \c DrawObject 's registration command.
	* 
	* A command class for use with the \c SceneManager to allow for the \c DrawObject 
	* to be registered to the draw list during the right point during a frame. 
	* 
	* \see	SceneManager
	* \see	DrawManager
	*/
	DrawRegistrationCommand* pRegCmd;
	/*!
	* \brief	This \c DrawObject 's deregistration command.
	*
	* A command class for use with the \c SceneManager to allow for the \c DrawObject
	* to be deregistered from the draw list during the right point during a frame. 
	*
	* \see	SceneManager
	* \see	DrawManager
	*/
	DrawDeregistrationCommand* pDeregCmd;
	/*!
	* \brief	An iterator for this \c DrawObject 's position in the draw list. 
	* 
	* An iterator to the \c DrawManager::DrawList pointing to this \c DrawObject 's 
	* position in the list upon registration for use when deleting this object from the draw list. 
	* 
	* \see DrawManager
	*/
	DrawManager::DrawListRef deleteRef;
	//SceneGraphNode* pNode;
};

#endif