#include "stdafx.h"
#include "CmdSearch.h"

CmdSearch::CmdSearch(string keyword) {
	_searchKeyword = keyword;
}

CmdSearch::~CmdSearch(void) {
}

vector<string> CmdSearch::execute() {
	vector<Item*>tasksToBeDisplayed;
	vector<Item*>deadlinesToBeDisplayed;
	vector<Item*>eventsToBeDisplayed;

	eventsToBeDisplayed = ItemBank::searchEvents(_searchKeyword);
	deadlinesToBeDisplayed = ItemBank::searchDeadlines(_searchKeyword);
	tasksToBeDisplayed = ItemBank::searchTasks(_searchKeyword);

	DisplayScreenConstructor* displayScreenConstructor = DisplayScreenConstructor::getInstance();
	outputMessageStorage.clear();
	outputMessageStorage = displayScreenConstructor->clearScreen();
	outputMessageStorage = displayScreenConstructor->constructSearchScreen(tasksToBeDisplayed, deadlinesToBeDisplayed, eventsToBeDisplayed);
	OutputControl::setCurrentScreen(OutputControl::CurrentScreenType::SEARCH_RESULTS_SCREEN);

	return outputMessageStorage;
}