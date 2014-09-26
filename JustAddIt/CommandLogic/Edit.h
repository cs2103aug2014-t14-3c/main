#pragma once
#include "CommandLogic.h"
class Edit :
	public CommandLogic
{
private:
	Item _item;
public:
	Edit(Item item);
	~Edit();

	virtual vector<string> execute();
};

