#pragma once
#include "Command.h"
#include "ItemBank.h"
#include "DisplayScreenConstructor.h"


class CmdEditItem :
	public Command
{
private:
	Item* _itemAddr;
	vector<Item*>::iterator _bankPtr;
	int _editFieldNumber;
	string _newFieldInfo;
	tm _newTimeInfo;

public:
	CmdEditItem(vector<Item*>::iterator itemPtr, int fieldNum, string newFieldInfo);
	CmdEditItem(vector<Item*>::iterator itemPtr, int fieldNum, tm newTimeInfo);
	~CmdEditItem(void);
	vector<string> CmdEditItem::execute();
};