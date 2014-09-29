#pragma once
#include "CommandLogic.h"
#include "Item.h"
#include "DataStorage.h"

class DeleteItem :
	public CommandLogic
{
private:
	vector<Item>::iterator _item;

public:
	DeleteItem(vector<Item>::iterator item);
	~DeleteItem();

	vector<string> execute();
	void deleteItem();
	void displaySuccessMessage();
};

