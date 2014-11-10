#pragma once
//@author A0110770U
//------------------------------------------
//CmdGoToListView acts as a function to allow the
//user to go to the list view.
//
//On the list view, it shows a sorted view
//of all items.
//
//CmdGoToListView will not throw exceptions.
//------------------------------------------
#include "command.h"
#include "ItemBank.h"
#include "DisplayScreenConstructor.h"

class CmdGoToListView :
	public Command
{
private:
	int _numWeeks;

	void updateOutputControl(vector<Item*> events, vector<Item*> deadlines, vector<Item*> tasks);
	vector<string> storeListScreenForDisplay(vector<Item*> events, vector<Item*> deadlines, vector<Item*> tasks);
public:

	CmdGoToListView();
	~CmdGoToListView(void);
	vector<string> execute();
};

