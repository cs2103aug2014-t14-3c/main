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

	eventsToBeDisplayed = ItemBank::getAllEvents();
	deadlinesToBeDisplayed = ItemBank::getAllDeadlines();
	tasksToBeDisplayed = ItemBank::getTasks();

	DisplayScreenConstructor* displayScreenConstructor = DisplayScreenConstructor::getInstance();
	outputMessageStorage.clear();
	outputMessageStorage = displayScreenConstructor->clearScreen();
	outputMessageStorage = displayScreenConstructor->constructListScreen(tasksToBeDisplayed, deadlinesToBeDisplayed, eventsToBeDisplayed);
	OutputControl::setCurrentScreen(OutputControl::CurrentScreenType::TO_DO_LIST_VIEW);

	return outputMessageStorage;
}