#ifndef INPUT_OBJECT_H
#define INPUT_OBJECT_H

#include <map>

#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/Joystick.hpp>

#include "InputEvent.h"
#include "RegistrationState.h"

// forward declarations
class KeyRegistrationCommand;
class KeyDeregistrationCommand;
class MouseBtnRegistrationCommand;
class MouseBtnDeregistrationCommand;
class MouseCursorRegistrationCommand;
class MouseCursorDeregistrationCommand;

class InputObject
{
public:
	InputObject();
	InputObject(const InputObject& io) = delete;
	InputObject& operator=(const InputObject& io) = delete;
	virtual ~InputObject();

protected:
	friend class InputObjectAttorney;

	/*!
	* \brief	Do something when a key is pressed.
	* 
	* The function called by the engine whenever a key registered for key press events is pressed. It is only called on the first frame
	* the key is held down. This function does nothing by default, and can be overridden by an \c InputObject -derived class. Any behavior
	* that should occur when a key is pressed should go in the overridden function body.
	* 
	* \param[in]	key		The key which was pressed.
	* 
	* \return	Does not return anything.
	* 
	* \section example Example
	* See the \ref go_inputSystem_exampleCode "Input System Example Code" section from the
	* \ref CreatingGameObject "Creating a Game Object" tutorial for example code.
	* 
	* \see InputObject::KeyReleased
	* \see InputObject::RequestKeyRegistration
	* \see InputObject::RequestKeyDeregistration
	* \see InputObject::MouseBtnPressed
	* \see InputObject::MouseBtnReleased
	* \see InputObject::RequestMouseBtnRegistration
	* \see InputObject::RequestMouseBtnDeregistration
	* \see InputObject::MouseCursorMoved
	* \see InputObject::RequestMouseCursorRegistration
	* \see InputObject::RequestMouseCursorDeregistration
	* \see UpdateObject
	* \see DrawObject
	* \see AlarmObject
	* \see CollisionObject
	*/
	virtual void KeyPressed(sf::Keyboard::Key key);
	/*!
	* \brief	Do something when a key is released.
	* 
	* The function called by the engine whenever a key registered for key release events is released. It is only called on the first frame
	* the key is released. This function does nothing by default, and can be overridden by an \c InputObject -derived class. Any behavior
	* that should occur when a key is pressed should go in the overridden function body.
	* 
	* \param[in]	key		The key which was released.
	* 
	* \return Does not return anything.
	* 
	* \section example Example
	* See the \ref go_inputSystem_exampleCode "Input System Example Code" section from the
	* \ref CreatingGameObject "Creating a Game Object" tutorial for example code.
	* 
	* \see InputObject::KeyPressed
	* \see InputObject::RequestKeyRegistration
	* \see InputObject::RequestKeyDeregistration
	* \see InputObject::MouseBtnPressed
	* \see InputObject::MouseBtnReleased
	* \see InputObject::RequestMouseBtnRegistration
	* \see InputObject::RequestMouseBtnDeregistration
	* \see InputObject::MouseCursorMoved
	* \see InputObject::RequestMouseCursorRegistration
	* \see InputObject::RequestMouseCursorDeregistration
	* \see UpdateObject
	* \see DrawObject
	* \see AlarmObject
	* \see CollisionObject
	*/
	virtual void KeyReleased(sf::Keyboard::Key key);

