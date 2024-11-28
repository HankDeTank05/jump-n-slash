#ifndef SWORD_ATTORNEY_H
#define SWORD_ATTORNEY_H

class SwordAttorney
{
public:
	class StateAccess
	{
	private:
		friend class SwordStateIdle;
		friend class SwordStateSwing;
	};
};

#endif