#pragma once
#include "command.h"

class CmdDeleteItem :
	public Command
{
private: 
	vector<Item>::iterator itemAddr;

public:
	CmdDeleteItem(void);
	~CmdDeleteItem(void);

	void execute();
};

