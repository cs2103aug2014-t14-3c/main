#include "stdafx.h"
#include "Command.h"

using namespace std;

const string Command::FORMAT_TITLE = "Title:       ";
const string Command::FORMAT_DESCRIPTION = "Description: ";
const string Command::FORMAT_START = "Start:       ";
const string Command::FORMAT_END = "End:        ";
const string Command::FORMAT_VENUE = "Venue:       ";
const string Command::FORMAT_PRIORITY = "Priority:    ";
const string Command::FORMAT_CATEGORY = "Category:    ";	
const string Command::FORMAT_DIVIDER = "================================================================================"; 

Command::Command(void)
{
}


Command::~Command(void)
{
}

string Command::priorityToString(Item::PriorityLevel priority) {
	switch(priority) {
		case Item::PriorityLevel::LOW:
			return "Low";
		case Item::PriorityLevel::MED:
			return "Medium";
		case Item::PriorityLevel::HIGH:
			return "High";
		case Item::PriorityLevel::INVALID:
			return "Invalid";
		default:
			return "";
	}
}

string Command::dateToString(tm* date) {
	char tempArray[MAX_SIZE];
	
	strftime(tempArray, MAX_SIZE, "%d %b %I:%M%p", date);

	string str(tempArray);

	return str;
}

vector<string> Command::itemToString(Item* itemPtr) {
	
	vector<string> item;
	string lineContent;
	
	lineContent = FORMAT_TITLE + itemPtr->getTitle();
	item.push_back(lineContent);

	lineContent = FORMAT_DESCRIPTION + itemPtr->getDescription();
	item.push_back(lineContent);

	lineContent = FORMAT_START + dateToString(&(itemPtr->getStartDateTime()));
	item.push_back(lineContent);

	lineContent = FORMAT_END + dateToString(&(itemPtr->getEndDateTime()));
	item.push_back(lineContent);

	lineContent = FORMAT_VENUE + itemPtr->getVenue();
	item.push_back(lineContent);

	lineContent = FORMAT_PRIORITY + priorityToString(itemPtr->getPriority());
	item.push_back(lineContent);

	lineContent = FORMAT_CATEGORY + itemPtr->getCategory();
	item.push_back(lineContent);

//	OutputControl::addItemToDisplayList(itemPtr); 

//	copy(item.begin(), item.end(), outputMessageStorage.end());
	
	return item;
}

vector<string> Command::constructOutput() {
	outputMessageStorage.clear();
	return outputMessageStorage;
}

vector<string> Command::execute() {
	outputMessageStorage.clear();
	return outputMessageStorage;
}

