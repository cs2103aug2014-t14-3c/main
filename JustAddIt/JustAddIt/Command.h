#pragma once

#include "stdafx.h"
#include "ItemBank.h"
#include "OutputControl.h"

#define MAX_SIZE 100

using namespace std;

class Command
{
protected:
	static const string FORMAT_TITLE;
	static const string FORMAT_DESCRIPTION;
	static const string FORMAT_START;
	static const string FORMAT_END;
	static const string FORMAT_VENUE;
	static const string FORMAT_PRIORITY;
	static const string FORMAT_CATEGORY;	
	static const string FORMAT_DIVIDER; 

	static const string PAGE_COMMAND_TO_DO_LIST_VIEW;
	static const string PAGE_COMMAND_CALENDAR_VIEW;
	static const string PAGE_COMMAND_OVERDUE_TASKS;
	static const string PAGE_COMMAND_SAVE;
	static const string PAGE_COMMAND_EDIT;
	static const string PAGE_COMMAND_CANCEL;
	static const string PAGE_COMMAND_VIEW_TWO_WEEKS;
	static const string PAGE_COMMAND_VIEW_THREE_WEEKS;
	static const string PAGE_COMMAND_VIEW_MONTH;
	static const string PAGE_COMMAND_SHOW_ALL;
	static const string PAGE_COMMAND_SORT_CATEGORY;
	static const string PAGE_COMMAND_SORT_PRIORITY;
	static const string PAGE_COMMAND_EXPORT;
	static const string PAGE_COMMAND_MODIFY;
	static const string PAGE_COMMAND_DELETE;
	static const string PAGE_COMMAND_MARK_DONE;


	vector<string> outputMessageStorage;

	virtual vector<string> itemToString(Item* itemPtr);
	virtual vector<string> constructOutput();

public:
	Command(void);
	~Command(void);
	virtual vector<string> execute();

};