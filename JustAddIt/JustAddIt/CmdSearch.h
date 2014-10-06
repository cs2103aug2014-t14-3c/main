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
	CmdSearch(vector<Item>::iterator itemPtr);
	~CmdSearch(void);

	vector<string> CmdSearch::execute();
};

