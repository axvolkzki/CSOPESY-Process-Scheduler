#pragma once
#include "../Config/GlobalConfig.h"
#include "../Threading/IETThread.h"

class ICommand
{
public:
	enum CommandType {
		PRINT
	};

	ICommand(int pid, CommandType commandType);
	CommandType getCommandType();
	virtual void execute();

protected:
	int pid;
	CommandType commandType;
};

inline ICommand::CommandType ICommand::getCommandType()
{
	return this->commandType;
}

inline void ICommand::execute()
{
	std::cout << "Hello world from Process " << this->pid << "!";
}