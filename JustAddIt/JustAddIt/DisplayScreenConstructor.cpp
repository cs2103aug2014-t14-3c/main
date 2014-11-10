//@author A0108397W
#include "stdafx.h"
#include "DisplayScreenConstructor.h"

using namespace std;

const string DisplayScreenConstructor::TEMPLATE_SCREEN_HOME = "JustAddIt/Templates/HomeScreen.txt";
const string DisplayScreenConstructor::TEMPLATE_SCREEN_EDIT = "JustAddIt/Templates/EditScreen.txt";
const string DisplayScreenConstructor::TEMPLATE_SCREEN_SEARCH = "JustAddIt/Templates/SearchScreen.txt";
const string DisplayScreenConstructor::TEMPLATE_SCREEN_LISTVIEW = "JustAddIt/Templates/ListViewScreen.txt";
const string DisplayScreenConstructor::TEMPLATE_SCREEN_OVERDUE = "JustAddIt/Templates/OverdueScreen.txt";
const string DisplayScreenConstructor::MARK_DONE = "<span style=\"color:#CC0000;\">[DONE]</span> ";
const string DisplayScreenConstructor::HOME_WEEK_CLEAR = "<span style=\"color:#d3d3d3;\">You're clear for the week!</span>";
const string DisplayScreenConstructor::HOME_HAPPENINGS = "<u>What's going on this week?</u>";
const string DisplayScreenConstructor::EDIT_HEADER = "<u>Edit ";
const string DisplayScreenConstructor::EDIT_TITLE_FIELD = "1) Title: ";
const string DisplayScreenConstructor::EDIT_DESCRIPTION_FIELD = "2) Description: ";
const string DisplayScreenConstructor::EDIT_START_TIME_FIELD = "3) Start: ";
const string DisplayScreenConstructor::EDIT_END_TIME_FIELD = "4) End: ";
const string DisplayScreenConstructor::EDIT_PRIORITY_FIELD = "5) Priority: ";
const string DisplayScreenConstructor::EDIT_CATEGORY_FIELD = "6) Category: ";
const string DisplayScreenConstructor::SEARCH_SHOW_RESULTS = "<u>Showing results:</u> <i>";
const string DisplayScreenConstructor::SEARCH_NO_RESULTS = "<span style=\"color:#d3d3d3;\">No results found.</span>";
const string DisplayScreenConstructor::LISTVIEW_ALL_EVENTS = "<u>All Events</u>";
const string DisplayScreenConstructor::LISTVIEW_NO_EVENTS = "<span style=\"color:#d3d3d3;\">No events found</span>";
const string DisplayScreenConstructor::LISTVIEW_NO_DEADLINES = "<span style=\"color:#d3d3d3;\">No deadlines found</span>";
const string DisplayScreenConstructor::LISTVIEW_NO_TASKS = "<span style=\"color:#d3d3d3;\">No tasks found</span>";
const string DisplayScreenConstructor::OVERDUE_HEADER = "<u>Overdue Deadlines";
const string DisplayScreenConstructor::OVERDUE_NO_OVERDUE = "<span style=\"color:#d3d3d3;\">All caught up! Nothing is overdue.</span>";
const string DisplayScreenConstructor::OVERDUE_DUE = " was due ";
const string DisplayScreenConstructor::PERIOD = ". ";
const string DisplayScreenConstructor::FROM = "&nbsp;&nbsp;&nbsp;from:&nbsp;";
const string DisplayScreenConstructor::TO = "&nbsp;&nbsp;&nbsp;to:&nbsp;&nbsp;&nbsp;&nbsp;";
const string DisplayScreenConstructor::BY = "&nbsp;&nbsp;&nbsp;by:&nbsp;&nbsp;&nbsp;&nbsp;";
const string DisplayScreenConstructor::DEFAULT_INPUT = "-";
const string DisplayScreenConstructor::BLANK =  "";
const string DisplayScreenConstructor::NEW_LINE = "<br>";

DisplayScreenConstructor* DisplayScreenConstructor::displayScreenConstructor = NULL;

DisplayScreenConstructor::DisplayScreenConstructor(void) {
}

DisplayScreenConstructor::~DisplayScreenConstructor(void) {
}

DisplayScreenConstructor* DisplayScreenConstructor::getInstance(void) {
	if (displayScreenConstructor == NULL) {
		displayScreenConstructor = new DisplayScreenConstructor();
	}
	return displayScreenConstructor;
}

