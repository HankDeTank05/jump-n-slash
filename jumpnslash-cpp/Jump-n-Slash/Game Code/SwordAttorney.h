#ifndef SWORD_ATTORNEY_H
#define SWORD_ATTORNEY_H

// forward declarations
class Sword;

class SwordAttorney
{
public:
	class StateAccess
	{
	private:
		friend class SwordStateIdle;
		friend class SwordStateSwing;
		static bool IsAttacking(Sword* pSword);
		static void RequestCollisionRegistration(Sword* pSword);
		static void RequestCollisionDeregistration(Sword* pSword);
		static void SetAnimationIdle(Sword* pSword);
		static void SetAnimationSwing(Sword* pSword);
	};
	class PlayerAccess
	{
		friend class Player;
		static void Attack(Sword* pSword);
	};
};

#endif