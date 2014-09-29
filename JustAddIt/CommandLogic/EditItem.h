#pragma once
#include "CommandLogic.h"
#include "DataStorage.h"

class EditItem :
	public CommandLogic
{
private:
	vector<Item>::iterator _item;

public:
	EditItem(vector<Item>::iterator item);
	~EditItem();

	virtual vector<string> execute();
	void executeEditFunction();
	FIELD_TYPE determineFieldType(string userInput);
	void editTitle();
	void editStartDate();
	void editEndDate();
	void editVenue();
	void editCategory();
	void editPriority();
	void showToUser(string outputString);
	void displaySuccessMessage();
};

