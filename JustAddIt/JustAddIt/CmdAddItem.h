#pragma once
#include "Command.h"
#include "ItemBank.h"


class CmdAddItem :
	public Command
{
private:
	Item* _itemAddr;
	
	void constructOutput();
	void itemToString(Item* itemPtr);
	void setPageCommands();

public:
	CmdAddItem(Item* item);
	~CmdAddItem(void);

	vector<string> execute();
	Item* getItem();
};

