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
	ifstream mytextfile ("JustAddIt/Templates/HomeScreen.txt");
	string dummyLine;
	int resultCounter = 1;

	outputMessageStorage.clear();

	while (!mytextfile.eof()) {
		getline(mytextfile, dummyLine);

		if (dummyLine == "<u>What's going on this week?</u>") {
			outputMessageStorage.push_back(dummyLine);

			getline(mytextfile, dummyLine);
			outputMessageStorage.push_back(dummyLine);
			if(events.empty() && deadlines.empty() && tasks.empty()){
				dummyLine += "<span style=\"color:#d3d3d3;\">You're clear for the week!</span>";
				outputMessageStorage.push_back(dummyLine);
			}
			else{
				for (vector<Item*>::iterator iter = events.begin(); iter != events.end(); iter++) {
					dummyLine = to_string(resultCounter) + ". ";

					if ((*iter)->isDone()) {
						dummyLine += "<span style=\"color:#CC0000;\">[DONE]</span> ";
					}

					dummyLine += (*iter)->getTitle() + " from " + (*iter)->getStartDateInString() + " to " + (*iter)->getEndDateInString();

					outputMessageStorage.push_back(dummyLine);
					resultCounter++;
				}
				for (vector<Item*>::iterator iter = deadlines.begin(); iter != deadlines.end(); iter++) {
					dummyLine = to_string(resultCounter) + ". ";

					if ((*iter)->isDone()) {
						dummyLine += "<span style=\"color:#CC0000;\">[DONE]</span> ";
					}

					dummyLine += (*iter)->getTitle() + " by " + (*iter)->getEndDateInString();

					outputMessageStorage.push_back(dummyLine);
					resultCounter++;
				}
				for (vector<Item*>::iterator iter = tasks.begin(); iter != tasks.end(); iter++) {
					dummyLine = to_string(resultCounter) + ". ";

					if ((*iter)->isDone()) {
						dummyLine += "<span style=\"color:#CC0000;\">[DONE]</span> ";
					}

					dummyLine += (*iter)->getTitle();

					outputMessageStorage.push_back(dummyLine);
					resultCounter++;
				}
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
	ifstream mytextfile ("JustAddIt/Templates/EditScreen.txt");
	string dummyLine;

	outputMessageStorage.clear();

	while (!mytextfile.eof()) {
		getline(mytextfile, dummyLine);

		if (dummyLine == "<u>Edit ") {
			dummyLine += item->getItemTypeInString();
		}
		else if (dummyLine == "1) Title: ") {

			if (item->isDone()) {
				dummyLine += "<span style=\"color:#CC0000;\">[DONE]</span>  ";
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
	ifstream mytextfile ("JustAddIt/Templates/SearchScreen.txt");
	string dummyLine;
	int resultCounter = 1;

	outputMessageStorage.clear();

	while (!mytextfile.eof()) {
		getline(mytextfile, dummyLine);

		if (dummyLine == "<u>Showing results:") {
			outputMessageStorage.push_back(dummyLine);

			getline(mytextfile, dummyLine);
			outputMessageStorage.push_back(dummyLine);
			if(events.empty() && deadlines.empty() && tasks.empty()){
				dummyLine += "<span style=\"color:#d3d3d3;\">No results found.</span>";
				outputMessageStorage.push_back(dummyLine);
			}
			else{
				for (vector<Item*>::iterator iter = events.begin(); iter != events.end(); iter++) {
					dummyLine = to_string(resultCounter) + ". ";

					if ((*iter)->isDone()) {
						dummyLine += "<span style=\"color:#CC0000;\">[DONE]</span>  ";
					}

					dummyLine += (*iter)->getTitle() + " from " + (*iter)->getStartDateInString() + " to " + (*iter)->getEndDateInString();

					outputMessageStorage.push_back(dummyLine);
					resultCounter++;
				}
				for (vector<Item*>::iterator iter = deadlines.begin(); iter != deadlines.end(); iter++) {
					dummyLine = to_string(resultCounter) + ". ";

					if ((*iter)->isDone()) {
						dummyLine += "<span style=\"color:#CC0000;\">[DONE]</span>  ";
					}

					dummyLine += (*iter)->getTitle() + " by " + (*iter)->getEndDateInString();

					outputMessageStorage.push_back(dummyLine);
					resultCounter++;
				}
				for (vector<Item*>::iterator iter = tasks.begin(); iter != tasks.end(); iter++) {
					dummyLine = to_string(resultCounter) + ". ";

					if ((*iter)->isDone()) {
						dummyLine += "<span style=\"color:#CC0000;\">[DONE]</span>  ";
					}

					dummyLine += (*iter)->getTitle();

					outputMessageStorage.push_back(dummyLine);
					resultCounter++;
				}
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
	ifstream mytextfile ("JustAddIt/Templates/ListViewScreen.txt");
	string dummyLine;
	int resultCounter = 1;
	vector<Item*>::iterator iter;

	outputMessageStorage.clear();

	while (!mytextfile.eof()) {
		getline(mytextfile, dummyLine);

		if (dummyLine == "<u>All Events</u>") {
			outputMessageStorage.push_back(dummyLine);
			getline(mytextfile, dummyLine);
			outputMessageStorage.push_back(dummyLine);

			if(events.empty()){
				dummyLine += "<span style=\"color:#d3d3d3;\">No events found</span>";
				outputMessageStorage.push_back(dummyLine);
			}
			else{
				for (vector<Item*>::iterator iter = events.begin(); iter != events.end(); iter++) {
					dummyLine = to_string(resultCounter) + ". ";

					if ((*iter)->isDone()) {
						dummyLine += "<span style=\"color:#CC0000;\">[DONE]</span>  ";
					}

					dummyLine += (*iter)->getTitle() + "<br>" + "&nbsp;&nbsp;&nbsp;&nbsp;from: " + (*iter)->getStartDateInString() + "<br>" + "&nbsp;&nbsp;&nbsp;&nbsp;to:&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;" + (*iter)->getEndDateInString();

					outputMessageStorage.push_back(dummyLine);
					resultCounter++;
				}
			}

			getline(mytextfile, dummyLine);
			outputMessageStorage.push_back(dummyLine);
			getline(mytextfile, dummyLine);
			outputMessageStorage.push_back(dummyLine);
			getline(mytextfile, dummyLine);
			outputMessageStorage.push_back(dummyLine);
			if(deadlines.empty()){
				dummyLine += "<span style=\"color:#d3d3d3;\">No deadlines found</span>";
				outputMessageStorage.push_back(dummyLine);
			}
			else{
				for (vector<Item*>::iterator iter = deadlines.begin(); iter != deadlines.end(); iter++) {
					dummyLine = to_string(resultCounter) + ". ";

					if ((*iter)->isDone()) {
						dummyLine += "<span style=\"color:#CC0000;\">[DONE]</span>  ";
					}

					dummyLine += (*iter)->getTitle() + " by " + (*iter)->getEndDateInString();

					outputMessageStorage.push_back(dummyLine);
					resultCounter++;
				}
			}


			getline(mytextfile, dummyLine);
			outputMessageStorage.push_back(dummyLine);
			getline(mytextfile, dummyLine);
			outputMessageStorage.push_back(dummyLine);
			getline(mytextfile, dummyLine);
			outputMessageStorage.push_back(dummyLine);
			if(tasks.empty()){
				dummyLine += "<span style=\"color:#d3d3d3;\">No tasks found</span>";
				outputMessageStorage.push_back(dummyLine);
			}
			else{
				for (vector<Item*>::iterator iter = tasks.begin(); iter != tasks.end(); iter++) {
					dummyLine = to_string(resultCounter) + ". ";

					if ((*iter)->isDone()) {
						dummyLine += "<span style=\"color:#CC0000;\">[DONE]</span>  ";
					}

					dummyLine += (*iter)->getTitle();

					outputMessageStorage.push_back(dummyLine);
					resultCounter++;
				}
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
	ifstream mytextfile ("JustAddIt/Templates/OverdueScreen.txt");
	string dummyLine;
	int resultCounter = 1;
	vector<Item*>::iterator iter;

	outputMessageStorage.clear();

	while (!mytextfile.eof()) {
		getline(mytextfile, dummyLine);
		if (dummyLine == "<u>Overdue Deadlines") {
			outputMessageStorage.push_back(dummyLine);

			getline(mytextfile, dummyLine);
			outputMessageStorage.push_back(dummyLine);
			if(items.empty()){
				dummyLine += "<span style=\"color:#d3d3d3;\">All caught up! Nothing is overdue.</span>";
				outputMessageStorage.push_back(dummyLine);
			}
			else{
				for (iter = items.begin(); iter != items.end(); iter++) {
					dummyLine = to_string(resultCounter) + ". ";

					if ((*iter)->isDone()) {
						dummyLine += "<span style=\"color:#CC0000;\">[DONE]</span>  ";
					}

					dummyLine += (*iter)->getTitle() + " was due " + (*iter)->getEndDateInString();

					outputMessageStorage.push_back(dummyLine);
					resultCounter++;
				}
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

//@author A0116781A-unused
vector<string> DisplayScreenConstructor::clearScreen() {
	outputMessageStorage.clear();
	for (int i = 0; i != 50; i++) {
		outputMessageStorage.push_back("");
	}
	return outputMessageStorage;
}