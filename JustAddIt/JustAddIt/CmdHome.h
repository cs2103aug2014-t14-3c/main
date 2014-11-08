#pragma once
//@author A0110770U
#include "Command.h"
#include "DisplayScreenConstructor.h"

class CmdHome :
	public Command
{
private:
	struct tm _currentTime;

	void updateOutputControl();
	vector<string> storeHomeScreenForDisplay();

public:
	CmdHome(void);
	~CmdHome(void);
	vector<string> CmdHome::execute();
};