vector<string> DisplayScreenConstructor::constructHomeScreen(vector<Item*>tasks, vector<Item*>deadlines, vector<Item*>events) {
	outputMessageStorage.clear();
	outputMessageStorage = displayItemsOnHomeScreen(tasks, deadlines, events);

	exportToFile(outputMessageStorage);

	return outputMessageStorage;
}

//This function inserts Item details onto the Home screen for display
vector<string> DisplayScreenConstructor::displayItemsOnHomeScreen(vector<Item*> tasks, vector<Item*> deadlines, vector<Item*> events) {
	ifstream mytextfile (TEMPLATE_SCREEN_HOME);
	vector<string> homeScreen;
	string dummyLine;
	int displayCounter = 1;

	while (!mytextfile.eof()) {
		getline(mytextfile, dummyLine);

		if (dummyLine == HOME_HAPPENINGS) {
			homeScreen.push_back(dummyLine);

			getline(mytextfile, dummyLine);
			homeScreen.push_back(dummyLine);

			if(events.empty() && deadlines.empty() && tasks.empty()) {
				dummyLine += HOME_WEEK_CLEAR;
				homeScreen.push_back(dummyLine);
			}
			else {
				vector<string> eventList = constructEventList(events,displayCounter);
				vector<string> deadlineList = constructDeadlineList(deadlines, displayCounter);
				vector<string> taskList = constructTaskList(tasks, displayCounter);

				homeScreen.insert(homeScreen.end(), eventList.begin(), eventList.end());
				homeScreen.insert(homeScreen.end(), deadlineList.begin(), deadlineList.end());
				homeScreen.insert(homeScreen.end(), taskList.begin(), taskList.end());
			}
		}
		else {
			homeScreen.push_back(dummyLine);
		}
	}
	return homeScreen;
}

//This function detects the various fields in the template Edit screen and inputs the corresponding Item details.
vector<string> DisplayScreenConstructor::constructEditScreen(Item* item) {
	ifstream mytextfile (TEMPLATE_SCREEN_EDIT);
	string dummyLine;

	outputMessageStorage.clear();

	while (!mytextfile.eof()) {
		getline(mytextfile, dummyLine);

		if (dummyLine == EDIT_HEADER) {
			dummyLine += item->getItemTypeInString();
		}
		else if (dummyLine == EDIT_TITLE_FIELD) {

			if (item->isDone()) {
				dummyLine += MARK_DONE;
			}

			dummyLine += item->getTitle();

		}
		else if (dummyLine == EDIT_DESCRIPTION_FIELD) {
			if (item->getDescription() == DEFAULT_INPUT) {
				dummyLine += BLANK;
			}
			else {
				dummyLine += item->getDescription();
			}
		}
		else if (dummyLine == EDIT_START_TIME_FIELD) {
			if (item->isTask() || item->isDeadline()) {
				dummyLine += BLANK;
			}
			else {
				dummyLine += item->getStartDateInString();
			}
		}
		else if (dummyLine == EDIT_END_TIME_FIELD) {
			if (item->isTask()) {
				dummyLine += BLANK;
			}
			else {
				dummyLine += item->getEndDateInString();
			}
		}
		else if (dummyLine == EDIT_PRIORITY_FIELD) {
			dummyLine += item->getPriorityInString();
		}
		else if (dummyLine == EDIT_CATEGORY_FIELD) {
			if (item->getCategory() == DEFAULT_INPUT) {
				dummyLine += BLANK;
			}
			else {
				dummyLine += item->getCategory();
			}
		}

		outputMessageStorage.push_back(dummyLine);
	}

	exportToFile(outputMessageStorage);

	return outputMessageStorage;
}

vector<string> DisplayScreenConstructor::constructSearchScreen(vector<Item*>tasks, vector<Item*>deadlines, vector<Item*>events, string keyword) {
	outputMessageStorage.clear();
	outputMessageStorage = displayItemsOnSearchScreen(tasks, deadlines, events, keyword);
	exportToFile(outputMessageStorage);

	return outputMessageStorage;
}

