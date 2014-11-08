//@author A0128461H
#pragma once
#include "ActionLog.h"
#include "Command.h"
#include "DisplayScreenConstructor.h"
#include "ItemBank.h"
#include "Item.h"
#include "OutputControl.h"

class CmdAddItem:
	public Command {
private:
	Item* _itemAddress;

public:
	CmdAddItem(Item* item);
	~CmdAddItem(void);

	vector<string> execute();
	Item* getItem();
};
