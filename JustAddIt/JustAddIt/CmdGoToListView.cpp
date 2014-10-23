#include "stdafx.h"
#include "CmdGoToListView.h"

CmdGoToListView::CmdGoToListView()
{
}

CmdGoToListView::~CmdGoToListView(void)
{
}

vector<string> CmdGoToListView::execute() {
	vector<Item*>tasksToBeDisplayed;
	vector<Item*>deadlinesToBeDisplayed;
	vector<Item*>eventsToBeDisplayed;
	vector<Item*>collatedList;

	eventsToBeDisplayed = ItemBank::getAllEvents();
	deadlinesToBeDisplayed = ItemBank::getAllDeadlines();
	tasksToBeDisplayed = ItemBank::getTasks();

	DisplayScreenConstructor* displayScreenConstructor = DisplayScreenConstructor::getInstance();
	outputMessageStorage.clear();
	outputMessageStorage = displayScreenConstructor->clearScreen();
	outputMessageStorage = displayScreenConstructor->constructListScreen(tasksToBeDisplayed, deadlinesToBeDisplayed, eventsToBeDisplayed);
	OutputControl::setCurrentScreen(OutputControl::CurrentScreenType::TO_DO_LIST_VIEW);
	//OutputControl::setCurrentBaseScreen(OutputControl::CurrentScreenType::TO_DO_LIST_VIEW);
	//append all items to collated list vector
	collatedList.insert(collatedList.end(), eventsToBeDisplayed.begin(), eventsToBeDisplayed.end());
	collatedList.insert(collatedList.end(), deadlinesToBeDisplayed.begin(), deadlinesToBeDisplayed.end());
	collatedList.insert(collatedList.end(), tasksToBeDisplayed.begin(), tasksToBeDisplayed.end());
	OutputControl::setCurrentDisplayedItemList(collatedList);

	return outputMessageStorage;
}