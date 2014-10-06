#pragma once
#include "Command.h"
#include "ItemBank.h"


class CmdAddItem :
	public Command
{
private:
	Item* _itemAddr;

public:
	CmdAddItem(Item item);
	~CmdAddItem(void);

	vector<string> execute();
};

