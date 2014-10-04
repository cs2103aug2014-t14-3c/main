#pragma once
#include "command.h"
#include "ItemBank.h"

class CmdAddItem :
	public Command
{
private:
	Item* _itemAddr;

public:
	CmdAddItem(Item item);
	~CmdAddItem(void);

	void execute();
};

