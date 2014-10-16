#pragma once
#include "Command.h"
#include "DisplayScreenConstructor.h"

class CmdHome :
	public Command
{
private:
	vector<string> outputMessageStorage;
	//void setPageCommands();

public:
	CmdHome(void);
	~CmdHome(void);
	vector<string> CmdHome::execute();
};