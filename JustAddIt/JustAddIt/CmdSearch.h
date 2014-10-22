#pragma once
#include "Command.h"
#include "ItemBank.h"
#include "ActionLog.h"

class CmdSearch :
	public Command 
{
private:
	string searchKeyword;
	vector<string> temporaryStorage;
	vector<string> contentAfterSearching;
	
public:
	CmdSearch(string keyword);
	~CmdSearch(void);

	vector<string> CmdSearch::execute();
};

