#pragma once
#include "CommandLogic.h"

class Delete :
	public CommandLogic
{
private:
	Item _item;

public:
	Delete(Item item);
	~Delete();

	vector<string> execute();

};

