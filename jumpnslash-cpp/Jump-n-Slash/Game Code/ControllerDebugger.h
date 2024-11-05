#ifndef CONTROLLER_DEBUGGER_H
#define CONTROLLER_DEBUGGER_H

#include "../Engine Code/UpdateObject.h"

class ControllerDebugger : public UpdateObject // this class is written as a singleton
{
private:
	static ControllerDebugger* pInstance;

	ControllerDebugger() = default;
	ControllerDebugger(const ControllerDebugger& cd) = delete;
	ControllerDebugger& operator=(const ControllerDebugger& cd) = delete;
	virtual ~ControllerDebugger() = default;

	static ControllerDebugger& Instance();

public: // static API functions
	static void DisplayDebugInfo();

private: // internal-only API functions
	friend class ControllerDebuggerAttorney;
	static void Terminate();

private: // API backend functions
	void privDisplayDebugInfo();
};

#endif