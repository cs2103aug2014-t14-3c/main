#include "stdafx.h"
#include "DisplayScreenConstructor.h"

using namespace std;

DisplayScreenConstructor* DisplayScreenConstructor::displayScreenConstructor = NULL;

DisplayScreenConstructor::DisplayScreenConstructor(void){
}

DisplayScreenConstructor::~DisplayScreenConstructor(void) {
}

DisplayScreenConstructor* DisplayScreenConstructor::getInstance(void) {
	if (displayScreenConstructor == NULL) {
		displayScreenConstructor = new DisplayScreenConstructor();
	}
	return displayScreenConstructor;
}

vector<string> DisplayScreenConstructor::constructHomeScreen(vector<Item*>tasksToBeDisplayed, vector<Item*>deadlinesToBeDisplayed, vector<Item*>eventsToBeDisplayed) {
	ifstream mytextfile ("HomeScreen.txt");
	string dummyLine;
	int resultCounter = 1;

	while (!mytextfile.eof()) {
		getline(mytextfile, dummyLine);

		if (dummyLine == "What's going on this week?") {
			outputMessageStorage.push_back(dummyLine);

			for (vector<Item*>::iterator iter = eventsToBeDisplayed.begin(); iter != eventsToBeDisplayed.end(); iter++) {
				dummyLine = to_string(resultCounter) + ". " + (*iter)->getTitle() + " from " + (*iter)->getStartDateInString() + " to " + (*iter)->getEndDateInString();
				outputMessageStorage.push_back(dummyLine);
				resultCounter++;
			}
			for (vector<Item*>::iterator iter = deadlinesToBeDisplayed.begin(); iter != deadlinesToBeDisplayed.end(); iter++) {
				dummyLine = to_string(resultCounter) + ". " + (*iter)->getTitle() + " by " + (*iter)->getEndDateInString();
				outputMessageStorage.push_back(dummyLine);
				resultCounter++;
			}
			for (vector<Item*>::iterator iter = tasksToBeDisplayed.begin(); iter != tasksToBeDisplayed.end(); iter++) {
				dummyLine = to_string(resultCounter) + ". " + (*iter)->getTitle();
				outputMessageStorage.push_back(dummyLine);
				resultCounter++;
			}
		}
		else {
			outputMessageStorage.push_back(dummyLine);
		}
	}
	return outputMessageStorage;
}

vector<string> DisplayScreenConstructor::constructEditScreen(Item* item) {
	ifstream mytextfile ("EditScreen.txt");
	string dummyLine;

	while (!mytextfile.eof()) {
		getline(mytextfile, dummyLine);

		if (dummyLine == "Edit ") {
			dummyLine += item->getItemType();
		}
		else if (dummyLine == "1) Title: ") {
			dummyLine += item->getTitle();
			if (item->getIsDone() == true) {
				dummyLine += " *Done*";
			}
		}
		else if (dummyLine == "2) Description: ") {
			if (item->getDescription() == "-") {
				dummyLine += "";
			}
			else {
				dummyLine += item->getDescription();
			}
		}
		else if (dummyLine == "3) Start: ") {
			if (item->getItemType() == "task" || item->getItemType() == "deadline") {
				dummyLine += "";
			}
			else {
				dummyLine += item->getStartDateInString();
			}
		}
		else if (dummyLine == "4) End: ") {
			if (item->getItemType() == "task") {
				dummyLine += "";
			}
			else {
				dummyLine += item->getEndDateInString();
			}
		}
		else if (dummyLine == "5) Priority: ") {
			dummyLine += item->getPriorityInString();
		}
		else if (dummyLine == "6) Category: ") {
			if (item->getCategory() == "-") {
				dummyLine += "";
			}
			else {
				dummyLine += item->getCategory();
			}
		}

		outputMessageStorage.push_back(dummyLine);
	}

	return outputMessageStorage;
}

vector<string> DisplayScreenConstructor::constructSearchScreen(vector<Item*>tasksToBeDisplayed, vector<Item*>deadlinesToBeDisplayed, vector<Item*>eventsToBeDisplayed) {
	ifstream mytextfile ("SearchScreen.txt");
	string dummyLine;
	int resultCounter = 1;

	while (!mytextfile.eof()) {
		getline(mytextfile, dummyLine);

		if (dummyLine == "Showing results:") {
			outputMessageStorage.push_back(dummyLine);

			for (vector<Item*>::iterator iter = eventsToBeDisplayed.begin(); iter != eventsToBeDisplayed.end(); iter++) {
				dummyLine = to_string(resultCounter) + ". " + (*iter)->getTitle() + " from " + (*iter)->getStartDateInString() + " to " + (*iter)->getEndDateInString();
				outputMessageStorage.push_back(dummyLine);
				resultCounter++;
			}
			for (vector<Item*>::iterator iter = deadlinesToBeDisplayed.begin(); iter != deadlinesToBeDisplayed.end(); iter++) {
				dummyLine = to_string(resultCounter) + ". " + (*iter)->getTitle() + " by " + (*iter)->getEndDateInString();
				outputMessageStorage.push_back(dummyLine);
				resultCounter++;
			}
			for (vector<Item*>::iterator iter = tasksToBeDisplayed.begin(); iter != tasksToBeDisplayed.end(); iter++) {
				dummyLine = to_string(resultCounter) + ". " + (*iter)->getTitle();
				outputMessageStorage.push_back(dummyLine);
				resultCounter++;
			}
		}
		else {
			outputMessageStorage.push_back(dummyLine);
		}
	}
	return outputMessageStorage;
}

