#pragma once
#include "Command.h"

class CmdSearch :
	public Command {
private:
	string itemsToBeSearched;
	vector<string> temporaryStorage;
public:
	CmdSearch(string keyword);
	~CmdSearch(void);

	string execute();
};