	/*!
	* \brief	Do something when a mouse button is pressed.
	* 
	* The function called by the engine whenever a mouse button registered for mouse button press events is pressed. It is only called on
	* the first frame the button is held down. This function does nothing by default, and can be overridden by an \c InputObject -derived
	* class. Any behavior that should occur when a key is pressed should go in the overridden function body.
	* 
	* \param[in]	btn		The button which was pressed.
	* 
	* \return	Does not return anything.
	* 
	* \section example Example
	* \code
	* // DoomGuy.h
	* #ifndef DOOM_GUY_H
	* #define DOOM_GUY_H
	* 
	* #include "../Engine Code/InputObject.h"
	* 
	* class DoomGuy : public InputObject
	* {
	* public:
	*	DoomGuy();
	*	DoomGuy(const DoomGuy& dg) = delete;
	*	DoomGuy& operator=(const DoomGuy& dg) = delete;
	*	virtual ~DoomGuy();
	* 
	*	// ... some functions ... //
	* 
	*	virtual void MouseBtnPressed(sf::Mouse::Button btn) override;
	* 
	*	// ... some more functions ... //
	* 
	* private:
	*	void Shoot();
	* 
	* private:
	*	// ... member variables ... //
	* }
	* 
	* #endif
	* \endcode
	* \code
	* // DoomGuy.cpp
	* #include "DoomGuy.h"
	* 
	* DoomGuy::DoomGuy()
	* {
	*	// ... some code ... //
	*	RequestMouseBtnRegistration(sf::Mouse::Left, MouseEvent::BtnPress);
	* }
	* 
	* DoomGuy::~DoomGuy()
	* {
	*	// ... some code ... //
	*	RequestMouseBtnDeregistration(sf::Mouse::Left, MouseEvent::BtnPress);
	* }
	* 
	* void DoomGuy::MouseBtnPressed(sf::Mouse::Button btn)
	* {
	*	switch(btn)
	*	{
	*	case sf::Mouse::Left:
	*		this->Shoot();
	*		break;
	*	}
	* }
	* \endcode
	* 
	* \see InputObject::KeyPressed
	* \see InputObject::KeyReleased
	* \see InputObject::RequestKeyRegistration
	* \see InputObject::RequestKeyDeregistration
	* \see InputObject::MouseBtnReleased
	* \see InputObject::RequestMouseBtnRegistration
	* \see InputObject::RequestMouseBtnDeregistration
	* \see InputObject::MouseCursorMoved
	* \see InputObject::RequestMouseCursorRegistration
	* \see InputObject::RequestMouseCursorDeregistration
	* \see UpdateObject
	* \see DrawObject
	* \see AlarmObject
	* \see CollisionObject
	*/
	virtual void MouseBtnPressed(sf::Mouse::Button btn);
	/*!
	* \brief	Do something when a mouse button is released.
	* 
	* The function called by the engine whenever a mouse button registered for mouse button release events is released. It is only called
	* on the first frame the button is released. This function does nothing by default, and can be overridden by an \c InputObject 
	* -derived class. Any behavior that should occur when a key is pressed should go in the overridden function body.
	* 
	* \param[in]	btn		The button which was released
	* 
	* \return Does not return anything.
	* 
	* \section example Example
	* \code
	* // DoomGuy.h
	* #ifndef DOOM_GUY_H
	* #define DOOM_GUY_H
	* 
	* #include "../Engine Code/UpdateObject.h"
	* #include "../Engine Code/InputObject.h"
	* 
	* class DoomGuy : public InputObject
	* {
	* public:
	*	DoomGuy();
	*	DoomGuy(const DoomGuy& dg) = delete;
	*	DoomGuy& operator=(const DoomGuy& dg) = delete;
	*	virtual ~DoomGuy();
	* 
	*	// ... some functions ... //
	* 
	*	virtual void Update(float deltaTime) override;
	* 
	*	virtual void MouseBtnPressed(sf::Mouse::Button btn) override;
	*	virtual void MouseBtnReleased(sf::Mouse::Button btn) override;
	* 
	*	// ... some more functions ... //
	* 
	* private:
	*	void Shoot();
	* 
	* private:
	*	// ... member variables ... //
	*	bool currentlyShooting;
	* }
	* 
	* #endif
	* \endcode
	* \code
	* // DoomGuy.cpp
	* #include "DoomGuy.h"
	* 
	* DoomGuy::DoomGuy()
	* {
	*	// ... some code ... //
	*	RequestMouseBtnRegistration(sf::Mouse::Left, MouseEvent::BtnPress);
	*	RequestMouseBtnRegistration(sf::Mouse::Left, MouseEvent::BtnRelease);
	* }
	* 
	* DoomGuy::~DoomGuy()
	* {
	*	// ... some code ... //
	*	RequestMouseBtnDeregistration(sf::Mouse::Left, MouseEvent::BtnPress);
	*	RequestMouseBtnDeregistration(sf::Mouse::Left, MouseEvent::BtnRelease);
	* }
	* 
	* void DoomGuy::Update(float deltaTime)
	* {
	*	if (currentlyShooting)
	*	{
	*		this->Shoot();
	*	}
	* }
	* 
	* void DoomGuy::MouseBtnPressed(sf::Mouse::Button btn)
	* {
	*	switch(btn)
	*	{
	*	case sf::Mouse::Left:
	*		this->currentlyShooting = true;
	*		break;
	*	}
	* }
	* 
	* void DoomGuy::MouseBtnReleased(sf::Mouse::Button btn)
	* {
	*	switch(btn)
	*	{
	*	case sf::Mouse::Left:
	*		this->currentlyShooting = false;
	*		break;
	*	}
	* }
	* \endcode
	* 
	* \see InputObject::KeyPressed
	* \see InputObject::KeyReleased
	* \see InputObject::RequestKeyRegistration
	* \see InputObject::RequestKeyDeregistration
	* \see InputObject::MouseBtnPressed
	* \see InputObject::RequestMouseBtnRegistration
	* \see InputObject::RequestMouseBtnDeregistration
	* \see InputObject::MouseCursorMoved
	* \see InputObject::RequestMouseCursorRegistration
	* \see InputObject::RequestMouseCursorDeregistration
	* \see UpdateObject
	* \see DrawObject
	* \see AlarmObject
	* \see CollisionObject
	*/
	virtual void MouseBtnReleased(sf::Mouse::Button btn);
	/*!
	* \brief	Do something when the mouse cursor is moved.
	* 
	* The function called by the engine whenever the mouse cursor is moved (as long as the object has registered for mouse cursor inputs).
	* It is only called on frames where the current mouse position is different from its position the previous frame. This function does
	* nothing by default, and can be overridden by an \c InputObject -derived class. Any behavior that should occur when the mouse cursor
	* moves should go in the overridden function body.
	* 
	* \note This engine is not framerate-controlled! A frame will render as soon as it can, meaning the amount of time between frames can
	* be extremely short. Because of this, a mouse movement that appears smooth and consistent may have one or more frames where no mouse
	* movement has been detected. It is recommended that you save the \c pos and/or \c posDelta values for accumulation/calculation in the
	* UpdateObject::Update function if you would like to read mouse movements over a period longer than a single frame.
	* 
	* \param[in]	pos			The current position of the mouse cursor, in pixels, relative to the top-left corner of the game window.
	* \param[in]	posDelta	The change in mouse position between the previous frame and the current frame.
	* 
	* \return	Does not return anything.
	* 
	* \section example Example
	* TODO: docs for InputObject::MouseCursorMoved needs example code
	* 
	* \see InputObject::KeyPressed
	* \see InputObject::KeyReleased
	* \see InputObject::RequestKeyRegistration
	* \see InputObject::RequestKeyDeregistration
	* \see InputObject::MouseBtnPressed
	* \see InputObject::MouseBtnReleased
	* \see InputObject::RequestMouseBtnRegistration
	* \see InputObject::RequestMouseBtnDeregistration
	* \see InputObject::RequestMouseCursorRegistration
	* \see InputObject::RequestMouseCursorDeregistration
	* \see UpdateObject
	* \see DrawObject
	* \see AlarmObject
	* \see CollisionObject
	*/
	virtual void MouseCursorMoved(sf::Vector2i pos, sf::Vector2i delta);
	// TODO: figure out mouse wheel inputs

