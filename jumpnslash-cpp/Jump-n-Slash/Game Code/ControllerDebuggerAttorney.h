#ifndef CONTROLLER_DEBUGGER_ATTORNEY_H
#define CONTROLLER_DEBUGGER_ATTORNEY_H

class ControllerDebuggerAttorney
{
public:
	class EngineAccess
	{
	private:
		friend class JumpSlashEngine;
		static void Terminate();
	};
};

#endif