#include "InputObjectAttorney.h"

#include "InputObject.h"

void InputObjectAttorney::Registration::RegisterKey(InputObject* pInputable, sf::Keyboard::Key key, KeyEvent eventToReg)
{
	pInputable->RegisterKey(key, eventToReg);
}

void InputObjectAttorney::Registration::DeregisterKey(InputObject* pInputable, sf::Keyboard::Key key, KeyEvent eventToDereg)
{
	pInputable->DeregisterKey(key, eventToDereg);
}

void InputObjectAttorney::Registration::RegisterMouseBtn(InputObject* pInputable, sf::Mouse::Button btn, MouseEvent eventToReg)
{
	pInputable->RegisterMouseBtn(btn, eventToReg);
}

void InputObjectAttorney::Registration::DeregisterMouseBtn(InputObject* pInputable, sf::Mouse::Button btn, MouseEvent eventToDereg)
{
	pInputable->DeregisterMouseBtn(btn, eventToDereg);
}

void InputObjectAttorney::Registration::RegisterMouseCursor(InputObject* pInputable)
{
	pInputable->RegisterMouseCursor();
}

void InputObjectAttorney::Registration::DeregisterMouseCursor(InputObject* pInputable)
{
	pInputable->DeregisterMouseCursor();
}

void InputObjectAttorney::Registration::RegisterGamepadBtn(InputObject* pInputable, int gamepadIndex, int btnNum, GamepadBtnEvent eventToReg)
{
	pInputable->RegisterGamepadBtn(gamepadIndex, btnNum, eventToReg);
}

void InputObjectAttorney::Registration::DeregisterGamepadBtn(InputObject* pInputable, int gamepadIndex, int btnNum, GamepadBtnEvent eventToDereg)
{
	pInputable->DeregisterGamepadBtn(gamepadIndex, btnNum, eventToDereg);
}

void InputObjectAttorney::Registration::RegisterGamepadAxis(InputObject* pInputable, int gamepadIndex, sf::Joystick::Axis axis, GamepadAxisEvent eventToReg)
{
	pInputable->RegisterGamepadAxis(gamepadIndex, axis, eventToReg);
}

void InputObjectAttorney::Registration::DeregisterGamepadAxis(InputObject* pInputable, int gamepadIndex, sf::Joystick::Axis axis, GamepadAxisEvent eventToDereg)
{
	pInputable->DeregisterGamepadAxis(gamepadIndex, axis, eventToDereg);
}

void InputObjectAttorney::KeyEvents::KeyPressed(InputObject* pInputable, sf::Keyboard::Key key)
{
	pInputable->KeyPressed(key);
}

void InputObjectAttorney::KeyEvents::KeyReleased(InputObject* pInputable, sf::Keyboard::Key key)
{
	pInputable->KeyReleased(key);
}

void InputObjectAttorney::MouseEvents::MouseBtnPressed(InputObject* pInputable, sf::Mouse::Button btn)
{
	pInputable->MouseBtnPressed(btn);
}

void InputObjectAttorney::MouseEvents::MouseBtnReleased(InputObject* pInputable, sf::Mouse::Button btn)
{
	pInputable->MouseBtnReleased(btn);
}

void InputObjectAttorney::MouseEvents::MouseCursorMoved(InputObject* pInputable, sf::Vector2i pos, sf::Vector2i delta)
{
	pInputable->MouseCursorMoved(pos, delta);
}

void InputObjectAttorney::GamepadEvents::GamepadBtnPressed(InputObject* pInputable, int gamepadIndex, int btnNum)
{
	pInputable->GamepadBtnPressed(gamepadIndex, btnNum);
}

void InputObjectAttorney::GamepadEvents::GamepadBtnReleased(InputObject* pInputable, int gamepadIndex, int btnNum)
{
	pInputable->GamepadBtnReleased(gamepadIndex, btnNum);
}

void InputObjectAttorney::GamepadEvents::GamepadAxisMoved(InputObject* pInputable, int gamepadIndex, sf::Joystick::Axis axis, float axisState, float axisStateDelta)
{
	pInputable->GamepadAxisMoved(gamepadIndex, axis, axisState, axisStateDelta);
}
