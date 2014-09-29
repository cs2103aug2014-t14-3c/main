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
	void editTitle(string );
	void editStartDate(tm );
	void editEndDate(tm );
	void editVenue(string );
	void editCategory(vector<string> );
	void editPriority(PriorityLevel );
	void showToUser(string outputString);
	void displaySuccessMessage();
};

