#ifndef CONTROL_MANAGER_ATTORNEY_H
#define CONTROL_MANAGER_ATTORNEY_H

class ControlManagerAttorney
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