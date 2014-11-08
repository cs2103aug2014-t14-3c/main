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
	vector<Item*> collatedList;

	ItemBank* itemBank = ItemBank::getInstance();

	events = itemBank->getAllEvents();
	deadlines = itemBank->getAllDeadlines();
	tasks = itemBank->getAllTasks();

	DisplayScreenConstructor* displayScreenConstructor = DisplayScreenConstructor::getInstance();
	outputMessageStorage.clear();
	outputMessageStorage = displayScreenConstructor->clearScreen();
	outputMessageStorage = displayScreenConstructor->constructListScreen(tasks, deadlines, events);
	OutputControl::setCurrentScreen(OutputControl::CurrentScreenType::TO_DO_LIST_VIEW);
	OutputControl::setCurrentBaseScreen(OutputControl::CurrentScreenType::TO_DO_LIST_VIEW);
	
	//append all items to collated list vector
	collatedList.insert(collatedList.end(), events.begin(), events.end());
	collatedList.insert(collatedList.end(), deadlines.begin(), deadlines.end());
	collatedList.insert(collatedList.end(), tasks.begin(), tasks.end());
	OutputControl::setCurrentDisplayedItemList(collatedList);

	return outputMessageStorage;
}