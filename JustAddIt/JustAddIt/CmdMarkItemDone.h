#pragma once
#include "Command.h"
#include "ItemBank.h"

class CmdMarkItemDone :
	public Command
{
private:
	vector<Item*>::iterator _itemPtr;
public:
	CmdMarkItemDone(vector<Item*>::iterator itemPtr);
	~CmdMarkItemDone(void);
	vector<string> CmdMarkItemDone::execute();
};