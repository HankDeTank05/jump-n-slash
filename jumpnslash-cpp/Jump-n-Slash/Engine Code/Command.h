#ifndef COMMAND_H
#define COMMAND_H

class Command
{
public:
	Command() = default;
	Command(const Command& c) = delete;
	Command& operator=(const Command& c) = delete;
	virtual ~Command() = default;

	virtual void Execute() = 0;

};

#endif