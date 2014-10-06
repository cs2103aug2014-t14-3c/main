#pragma once
#include "Command.h"
#include "ItemBank.h"

class CmdEditItem :
	public Command 
{
private:
	vector<Item>::iterator _itemPtr;
	int _editFieldNumber;
	string _newTitle;
	struct tm _newStartDateTime;
	struct tm _newEndDateTime;
	string _newVenue;
	string _newCategory;
	PriorityLevel _newPriority;

public:
	CmdEditItem(vector<Item>::iterator itemPtr);
	~CmdEditItem(void);
	vector<string> CmdEditItem::execute();
};