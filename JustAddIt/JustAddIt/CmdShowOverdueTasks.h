#pragma once
#include "command.h"
#include "DisplayScreenConstructor.h"

class CmdShowOverdueTasks :
	public Command
{
private:
	time_t _currentTime;
	
public:
	CmdShowOverdueTasks(void);
	~CmdShowOverdueTasks(void);
	vector<string> execute();
};

