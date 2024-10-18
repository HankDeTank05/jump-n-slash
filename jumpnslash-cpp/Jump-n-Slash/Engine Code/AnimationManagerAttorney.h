#ifndef ANIMATION_MANAGER_ATTORNEY_H
#define ANIMATION_MANAGER_ATTORNEY_H

class AnimationManagerAttorney
{
public:
	class Termination
	{
	private:
		friend class JumpSlashEngine;
		static void Terminate();
	};
};

#endif