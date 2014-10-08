#pragma once
#include "Command.h"
#include "ItemBank.h"


class CmdEditItem :
	public Command
{
private:
	vector<Item*>::iterator _itemPtr;
	int _editFieldNumber;
	//string _newTitle;
	//string _newDescription;
	//struct tm _newStartDateTime;
	//struct tm _newEndDateTime;
	//string _newVenue;
	//string _newCategory;
	//Item::PriorityLevel _newPriority;
	string _newFieldInfo;

	void constructOutput();
	void itemToString(Item* itemPtr);
	void setPageCommands();

public:
	CmdEditItem(vector<Item*>::iterator itemPtr, int fieldNum, string newFieldInfo);
	~CmdEditItem(void);
	vector<string> CmdEditItem::execute();
};