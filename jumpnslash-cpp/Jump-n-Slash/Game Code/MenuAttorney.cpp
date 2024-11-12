#include "MenuAttorney.h"

#include "Menu.h"

void MenuAttorney::MenuManagerAccess::Init(Menu* pMenu)
{
	pMenu->Init();
}

void MenuAttorney::MenuManagerAccess::End(Menu* pMenu)
{
	pMenu->End();
}
