#pragma once
#include "CommandLogic.h"
class Add :
	public CommandLogic
{
private:
	Item item;

public:
	Add(Item item);
	~Add();

	vector<string> execute();
};

