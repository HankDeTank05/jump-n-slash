#ifndef REGISTRATION_BROKER_H
#define REGISTRATION_BROKER_H

#include <list>

// forward declarations
class Command;

class RegistrationBroker
{
public:
	RegistrationBroker() = default;
	RegistrationBroker(const RegistrationBroker& rb) = delete;
	RegistrationBroker& operator=(const RegistrationBroker& rb) = delete;
	virtual ~RegistrationBroker();

	void AddCommand(Command* pCmd);
	void ExecuteCommands();

private:
	using CommandList = std::list<Command*>;
	CommandList cmdList;
};

#endif