//@author A0128461H
#pragma once
#include "Command.h"
#include "DisplayScreenConstructor.h"
#include "ItemBank.h"
#include "Item.h"
#include "OutputControl.h"
#include "ActionLog.h"

class CmdAddItem:
	public Command {
private:
	Item* _itemAddress;

public:
	static const string SUCCESS_MESSAGE;
	static const string TIME_DATE_CONFLICT_MESSAGE;

	CmdAddItem(Item* item);
	~CmdAddItem(void);

	vector<string> execute();

	Item* getItem();
};