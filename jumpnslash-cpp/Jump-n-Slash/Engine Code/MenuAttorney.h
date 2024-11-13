#ifndef MENU_ATTORNEY_H
#define MENU_ATTORNEY_H

// forward declarations
class Menu;

class MenuAttorney
{
public:
	class MenuManagerAccess
	{
	private:
		friend class MenuManager;
		static void Init(Menu* pMenu);
		static void End(Menu* pMenu);
	};
};

#endif