//This function inputs the searched items onto the Search screen for display
vector<string> DisplayScreenConstructor::displayItemsOnSearchScreen(vector<Item*>tasks, vector<Item*>deadlines, vector<Item*>events, string keyword) {
	ifstream mytextfile (TEMPLATE_SCREEN_SEARCH);
	vector<string> searchScreen;
	string dummyLine;
	int displayCounter = 1;

	while (!mytextfile.eof()) {
		getline(mytextfile, dummyLine);

		if (dummyLine == SEARCH_SHOW_RESULTS) {
			dummyLine += keyword;
			searchScreen.push_back(dummyLine);

			getline(mytextfile, dummyLine);
			searchScreen.push_back(dummyLine);

			if(events.empty() && deadlines.empty() && tasks.empty()){
				dummyLine += SEARCH_NO_RESULTS;
				searchScreen.push_back(dummyLine);
			}
			else{
				vector<string> eventList = constructEventList(events,displayCounter);
				vector<string> deadlineList = constructDeadlineList(deadlines, displayCounter);
				vector<string> taskList = constructTaskList(tasks, displayCounter);

				searchScreen.insert(searchScreen.end(), eventList.begin(), eventList.end());
				searchScreen.insert(searchScreen.end(), deadlineList.begin(), deadlineList.end());
				searchScreen.insert(searchScreen.end(), taskList.begin(), taskList.end());
			}
		}
		else {
			searchScreen.push_back(dummyLine);
		}
	}

	return searchScreen;
}

vector<string> DisplayScreenConstructor::constructListView(vector<Item*>tasks, vector<Item*>deadlines, vector<Item*>events) {
	outputMessageStorage.clear();
	outputMessageStorage = displayItemsOnListView(tasks, deadlines, events);
	exportToFile(outputMessageStorage);

	return outputMessageStorage;
}

vector<string> DisplayScreenConstructor::displayItemsOnListView(vector<Item*>tasks, vector<Item*>deadlines, vector<Item*>events) {
	ifstream mytextfile (TEMPLATE_SCREEN_LISTVIEW);
	vector<string> listViewScreen, eventList, deadlineList, taskList;
	string dummyLine;
	int displayCounter = 1;
	vector<Item*>::iterator iter;

	while (!mytextfile.eof()) {
		getline(mytextfile, dummyLine);

		if (dummyLine == LISTVIEW_ALL_EVENTS) {

			listViewScreen.push_back(dummyLine);
			getline(mytextfile, dummyLine);
			listViewScreen.push_back(dummyLine);

			if(events.empty()){
				dummyLine += LISTVIEW_NO_EVENTS;
				listViewScreen.push_back(dummyLine);
			}
			else{
				eventList = constructEventList(events,displayCounter);
				listViewScreen.insert(listViewScreen.end(), eventList.begin(), eventList.end());
			}

			getline(mytextfile, dummyLine);
			listViewScreen.push_back(dummyLine);
			getline(mytextfile, dummyLine);
			listViewScreen.push_back(dummyLine);
			getline(mytextfile, dummyLine);
			listViewScreen.push_back(dummyLine);

			if(deadlines.empty()){
				dummyLine += LISTVIEW_NO_DEADLINES;
				listViewScreen.push_back(dummyLine);
			}
			else{
				deadlineList = constructDeadlineList(deadlines, displayCounter);
				listViewScreen.insert(listViewScreen.end(), deadlineList.begin(), deadlineList.end());
			}

			getline(mytextfile, dummyLine);
			listViewScreen.push_back(dummyLine);
			getline(mytextfile, dummyLine);
			listViewScreen.push_back(dummyLine);
			getline(mytextfile, dummyLine);
			listViewScreen.push_back(dummyLine);

			if(tasks.empty()){
				dummyLine += LISTVIEW_NO_TASKS;
				listViewScreen.push_back(dummyLine);
			}
			else{
				taskList = constructTaskList(tasks, displayCounter);
				listViewScreen.insert(listViewScreen.end(), taskList.begin(), taskList.end());
			}
		}
		else {
			listViewScreen.push_back(dummyLine);
		}
	}

	return listViewScreen;
}

vector<string> DisplayScreenConstructor::constructOverdueScreen(vector<Item*>items) {

	outputMessageStorage.clear();
	outputMessageStorage = displayItemsOnOverdueScreen(items);
	exportToFile(outputMessageStorage);

	return outputMessageStorage;
}

vector<string> DisplayScreenConstructor::displayItemsOnOverdueScreen (vector<Item*> overdueItems) {
	ifstream mytextfile (TEMPLATE_SCREEN_OVERDUE);
	vector<string> overdueScreen;
	string dummyLine;
	int displayCounter = 1;
	vector<Item*>::iterator iter;

	while (!mytextfile.eof()) {
		getline(mytextfile, dummyLine);
		if (dummyLine == OVERDUE_HEADER) {
			overdueScreen.push_back(dummyLine);

			getline(mytextfile, dummyLine);
			overdueScreen.push_back(dummyLine);

			if(overdueItems.empty()){
				dummyLine += OVERDUE_NO_OVERDUE;
				overdueScreen.push_back(dummyLine);
			}
			else{
				vector<string> overdueList = constructOverdueList(overdueItems, displayCounter);
				overdueScreen.insert(overdueScreen.end(), overdueList.begin(), overdueList.end());
			}
		}
		else {
			overdueScreen.push_back(dummyLine);
		}
	}

	return overdueScreen;
}