	// TODO: figure out gamepad button inputs
	// TODO: figure out gamepad stick inputs

	/*!
	* /brief	Request that the engine read for key events.
	* 
	* Call this function in an \c InputObject -derived class to let the engine know you would like it to listen for a certain key's
	* specified input event. You must provide the key you want to receive input from, and an event which should be listened for.
	* 
	* \note This function is only accessible to classes deriving \c InputObject .
	* 
	* \param[in]	key				The key you would like to receive input from. Type \c sf::Keyboard:: and IntelliSense will provide you
	* with a list of available keys.
	* \param[in]	eventToReg		The event you would like the engine to listen for. Your options are \c KeyEvent::Press and
	* \c KeyEvent::Release .
	* 
	* \note As the name of this function implies, this puts in a request for the engine to listen for the given key's specified input
	* event. The request is processed on the same frame this function is called, and calls to either \c InputObject::KeyPressed or
	* \c InputObject::KeyReleased can begin as soon as \b the \b following frame.
	* 
	* \return	Does not return anything.
	* 
	* \section example Example
	* See the \ref go_inputSystem_exampleCode "Input System Example Code" section from the
	* \ref CreatingGameObject "Creating a Game Object" tutorial for example code.
	* 
	* \see InputObject::KeyPressed
	* \see InputObject::KeyReleased
	* \see InputObject::RequestKeyDeregistration
	* \see InputObject::MouseBtnPressed
	* \see InputObject::MouseBtnReleased
	* \see InputObject::RequestMouseBtnRegistration
	* \see InputObject::RequestMouseBtnDeregistration
	* \see InputObject::MouseCursorMoved
	* \see InputObject::RequestMouseCursorRegistration
	* \see InputObject::RequestMouseCursorDeregistration
	* \see UpdateObject
	* \see DrawObject
	* \see AlarmObject
	* \see CollisionObject
	* 
	*/
	void RequestKeyRegistration(sf::Keyboard::Key key, KeyEvent eventToReg); 
	/*!
	* \brief	Request that the engine stop reading for key events.
	* 
	* Call this function in an \c InputObject -derived class to let the engine know you would like it to stop listening for a certain
	* key's specified input event. You must provide the key you want to stop receiving input from, and the event which should no longer
	* be listened for.
	* 
	* \note This function is only accessible to classes deriving from \c InputObject .
	* 
	* \param[in]	key				The key you would like to stop receiving input from. Type \c sf::Keyboard:: and IntelliSense will
	* provide you a list of available keys.
	* \param[in]	eventToDereg	The event you would like the engine to stop listening for. Your options are \c KeyEvent::Press and
	* \c KeyEvent::Release .
	* 
	* \note As the name of this function implies, this puts in a request for the engine to stop listening for the given key's specified
	* input event. The request is processed on the same frame this function is called, and calls to either \c InputObject::KeyPressed or
	* \c InputObject::KeyReleased will cease \b the \b following frame.
	* 
	* \return	Does not return anything.
	* 
	* \section example Example
	* See the \ref go_inputSystem_exampleCode "Input System Example Code" section from the
	* \ref CreatingGameObject "Creating a Game Object" tutorial for example code.
	* 
	* \see InputObject::KeyPressed
	* \see InputObject::KeyReleased
	* \see InputObject::RequestKeyRegistration
	* \see InputObject::MouseBtnPressed
	* \see InputObject::MouseBtnReleased
	* \see InputObject::RequestMouseBtnRegistration
	* \see InputObject::RequestMouseBtnDeregistration
	* \see InputObject::MouseCursorMoved
	* \see InputObject::RequestMouseCursorRegistration
	* \see InputObject::RequestMouseCursorDeregistration
	* \see UpdateObject
	* \see DrawObject
	* \see AlarmObject
	* \see CollisionObject
	*/
	void RequestKeyDeregistration(sf::Keyboard::Key key, KeyEvent eventToDereg); 

