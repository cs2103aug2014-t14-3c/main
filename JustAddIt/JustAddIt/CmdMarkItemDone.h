#pragma once
#include "Command.h"
#include "ItemBank.h"
#include "ActionLog.h"
#include "CmdGoToBaseScreen.h"

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