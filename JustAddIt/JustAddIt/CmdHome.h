#pragma once
#include "Command.h"
#include "DisplayScreenConstructor.h"

class CmdHome :
	public Command
{
private:
	struct tm _currentTime;

public:
	CmdHome(void);
	~CmdHome(void);
	vector<string> CmdHome::execute();
};