	/*!
	* \brief	Request that the engine read for mouse button events.
	* 
	* Call this function in an \c InputObject -derived class to let the engine know you would like it to listen for a certain mouse
	* button's specified input event. You must provide the mouse button you want to receive input from, and an event which should be
	* listened for.
	* 
	* \note This function is only accessible to classes deriving from \c InputObject .
	* 
	* \param[in]	btn				The mouse button you would like to receive input from. Type \c sf::Mouse:: and IntelliSense will
	* provide you with a list of available mouse buttons.
	* \param[in]	eventToReg		The event you would like the engine to listen for. Your options are \c MouseEvent::BtnPress and
	* \c MouseEvent::BtnRelease .
	* 
	* \note As the name of this function implies, this puts in a request for the engine to listen for the given mouse button's specified
	* input event. The request is processed on the same frame this function is called, and calls to either \c InputObject::MouseBtnPressed
	* or \c InputObject::MouseBtnReleased can begin as soon as \b the \b following frame.
	* 
	* \return	Does not return anything.
	* 
	* \section example Example
	* See the example code for InputObject::MouseBtnPressed for usage example.
	* 
	* \see InputObject::KeyPressed
	* \see InputObject::KeyReleased
	* \see InputObject::RequestKeyRegistration
	* \see InputObject::RequestKeyDeregistration
	* \see InputObject::MouseBtnPressed
	* \see InputObject::MouseBtnReleased
	* \see InputObject::RequestMouseBtnDeregistration
	* \see InputObject::MouseCursorMoved
	* \see InputObject::RequestMouseCursorRegistration
	* \see InputObject::RequestMouseCursorDeregistration
	* \see UpdateObject
	* \see DrawObject
	* \see AlarmObject
	* \see CollisionObject
	*/
	void RequestMouseBtnRegistration(sf::Mouse::Button btn, MouseEvent eventToReg); 
	/*!
	* \brief	Request that the engine stop reading for mouse button events.
	* 
	* Call this function in an \c InputObject -derived class to let the engine know you would like it to stop listening for a certain
	* mouse button's specified input event. You must provide the mouse button you want to stop receiving input from, and the event which
	* should no longer be listened for.
	* 
	* \note This function is only accessible to classes deriving from \c InputObject .
	* 
	* \param[in]	btn				The mouse button you would like to stop receiving input from. Type \c sf::Mouse:: and IntelliSense
	* will provide you a list of available mouse buttons.
	* \param[in]	eventToDereg	The event you would like the engine to stop listening for. Your options are \c MouseEvent::BtnPress or
	* \c MouseEvent::BtnRelease .
	* 
	* \note As the name of this function implies, this puts in a request for the engine to stop listening for the given mouse button's
	* specified input event. The request is processed on the same frame this function is called, and calls to either
	* \c InputObject::MouseBtnPressed or \c InputObject::MouseBtnReleased will cease \b the \b following frame.
	* 
	* \return	Does not return anything.
	* 
	* \section example Example
	* See the example code for InputObject::MouseBtnReleased for usage example.
	* 
	* \see InputObject::KeyPressed
	* \see InputObject::KeyReleased
	* \see InputObject::RequestKeyRegistration
	* \see InputObject::RequestKeyDeregistration
	* \see InputObject::MouseBtnPressed
	* \see InputObject::MouseBtnReleased
	* \see InputObject::RequestMouseBtnRegistration
	* \see InputObject::MouseCursorMoved
	* \see InputObject::RequestMouseCursorRegistration
	* \see InputObject::RequestMouseCursorDeregistration
	* \see UpdateObject
	* \see DrawObject
	* \see AlarmObject
	* \see CollisionObject
	*/
	void RequestMouseBtnDeregistration(sf::Mouse::Button btn, MouseEvent eventToDereg); 
	/*!
	* \brief	Request that the engine read mouse cursor movements.
	* 
	* Call this function in a \c InputObject -derived class to let the engine know you would like it to listen for when the mouse
	* cursor moves.
	* 
	* \note This function is only accessible to classes deriving from \c InputObject .
	* 
	* \note As the name of this function implies, this puts in a request for the engine to listen for mouse cursor movements. The request
	* is processed on the same frame this function is called, and calls to \c InputObject::MouseCursorMoved can begin as soon as \b the
	* \b following frame.
	* 
	* \return	Does not return anything.
	* 
	* \section example Example
	* TODO: docs for InputObject::RequestMouseCursorRegistration needs example code
	* 
	* \see InputObject::KeyPressed
	* \see InputObject::KeyReleased
	* \see InputObject::RequestKeyRegistration
	* \see InputObject::RequestKeyDeregistration
	* \see InputObject::MouseBtnPressed
	* \see InputObject::MouseBtnReleased
	* \see InputObject::RequestMouseBtnRegistration
	* \see InputObject::RequestMouseBtnDeregistration
	* \see InputObject::MouseCursorMoved
	* \see InputObject::RequestMouseCursorDeregistration
	* \see UpdateObject
	* \see DrawObject
	* \see AlarmObject
	* \see CollisionObject
	*/
	void RequestMouseCursorRegistration(); 
	/*!
	* \brief	Request that the engine stop reading mouse cursor movements.
	* 
	* Call this function in a \c InputObject -derived class to let the engine know you would like it to stop listening for mouse cursor
	* movements.
	* 
	* \note This function is only accessible to classes deriving from \c InputObject .
	* 
	* \note As the name of this function implies, this puts in a request for the engine to stop listening for mouse cursor movements.
	* The request is processed on the same frame this function is called, and calls to \c InputObject::MouseCursorMoved will cease
	* \b the \b following frame.
	* 
	* \return	Does not return anything.
	* 
	* \section example Example
	* TODO: docs for InputObject::RequestMouseCursorDeregistration need example code
	* 
	* \see InputObject::KeyPressed
	* \see InputObject::KeyReleased
	* \see InputObject::RequestKeyRegistration
	* \see InputObject::RequestKeyDeregistration
	* \see InputObject::MouseBtnPressed
	* \see InputObject::MouseBtnReleased
	* \see InputObject::RequestMouseBtnRegistration
	* \see InputObject::RequestMouseBtnDeregistration
	* \see InputObject::MouseCursorMoved
	* \see InputObject::RequestMouseCursorRegistration
	* \see UpdateObject
	* \see DrawObject
	* \see AlarmObject
	* \see CollisionObject
	*/
	void RequestMouseCursorDeregistration(); 

private:
	void RegisterKey(sf::Keyboard::Key key, KeyEvent eventToReg);
	void DeregisterKey(sf::Keyboard::Key key, KeyEvent eventToDereg);

