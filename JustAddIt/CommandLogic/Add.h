#pragma once
#include "CommandLogic.h"

class Add :
	public CommandLogic
{
private:
	Item _item;

public:
	Add(Item item);
	~Add();

	vector<string> execute();
};

