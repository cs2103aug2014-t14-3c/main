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
	COMMAND_TYPE determineCommandType(string userInput);
	void editTitle();
	void editStartDate();
	void editEndDate();
	void editVenue();
	void editCategory();
	void editPriority();
	PRIORITY_LEVEL obtainNewPriorityLevel();
	void showToUser(string outputString);
	void displaySuccessMessage();
	void displayEditScreen();
};

