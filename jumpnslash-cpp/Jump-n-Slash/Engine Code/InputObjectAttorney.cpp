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
