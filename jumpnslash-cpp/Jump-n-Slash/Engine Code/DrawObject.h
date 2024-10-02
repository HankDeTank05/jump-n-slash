#ifndef DRAW_OBJECT_H
#define DRAW_OBJECT_H

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
	* \see DrawObject::RequestDrawRegistration
	* \see DrawObject::RequestDrawDeregistration
	* \see UpdateObject
	* \see InputObject
	* \see AlarmObject
	* \see CollisionObject
	*/
	virtual void Draw();

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