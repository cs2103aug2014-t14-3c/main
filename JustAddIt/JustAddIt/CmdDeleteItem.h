#pragma once
#include "Command.h"
#include "ItemBank.h"
#include "DisplayScreenConstructor.h"
#include "OutputControl.h"

#include "CmdGoToBaseScreen.h"

class CmdDeleteItem :
	public Command
{
private:
	vector<Item*> _itemPtrs;

public:
	CmdDeleteItem(vector<Item*> itemPtrs);
	~CmdDeleteItem(void);
	vector<string> CmdDeleteItem::execute();
};