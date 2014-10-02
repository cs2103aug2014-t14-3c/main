#pragma once
#include "CommandLogic.h"
#include "DataStorage.h"

enum COMMAND_TYPE { EDIT_TITLE, EDIT_START_DATE, EDIT_END_DATE, EDIT_VENUE, EDIT_CATEGORY, EDIT_PRIORITY, SAVE, CANCEL, COMMAND_INVALID };

class EditItem :
	public CommandLogic
{
private:
	vector<Item>::iterator _item;

public:
	EditItem(vector<Item>::iterator item);
	~EditItem();

	virtual vector<string> execute(); // Why virtual??
	void executeEditFunction();
	COMMAND_TYPE determineCommandType(string userCommand);

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

