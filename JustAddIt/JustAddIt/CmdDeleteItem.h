#pragma once
#include "Command.h"
#include "ItemBank.h"

class CmdDeleteItem :
	public Command
{
private:
	vector<Item>::iterator _itemPtr;
public:
	CmdDeleteItem(vector<Item>::iterator itemPtr);
	~CmdDeleteItem(void);
	vector<string> CmdDeleteItem::execute();
};