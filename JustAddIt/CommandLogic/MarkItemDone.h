#pragma once
#include "CommandLogic.h"
#include "Item.h"

class MarkItemDone :
	public CommandLogic
{
private:
	vector<Item>::iterator _item;

public:
	MarkItemDone(vector<Item>::iterator item);
	~MarkItemDone();

	vector<string> execute();
	void markItem();
	void displaySuccessMessage();
};

