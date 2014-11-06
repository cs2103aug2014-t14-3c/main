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

vector<string> DisplayScreenConstructor::constructHomeScreen(vector<Item*>tasks, vector<Item*>deadlines, vector<Item*>events) {
	ifstream mytextfile ("../JustAddIt/HomeScreen.txt");
	string dummyLine;
	int resultCounter = 1;

	while (!mytextfile.eof()) {
		getline(mytextfile, dummyLine);

		if (dummyLine == "What's going on this week?") {
			outputMessageStorage.push_back(dummyLine);

			for (vector<Item*>::iterator iter = events.begin(); iter != events.end(); iter++) {
				dummyLine = to_string(resultCounter) + ". ";

				if ((*iter)->isDone()) {
					dummyLine += "[DONE] ";
				}

				dummyLine += (*iter)->getTitle() + " from " + (*iter)->getStartDateInString() + " to " + (*iter)->getEndDateInString();

				outputMessageStorage.push_back(dummyLine);
				resultCounter++;
			}
			for (vector<Item*>::iterator iter = deadlines.begin(); iter != deadlines.end(); iter++) {
				dummyLine = to_string(resultCounter) + ". ";

				if ((*iter)->isDone()) {
					dummyLine += "[DONE] ";
				}

				dummyLine += (*iter)->getTitle() + " by " + (*iter)->getEndDateInString();

				outputMessageStorage.push_back(dummyLine);
				resultCounter++;
			}
			for (vector<Item*>::iterator iter = tasks.begin(); iter != tasks.end(); iter++) {
				dummyLine = to_string(resultCounter) + ". ";

				if ((*iter)->isDone()) {
					dummyLine += "[DONE] ";
				}

				dummyLine += (*iter)->getTitle();

				outputMessageStorage.push_back(dummyLine);
				resultCounter++;
			}
		}
		else {
			outputMessageStorage.push_back(dummyLine);
		}
	}

	Exporter* exporter = Exporter::getInstance();
	exporter->writeToFile(outputMessageStorage);

	return outputMessageStorage;
}

