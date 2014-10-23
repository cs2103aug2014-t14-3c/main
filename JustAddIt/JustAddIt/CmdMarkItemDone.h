#pragma once
#include "Command.h"
#include "ItemBank.h"

class CmdMarkItemDone :
	public Command
{
private:
	vector<Item*> _itemPtr;
public:
	CmdMarkItemDone(vector<Item*> itemPtr);
	~CmdMarkItemDone(void);
	vector<string> CmdMarkItemDone::execute();
};