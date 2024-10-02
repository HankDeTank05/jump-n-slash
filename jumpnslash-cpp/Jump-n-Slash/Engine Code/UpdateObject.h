#ifndef UPDATE_OBJECT_H
#define UPDATE_OBJECT_H

#include "RegistrationState.h"
#include "UpdateManager.h"

// forward declarations
class UpdateRegistrationCommand;
class UpdateDeregistrationCommand;

class UpdateObject
{
public:
	UpdateObject();
	UpdateObject(const UpdateObject& uo) = delete;
	UpdateObject& operator=(const UpdateObject& uo) = delete;
	virtual ~UpdateObject();

protected:
	/*!
	* \brief	Update an object.
	* 
	* The function called by the engine to update an object. This function does nothing by default, and can be overridden by an
	* \c UpdateObject -derived class. Any behavior that should occur when updating an object should go in the overridden function
	* body.
	* 
	* \param[in]	deltaTime	The amount of time since the previous frame, in seconds.
	* 
	* \note This engine is not framerate-controlled! A frame will render as soon as it can, meaning the time between frames is unknown.
	* Any behavior (such as movement) which occurs over time needs to be multiplied by the provided \c deltaTime argument in order to
	* appear normal!
	* 
	* \return	Does not return anything.
	* 
	* \section example Example
	* See the \ref go_updateSystem_exampleCode "Update System Example Code" section from the
	* \ref CreatingGameObject "Creating a Game Object" tutorial for example code.
	* 
	* \see UpdateObject::RequestUpdateRegistration
	* \see UpdateObject::RequestUpdateDeregistration
	* \see DrawObject
	* \see InputObject
	* \see AlarmObject
	* \see CollisionObject
	*/
	virtual void Update(float deltaTime);

	/*!
	* \brief Request that the engine update this object.
	* 
	* Call this function in an \c UpdateObject -derived class to let the engine know you would like to begin updating the object.
	* 
	* \note This function is only accessible to classes deriving from \c UpdateObject .
	* 
	* \note As the name of the function implies, this puts in a request with the engine for your object to be updated. The request is
	* processed by the engine on the same frame this function is called, and calls to \c UpdateObject::Update will begin \b the 
	* \b following frame.
	* 
	* \return	Does not return anything.
	* 
	* \section example Example
	* See the \ref go_updateSystem_exampleCode "Update System Example Code" section from the
	* \ref CreatingGameObject "Creating a Game Object" tutorial for example code.
	* 
	* \see UpdateObject::Update
	* \see UpdateObject::RequestUpdateDeregistration
	* \see DrawObject
	* \see InputObject
	* \see AlarmObject
	* \see CollisionObject
	*/
	void RequestUpdateRegistration();
	/*!
	* \brief Request that the engine stop updating this object.
	* 
	* Call this function in an \c UpdateObject -derived class to let the engine know you would like to stop updating the object.
	* 
	* \note This function is only accessible to classes deriving from \c UpdateObject .
	* 
	* \note As the name of the function implies, this puts in a request with the engine for your object to stop being updated. The
	* request is processed by the engine on the same frame this function is called, and calls to \c UpdateObject::Update will cease
	* \b the \b following frame.
	* 
	* \return	Does not return anything.
	* 
	* \section example Example
	* See the \ref go_updateSystem_exampleCode "Update System Example Code" section from the
	* \ref CreatingGameObject "Creating a Game Object" tutorial for example code.
	* 
	* \see UpdateObject::Update
	* \see UpdateObject::RequestUpdateRegistration
	* \see DrawObject
	* \see InputObject
	* \see AlarmObject
	* \see CollisionObject
	*/
	void RequestUpdateDeregistration();

private:
	friend class UpdateObjectAttorney;
	void Register();
	void Deregister();

private:
	RegistrationState regState; // TODO: documentation for member variable
	UpdateRegistrationCommand* pRegCmd; // TODO: documentation for member variable
	UpdateDeregistrationCommand* pDeregCmd; // TODO: documentation for member variable
	UpdateManager::UpdateListRef deleteRef; // TODO: documentation for member variable
};

#endif