vector<string> DisplayScreenConstructor::constructEditScreen(Item* item) {
	ifstream mytextfile ("../JustAddIt/EditScreen.txt");
	string dummyLine;

	while (!mytextfile.eof()) {
		getline(mytextfile, dummyLine);

		if (dummyLine == "Edit ") {
			dummyLine += item->getItemTypeInString();
		}
		else if (dummyLine == "1) Title: ") {

			if (item->isDone()) {
				dummyLine += "[DONE] ";
			}

			dummyLine += item->getTitle();

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
			if (item->isTask() || item->isDeadline()) {
				dummyLine += "";
			}
			else {
				dummyLine += item->getStartDateInString();
			}
		}
		else if (dummyLine == "4) End: ") {
			if (item->isTask()) {
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

	Exporter* exporter = Exporter::getInstance();
	exporter->writeToFile(outputMessageStorage);

	return outputMessageStorage;
}

vector<string> DisplayScreenConstructor::constructSearchScreen(vector<Item*>tasks, vector<Item*>deadlines, vector<Item*>events) {
	ifstream mytextfile ("../JustAddIt/SearchScreen.txt");
	string dummyLine;
	int resultCounter = 1;

	while (!mytextfile.eof()) {
		getline(mytextfile, dummyLine);

		if (dummyLine == "Showing results:") {
			outputMessageStorage.push_back(dummyLine);

			for (vector<Item*>::iterator iter = events.begin(); iter != events.end(); iter++) {
				dummyLine = to_string(resultCounter) + ". ";

				if ((*iter)->isDone()) {
					dummyLine += "[DONE] ";
				}

				dummyLine += (*iter)->getTitle() + " from " + (*iter)->getStartDateInString() + " to " + (*iter)->getEndDateInString();

				outputMessageStorage.push_back(dummyLine);
				resultCounter++;
			}
			for (vector<Item*>::iterator iter = deadlines.begin(); iter != deadlines.end(); iter++) {
				dummyLine = to_string(resultCounter) + ". ";

				if ((*iter)->isDone()) {
					dummyLine += "[DONE] ";
				}

				dummyLine += (*iter)->getTitle() + " by " + (*iter)->getEndDateInString();

				outputMessageStorage.push_back(dummyLine);
				resultCounter++;
			}
			for (vector<Item*>::iterator iter = tasks.begin(); iter != tasks.end(); iter++) {
				dummyLine = to_string(resultCounter) + ". ";

				if ((*iter)->isDone()) {
					dummyLine += "[DONE] ";
				}

				dummyLine += (*iter)->getTitle();

				outputMessageStorage.push_back(dummyLine);
				resultCounter++;
			}
		}
		else {
			outputMessageStorage.push_back(dummyLine);
		}
	}

	Exporter* exporter = Exporter::getInstance();
	exporter->writeToFile(outputMessageStorage);

	return outputMessageStorage;
}

vector<string> DisplayScreenConstructor::constructListScreen(vector<Item*>tasks, vector<Item*>deadlines, vector<Item*>events) {
	ifstream mytextfile ("../JustAddIt/ListViewScreen.txt");
	string dummyLine;
	int resultCounter = 1;
	vector<Item*>::iterator iter;

	while (!mytextfile.eof()) {
		getline(mytextfile, dummyLine);

		if (dummyLine == "All Events") {
			outputMessageStorage.push_back(dummyLine);
			getline(mytextfile, dummyLine);
			outputMessageStorage.push_back(dummyLine);

			for (vector<Item*>::iterator iter = events.begin(); iter != events.end(); iter++) {
				dummyLine = to_string(resultCounter) + ". ";

				if ((*iter)->isDone()) {
					dummyLine += "[DONE] ";
				}

				dummyLine += (*iter)->getTitle() + " from " + (*iter)->getStartDateInString() + " to " + (*iter)->getEndDateInString();

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

			for (vector<Item*>::iterator iter = deadlines.begin(); iter != deadlines.end(); iter++) {
				dummyLine = to_string(resultCounter) + ". ";

				if ((*iter)->isDone()) {
					dummyLine += "[DONE] ";
				}

				dummyLine += (*iter)->getTitle() + " by " + (*iter)->getEndDateInString();

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

			for (vector<Item*>::iterator iter = tasks.begin(); iter != tasks.end(); iter++) {
				dummyLine = to_string(resultCounter) + ". ";

				if ((*iter)->isDone()) {
					dummyLine += "[DONE] ";
				}

				dummyLine += (*iter)->getTitle();

				outputMessageStorage.push_back(dummyLine);
				resultCounter++;
			}
		}
		else {
			outputMessageStorage.push_back(dummyLine);
		}
	}

	Exporter* exporter = Exporter::getInstance();
	exporter->writeToFile(outputMessageStorage);

	return outputMessageStorage;
}

vector<string> DisplayScreenConstructor::constructOverdueScreen(vector<Item*>items) {
	ifstream mytextfile ("../JustAddIt/OverdueScreen.txt");
	string dummyLine;
	int resultCounter = 1;
	vector<Item*>::iterator iter;

	while (!mytextfile.eof()) {
		getline(mytextfile, dummyLine);
		if (dummyLine == "Overdue Deadlines") {
			outputMessageStorage.push_back(dummyLine);

			for (iter = items.begin(); iter != items.end(); iter++) {
				dummyLine = to_string(resultCounter) + ". ";

				if ((*iter)->isDone()) {
					dummyLine += "[DONE] ";
				}

				dummyLine += (*iter)->getTitle() + " was due " + (*iter)->getEndDateInString();

				outputMessageStorage.push_back(dummyLine);
				resultCounter++;
			}
		}
		else {
			outputMessageStorage.push_back(dummyLine);
		}
	}

	Exporter* exporter = Exporter::getInstance();
	exporter->writeToFile(outputMessageStorage);

	return outputMessageStorage;
}

vector<string> DisplayScreenConstructor::clearScreen() {
	outputMessageStorage.clear();
	for (int i = 0; i != 50; i++) {
		outputMessageStorage.push_back("");
	}
	return outputMessageStorage;
}