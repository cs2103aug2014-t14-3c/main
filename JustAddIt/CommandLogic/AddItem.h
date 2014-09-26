#pragma once
#include "CommandLogic.h"

class AddItem :
	public CommandLogic
{
private:
	Item* _item;

public:
	AddItem(Item item);
	~AddItem();

	vector<string> execute();
};