vector<string> DisplayScreenConstructor::constructListScreen(vector<Item*>tasksToBeDisplayed, vector<Item*>deadlinesToBeDisplayed, vector<Item*>eventsToBeDisplayed) {
	ifstream mytextfile ("ListViewScreen.txt");
	string dummyLine;
	int resultCounter = 1;
	vector<Item*>::iterator iter;

	while (!mytextfile.eof()) {
		getline(mytextfile, dummyLine);

		if (dummyLine == "All Events") {
			outputMessageStorage.push_back(dummyLine);
			getline(mytextfile, dummyLine);
			outputMessageStorage.push_back(dummyLine);

			for (vector<Item*>::iterator iter = eventsToBeDisplayed.begin(); iter != eventsToBeDisplayed.end(); iter++) {
				dummyLine = to_string(resultCounter) + ". " + (*iter)->getTitle() + " from " + (*iter)->getStartDateInString() + " to " + (*iter)->getEndDateInString();
				outputMessageStorage.push_back(dummyLine);
				resultCounter++;
			}

			getline(mytextfile, dummyLine);
			outputMessageStorage.push_back(dummyLine);
			getline(mytextfile, dummyLine);
			outputMessageStorage.push_back(dummyLine);
			getline(mytextfile, dummyLine);
			outputMessageStorage.push_back(dummyLine);
			getline(mytextfile, dummyLine);
			outputMessageStorage.push_back(dummyLine);

			for (vector<Item*>::iterator iter = deadlinesToBeDisplayed.begin(); iter != deadlinesToBeDisplayed.end(); iter++) {
				dummyLine = to_string(resultCounter) + ". " + (*iter)->getTitle() + " by " + (*iter)->getEndDateInString();
				outputMessageStorage.push_back(dummyLine);
				resultCounter++;
			}

			getline(mytextfile, dummyLine);
			outputMessageStorage.push_back(dummyLine);
			getline(mytextfile, dummyLine);
			outputMessageStorage.push_back(dummyLine);
			getline(mytextfile, dummyLine);
			outputMessageStorage.push_back(dummyLine);
			getline(mytextfile, dummyLine);
			outputMessageStorage.push_back(dummyLine);

			for (vector<Item*>::iterator iter = tasksToBeDisplayed.begin(); iter != tasksToBeDisplayed.end(); iter++) {
				dummyLine = to_string(resultCounter) + ". " + (*iter)->getTitle();
				outputMessageStorage.push_back(dummyLine);
				resultCounter++;
			}
		}
		else {
			outputMessageStorage.push_back(dummyLine);
		}
	}
	return outputMessageStorage;
}

vector<string> DisplayScreenConstructor::constructCalendarScreen(vector<Item*>itemsToBeDisplayed) {
	ifstream mytextfile ("CalendarViewScreen.txt");
	string dummyLine;
	int resultCounter = 1;
	vector<Item*>::iterator iter;

	while (!mytextfile.eof()) {
		getline(mytextfile, dummyLine);
		if (dummyLine == "All happenings within this month:") {
			outputMessageStorage.push_back(dummyLine);
			getline(mytextfile, dummyLine);
			outputMessageStorage.push_back(dummyLine);

			for (iter = itemsToBeDisplayed.begin(); iter != itemsToBeDisplayed.end(); iter++) {
				if ((*iter)->getItemType() == "event") {
					dummyLine = to_string(resultCounter) + ". " + (*iter)->getTitle() + " from " + (*iter)->getStartDateInString() + " to " + (*iter)->getEndDateInString();
					outputMessageStorage.push_back(dummyLine);
					dummyLine = "";
					outputMessageStorage.push_back(dummyLine);
				}
				else if ((*iter)->getItemType() == "deadline") {
					dummyLine = to_string(resultCounter) + ". " + (*iter)->getTitle() + " by " + (*iter)->getEndDateInString();
					outputMessageStorage.push_back(dummyLine);
					dummyLine = "";
					outputMessageStorage.push_back(dummyLine);
				}
				else {
					dummyLine = "getItemType is not one of the 2 accepted inputs";
					outputMessageStorage.push_back(dummyLine);
					dummyLine = "";
					outputMessageStorage.push_back(dummyLine);
				}
				resultCounter++;
			}
		}
	}

	return outputMessageStorage;
}

vector<string> DisplayScreenConstructor::constructOverdueScreen(vector<Item*>itemsToBeDisplayed) {
	ifstream mytextfile ("OverdueScreen.txt");
	string dummyLine;
	int resultCounter = 1;
	vector<Item*>::iterator iter;

	while (!mytextfile.eof()) {
		getline(mytextfile, dummyLine);
		if (dummyLine == "Overdue Deadlines") {
			outputMessageStorage.push_back(dummyLine);

			for (iter = itemsToBeDisplayed.begin(); iter != itemsToBeDisplayed.end(); iter++) {
				dummyLine = to_string(resultCounter) + ". " + (*iter)->getTitle() + " was due " + (*iter)->getEndDateInString();
				outputMessageStorage.push_back(dummyLine);
				resultCounter++;
			}
		}
		else {
			outputMessageStorage.push_back(dummyLine);
		}
	}
	return outputMessageStorage;
}

vector<string> DisplayScreenConstructor::clearScreen() {
	outputMessageStorage.clear();
	for (int i = 0; i != 50; i++) {
		outputMessageStorage.push_back("");
	}
	return outputMessageStorage;
}