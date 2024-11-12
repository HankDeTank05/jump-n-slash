#ifndef QUIT_GAME_COMMAND_H
#define QUIT_GAME_COMMAND_H

#include "MenuCommand.h"

class QuitGameCommand : public MenuCommand
{
public:
	QuitGameCommand() = default;
	QuitGameCommand(const QuitGameCommand& qgc) = delete;
	QuitGameCommand& operator=(const QuitGameCommand& qgc) = delete;
	virtual ~QuitGameCommand() = default;

	virtual void Execute() override;
};

#endif