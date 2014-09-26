#pragma once
#include "CommandLogic.h"

class EditItem :
	public CommandLogic
{
private:
	vector<Item>::iterator _item;

public:
	EditItem(vector<Item>::iterator item);
	~EditItem();

	virtual vector<string> execute();
};

