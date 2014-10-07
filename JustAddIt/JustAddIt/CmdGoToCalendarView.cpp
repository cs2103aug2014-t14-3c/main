#include "stdafx.h"
#include "CmdGoToCalendarView.h"


CmdGoToCalendarView::CmdGoToCalendarView(void)
{
}


CmdGoToCalendarView::~CmdGoToCalendarView(void)
{
}

vector<string> CmdGoToCalendarView::execute() {

	// get events in the month and input into toDoList and calList

	CmdGoToCalendarView::constructOutput();

	return outputMessageStorage;
}

void CmdGoToCalendarView::constructOutput() {
	int i = 1;
	string lineCount;

	outputMessageStorage.clear();
	OutputControl::resetCurrentItemList();

	outputMessageStorage.push_back("Item successfully added!\n");

	for(vector<Item*>::iterator iter = toDoList.begin(); iter != toDoList.end(); iter++) {
		lineCount = to_string(i) + ")";
		outputMessageStorage.push_back(lineCount);
		CmdGoToCalendarView::itemToString(*iter);
		i++;
	}

	CmdGoToCalendarView::setPageCommands();
}

void CmdGoToCalendarView::itemToString(Item* itemPtr) {
	string lineContent;

	lineContent = "   " + itemPtr->getTitle() + " " + itemPtr->getStartDateInString() + " to " + itemPtr->getEndDateInString();
	outputMessageStorage.push_back(lineContent);
}

void CmdGoToCalendarView::setPageCommands() {

}