	void RegisterMouseBtn(sf::Mouse::Button btn, MouseEvent eventToReg);
	void DeregisterMouseBtn(sf::Mouse::Button btn, MouseEvent eventToDereg);
	void RegisterMouseCursor();
	void DeregisterMouseCursor();

	struct KeyRegistrationData
	{
		RegistrationState regState;
		KeyRegistrationCommand* pRegCmd;
		KeyDeregistrationCommand* pDeregCmd;
	};

	using KeyTrackerID = std::pair<sf::Keyboard::Key, KeyEvent>;
	using KeyRegTracker = std::map<KeyTrackerID, KeyRegistrationData>;

	struct MouseBtnRegistrationData
	{
		RegistrationState regState;
		MouseBtnRegistrationCommand* pRegCmd;
		MouseBtnDeregistrationCommand* pDeregCmd;
	};

	using MouseBtnTrackerID = std::pair<sf::Mouse::Button, MouseEvent>;
	using MouseBtnRegTracker = std::map<MouseBtnTrackerID, MouseBtnRegistrationData>;

	struct MouseCursorRegistrationData
	{
		RegistrationState regState;
		MouseCursorRegistrationCommand* pRegCmd;
		MouseCursorDeregistrationCommand* pDeregCmd;
	};

private:
	KeyRegTracker keyTracker;
	MouseBtnRegTracker mouseBtnTracker;
	MouseCursorRegistrationData mouseCursorRegData;
};

#endif