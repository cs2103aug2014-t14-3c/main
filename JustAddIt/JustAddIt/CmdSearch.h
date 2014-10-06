#pragma once
#include "Command.h"
#include "ItemBank.h"

class CmdSearch :
	public Command 
{
private:
	string itemsToBeSearched;
	vector<string> temporaryStorage;
	vector<Item>::iterator _itemPtr;
public:
	CmdSearch(string keyword);
	~CmdSearch(void);

	vector<string> CmdSearch::execute();
};

