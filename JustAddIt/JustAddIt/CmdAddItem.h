#pragma once
#include "Command.h"
#include "ItemBank.h"
#include "Item.h"
#include "OutputControl.h"
#include "DisplayScreenConstructor.h"

class CmdAddItem :
	public Command
{
private:
	Item* _itemAddr;

public:
	CmdAddItem(Item* item);
	~CmdAddItem(void);

	vector<string> execute();
	vector<string> undo();
	Item* getItem();
};