vector<string> DisplayScreenConstructor::constructOverdueList(vector<Item*>overdueItems, int &displayCounter) {
	vector<string> overdueList;
	string overdueItem;

	for (vector<Item*>::iterator iter = overdueItems.begin(); iter != overdueItems.end(); iter++) {
		overdueItem = constructOverdueItemDisplay(iter, displayCounter);
		overdueList.push_back(overdueItem);
		displayCounter++;
	}

	return overdueList;
}

string DisplayScreenConstructor::constructOverdueItemDisplay(vector<Item*>::iterator iter, int displayCounter) {
	string overdueItem;
	overdueItem = to_string(displayCounter) + PERIOD;

	if ((*iter)->isDone()) {
		overdueItem += MARK_DONE;
	}

	overdueItem += (*iter)->getTitle() + OVERDUE_DUE + (*iter)->getEndDateInString();

	return overdueItem;
}

vector<string> DisplayScreenConstructor::constructEventList(vector<Item*> events, int &displayCounter) {
	vector<string> eventList;
	string event;

	for (vector<Item*>::iterator iter = events.begin(); iter != events.end(); iter++) {
		event = constructEventDisplay(iter, displayCounter);
		eventList.push_back(event);
		displayCounter++;
	}

	return eventList;
}

//This function constructs the details of a event into a string
string DisplayScreenConstructor::constructEventDisplay(vector<Item*>::iterator iter, int displayCounter) {
	string event;

	event = to_string(displayCounter) + PERIOD;

	if ((*iter)->isDone()) {
		event += MARK_DONE;
	}

	event += (*iter)->getTitle() + NEW_LINE; 
	event += FROM + (*iter)->getStartDateInString() + NEW_LINE;
	event += TO + (*iter)->getEndDateInString();

	return event;
}

vector<string> DisplayScreenConstructor::constructDeadlineList(vector<Item*> deadlines, int &displayCounter) {
	vector<string> deadlineList;
	string deadline;

	for (vector<Item*>::iterator iter = deadlines.begin(); iter != deadlines.end(); iter++) {
		deadline = constructDeadlineDisplay(iter, displayCounter);
		deadlineList.push_back(deadline);
		displayCounter++;
	}

	return deadlineList;
}

//This function constructs the details of a deadline into a string
string DisplayScreenConstructor::constructDeadlineDisplay(vector<Item*>::iterator iter, int displayCounter) {
	string deadline;

	deadline = to_string(displayCounter) + PERIOD;

	if ((*iter)->isDone()) {
		deadline += MARK_DONE;
	}

	deadline += (*iter)->getTitle() + NEW_LINE;
	deadline += BY + (*iter)->getEndDateInString();

	return deadline;
}

vector<string> DisplayScreenConstructor::constructTaskList(vector<Item*> tasks, int &displayCounter) {
	vector<string> taskList;
	string task;

	for (vector<Item*>::iterator iter = tasks.begin(); iter != tasks.end(); iter++) {
		task = constructTaskDisplay(iter, displayCounter);
		taskList.push_back(task);
		displayCounter++;
	}

	return taskList;
}

//This function constructs the details of a task into a string
string DisplayScreenConstructor::constructTaskDisplay(vector<Item*>::iterator iter, int displayCounter) {
	string task;

	task = to_string(displayCounter) + PERIOD;

	if ((*iter)->isDone()) {
		task += MARK_DONE;
	}

	task += (*iter)->getTitle();

	return task;
}

void DisplayScreenConstructor::exportToFile(vector<string>displayScreen) {
	Exporter* exporter = Exporter::getInstance();
	exporter->writeToFile(displayScreen);
}

//@author A0116781A-unused
//after moving away from CLI, we no longer need to clear screen with this method.
vector<string> DisplayScreenConstructor::clearScreen() {
	outputMessageStorage.clear();
	for (int i = 0; i != 50; i++) {
		outputMessageStorage.push_back(BLANK);
	}
	return outputMessageStorage;
}