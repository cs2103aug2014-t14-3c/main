//@author A0128461H
#include "stdafx.h"
#include "CmdSearch.h"

//Used substr(1) because the first space character is unnecessary
CmdSearch::CmdSearch(string keyword) {
	_searchKeyword = keyword.substr(1);
}

CmdSearch::~CmdSearch(void) {
}

vector<string> CmdSearch::execute() {
	vector<Item*> tasks;
	vector<Item*> deadlines;
	vector<Item*> events;

	ItemBank* itemBank = ItemBank::getInstance();

	events = itemBank -> searchEvents(_searchKeyword);
	deadlines = itemBank -> searchDeadlines(_searchKeyword);
	tasks = itemBank -> searchTasks(_searchKeyword);

	DisplayScreenConstructor* displayScreenConstructor = DisplayScreenConstructor::getInstance();
	outputMessageStorage.clear();
	outputMessageStorage = displayScreenConstructor -> constructSearchScreen(tasks, deadlines, events, _searchKeyword);
	
	OutputControl::setCurrentScreen(OutputControl::CurrentScreenType::SEARCH_RESULTS_SCREEN);
	OutputControl::setCurrentBaseScreen(OutputControl::CurrentScreenType::SEARCH_RESULTS_SCREEN);

	//append all the items to a collated list vector
	vector<Item*> collatedList;
	collatedList.insert(collatedList.end(), events.begin(), events.end());
	collatedList.insert(collatedList.end(), deadlines.begin(), deadlines.end());
	collatedList.insert(collatedList.end(), tasks.begin(), tasks.end());
	OutputControl::setCurrentDisplayedItemList(collatedList);

	return outputMessageStorage;
}