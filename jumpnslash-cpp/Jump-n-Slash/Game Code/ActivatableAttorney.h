#ifndef ACTIVATABLE_ATTORNEY_H
#define ACTIVATABLE_ATTORNEY_H

// forward declarations
class Activatable;

class ActivatableAttorney
{
public:
	class ActivatorAccess
	{
	private:
		friend class Activator;
		static void Activate(Activatable* pActivatable);
	};
};

#endif