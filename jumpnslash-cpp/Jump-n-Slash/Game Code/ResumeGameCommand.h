#ifndef RESUME_GAME_COMMAND_H
#define RESUME_GAME_COMMAND_H

// game includes
#include "MenuCommand.h"

class ResumeGameCommand : public MenuCommand
{
public:
	ResumeGameCommand() = default;
	ResumeGameCommand(const ResumeGameCommand& rgc) = delete;
	ResumeGameCommand& operator=(const ResumeGameCommand& rgc) = delete;
	virtual ~ResumeGameCommand() = default;

	virtual void Execute() override;
};

#endif