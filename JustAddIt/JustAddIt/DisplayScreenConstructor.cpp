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

vector<string> DisplayScreenConstructor::constructHomeScreen() {
	ifstream mytextfile ("HomeScreen.txt");
	string dummyLine;

	while (!mytextfile.eof()) {
		getline(mytextfile, dummyLine);
		outputMessageStorage.push_back(dummyLine);
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
			dummyLine += item->getDescription();
		}
		else if (dummyLine == "3) Start: ") {
			dummyLine += item->getStartDateInString();
		}
		else if (dummyLine == "4) End: ") {
			dummyLine += item->getEndDateInString();
		}
		else if (dummyLine == "5) Priority: ") {
			dummyLine += item->getPriorityInString();
		}
		else if (dummyLine == "6) Category: ") {
			dummyLine += item->getCategory();
		}

		outputMessageStorage.push_back(dummyLine);
	}

	return outputMessageStorage;
}

vector<string> DisplayScreenConstructor::constructSearchScreen(vector<Item*>itemsToBeDisplayed) {
	ifstream mytextfile ("SearchScreen.txt");
	string dummyLine;
	int resultCounter = 1;
	vector<Item*>::iterator iter;

	while (!mytextfile.eof()) {
		getline(mytextfile, dummyLine);
		if (dummyLine == "Showing results:") {
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
				else if ((*iter)->getItemType() == "task") {
					dummyLine = to_string(resultCounter) + ". " + (*iter)->getTitle();
					outputMessageStorage.push_back(dummyLine);
					dummyLine = "";
					outputMessageStorage.push_back(dummyLine);
				}
				else {
					dummyLine = "getItemType is not one of the 3 accepted inputs";
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

vector<string> DisplayScreenConstructor::constructListScreen_1Week(vector<Item*>itemsToBeDisplayed) {
	ifstream mytextfile ("ListViewScreen(1 week).txt");
	string dummyLine;
	int resultCounter = 1;
	vector<Item*>::iterator iter;

	while (!mytextfile.eof()) {
		getline(mytextfile, dummyLine);
		if (dummyLine == "Deadlines due in a week") {
			outputMessageStorage.push_back(dummyLine);
			getline(mytextfile, dummyLine);
			outputMessageStorage.push_back(dummyLine);
			for (iter = itemsToBeDisplayed.begin(); iter != itemsToBeDisplayed.end(); iter++) {
				if ((*iter)->getItemType() == "deadline") {
					dummyLine = to_string(resultCounter) + ". " + (*iter)->getTitle() + " by " + (*iter)->getEndDateInString();
					outputMessageStorage.push_back(dummyLine);
					dummyLine = "";
					outputMessageStorage.push_back(dummyLine);
				}
				resultCounter++;
			}
		}

		if (dummyLine == "Tasks") {
			outputMessageStorage.push_back(dummyLine);
			getline(mytextfile, dummyLine);
			outputMessageStorage.push_back(dummyLine);
			for (iter = itemsToBeDisplayed.begin(); iter != itemsToBeDisplayed.end(); iter++) {
				if ((*iter)->getItemType() == "tasks") {
					dummyLine = to_string(resultCounter) + ". " + (*iter)->getTitle();
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

vector<string> DisplayScreenConstructor::constructListScreen_2Weeks(vector<Item*>itemsToBeDisplayed) {
	ifstream mytextfile ("ListViewScreen(2 weeks).txt");
	string dummyLine;
	int resultCounter = 1;
	vector<Item*>::iterator iter;

	while (!mytextfile.eof()) {
		getline(mytextfile, dummyLine);
		if (dummyLine == "Deadlines due in 2 weeks") {
			outputMessageStorage.push_back(dummyLine);
			getline(mytextfile, dummyLine);
			outputMessageStorage.push_back(dummyLine);
			for (iter = itemsToBeDisplayed.begin(); iter != itemsToBeDisplayed.end(); iter++) {
				if ((*iter)->getItemType() == "deadline") {
					dummyLine = to_string(resultCounter) + ". " + (*iter)->getTitle() + " by " + (*iter)->getEndDateInString();
					outputMessageStorage.push_back(dummyLine);
					dummyLine = "";
					outputMessageStorage.push_back(dummyLine);
				}
				resultCounter++;
			}
		}

		if (dummyLine == "Tasks") {
			outputMessageStorage.push_back(dummyLine);
			getline(mytextfile, dummyLine);
			outputMessageStorage.push_back(dummyLine);
			for (iter = itemsToBeDisplayed.begin(); iter != itemsToBeDisplayed.end(); iter++) {
				if ((*iter)->getItemType() == "tasks") {
					dummyLine = to_string(resultCounter) + ". " + (*iter)->getTitle();
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

vector<string> DisplayScreenConstructor::constructListScreen_3Weeks(vector<Item*>itemsToBeDisplayed) {
	ifstream mytextfile ("ListViewScreen(3 weeks).txt");
	string dummyLine;
	int resultCounter = 1;
	vector<Item*>::iterator iter;

	while (!mytextfile.eof()) {
		getline(mytextfile, dummyLine);
		if (dummyLine == "Deadlines due in 3 weeks") {
			outputMessageStorage.push_back(dummyLine);
			getline(mytextfile, dummyLine);
			outputMessageStorage.push_back(dummyLine);
			for (iter = itemsToBeDisplayed.begin(); iter != itemsToBeDisplayed.end(); iter++) {
				if ((*iter)->getItemType() == "deadline") {
					dummyLine = to_string(resultCounter) + ". " + (*iter)->getTitle() + " by " + (*iter)->getEndDateInString();
					outputMessageStorage.push_back(dummyLine);
					dummyLine = "";
					outputMessageStorage.push_back(dummyLine);
				}
				resultCounter++;
			}
		}

		if (dummyLine == "Tasks") {
			outputMessageStorage.push_back(dummyLine);
			getline(mytextfile, dummyLine);
			outputMessageStorage.push_back(dummyLine);
			for (iter = itemsToBeDisplayed.begin(); iter != itemsToBeDisplayed.end(); iter++) {
				if ((*iter)->getItemType() == "tasks") {
					dummyLine = to_string(resultCounter) + ". " + (*iter)->getTitle();
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

vector<string> DisplayScreenConstructor::constructListScreen_Month(vector<Item*>itemsToBeDisplayed) {
	ifstream mytextfile ("ListViewScreen(month).txt");
	string dummyLine;
	int resultCounter = 1;
	vector<Item*>::iterator iter;

	while (!mytextfile.eof()) {
		getline(mytextfile, dummyLine);
		if (dummyLine == "Deadlines due in a month") {
			outputMessageStorage.push_back(dummyLine);
			getline(mytextfile, dummyLine);
			outputMessageStorage.push_back(dummyLine);
			for (iter = itemsToBeDisplayed.begin(); iter != itemsToBeDisplayed.end(); iter++) {
				if ((*iter)->getItemType() == "deadline") {
					dummyLine = to_string(resultCounter) + ". " + (*iter)->getTitle() + " by " + (*iter)->getEndDateInString();
					outputMessageStorage.push_back(dummyLine);
					dummyLine = "";
					outputMessageStorage.push_back(dummyLine);
				}
				resultCounter++;
			}
		}

		if (dummyLine == "Tasks") {
			outputMessageStorage.push_back(dummyLine);
			getline(mytextfile, dummyLine);
			outputMessageStorage.push_back(dummyLine);
			for (iter = itemsToBeDisplayed.begin(); iter != itemsToBeDisplayed.end(); iter++) {
				if ((*iter)->getItemType() == "tasks") {
					dummyLine = to_string(resultCounter) + ". " + (*iter)->getTitle();
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
		if (dummyLine == "Overdue Deadlines") {
			outputMessageStorage.push_back(dummyLine);
			getline(mytextfile, dummyLine);
			outputMessageStorage.push_back(dummyLine);
			for (iter = itemsToBeDisplayed.begin(); iter != itemsToBeDisplayed.end(); iter++) {
				if ((*iter)->getItemType() == "deadline") {
					dummyLine = to_string(resultCounter) + ". " + (*iter)->getTitle() + " was due " + (*iter)->getEndDateInString();
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

vector<string> DisplayScreenConstructor::clearScreen() {
	outputMessageStorage.clear();
	for (int i = 0; i != 50; i++) {
	outputMessageStorage.push_back("");
	}
	return outputMessageStorage;
}