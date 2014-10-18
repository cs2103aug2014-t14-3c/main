#pragma once
#include "Command.h"
#include "ItemBank.h"
#include "DisplayScreenConstructor.h"


class CmdEditItem :
	public Command
{
private:
	Item* _itemAddr;
	vector<Item*>::iterator _itemPtr;
	int _editFieldNumber;
	string _newFieldInfo;

public:
	CmdEditItem(vector<Item*>::iterator itemPtr, int fieldNum, string newFieldInfo);
	~CmdEditItem(void);
	vector<string> CmdEditItem::execute();
};