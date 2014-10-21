#pragma once
#include "command.h"
#include "DisplayScreenConstructor.h"

class CmdShowOverdueDeadlines :
	public Command
{
private:
	time_t _currentTime;
	
public:
	CmdShowOverdueDeadlines(void);
	~CmdShowOverdueDeadlines(void);
	vector<string> execute();
};

