#pragma once
#include "Command.h"
#include "ItemBank.h"
#include "DisplayScreenConstructor.h"
#include "OutputControl.h"

class CmdDeleteItem :
	public Command
{
private:
	vector<Item*>::iterator _itemPtr;
	Item* _itemAddr;
	vector<string> outputMessageStorage;

	//void constructOutput();
	//void itemToString(Item* itemPtr);
	//void setPageCommands();

public:
	CmdDeleteItem(vector<Item*>::iterator itemPtr);
	~CmdDeleteItem(void);
	vector<string> CmdDeleteItem::execute();
};