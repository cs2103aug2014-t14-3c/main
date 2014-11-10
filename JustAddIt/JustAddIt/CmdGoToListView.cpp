//@author A0110770U
#include "stdafx.h"
#include "CmdGoToListView.h"

CmdGoToListView::CmdGoToListView()
{
}

CmdGoToListView::~CmdGoToListView(void)
{
}

vector<string> CmdGoToListView::execute() {
	
	vector<Item*> tasks;
	vector<Item*> deadlines;
	vector<Item*> events;
	ItemBank* itemBank = ItemBank::getInstance();

	events = itemBank->getAllEvents();
	deadlines = itemBank->getAllDeadlines();
	tasks = itemBank->getAllTasks();
	
	outputMessageStorage.clear();
	outputMessageStorage = storeListScreenForDisplay(events, deadlines, tasks);
	updateOutputControl(events, deadlines, tasks);

	return outputMessageStorage;
}

//This function updates the information that OutputControl
//keeps track of; items displayed, base screen and current screen.
void CmdGoToListView::updateOutputControl(vector<Item*> events, vector<Item*> deadlines, vector<Item*> tasks){
	
	vector<Item*> collatedList;
	collatedList.insert(collatedList.end(), events.begin(), events.end());
	collatedList.insert(collatedList.end(), deadlines.begin(), deadlines.end());
	collatedList.insert(collatedList.end(), tasks.begin(), tasks.end());
	OutputControl::setCurrentDisplayedItemList(collatedList);

	OutputControl::setCurrentScreen(OutputControl::CurrentScreenType::TO_DO_LIST_VIEW);
	OutputControl::setCurrentBaseScreen(OutputControl::CurrentScreenType::TO_DO_LIST_VIEW);
}

//This function uses the input Item* vectors and 
//returns the list screen as a vector of strings.
vector<string> CmdGoToListView::storeListScreenForDisplay(vector<Item*> events, vector<Item*> deadlines, vector<Item*> tasks){
	DisplayScreenConstructor* displayScreenConstructor = DisplayScreenConstructor::getInstance();
	return displayScreenConstructor->constructListView(tasks, deadlines, events);
	 
}