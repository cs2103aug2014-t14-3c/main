#include "stdafx.h"
#include "OutputConstructor.h"

vector<Item*> OutputConstructor::currentDisplayedItemList;
OutputConstructor::CurrentScreenType OutputConstructor::currentScreen = OutputConstructor::CurrentScreenType::HOME_SCREEN;

string TITLE = "Title:       ";
string DESCRIPTION = "Description: ";
string START = "Start:       ";
string END = "End:        ";
string VENUE = "Venue:       ";
string PRIORITY = "Priority:    ";
string CATEGORY = "Category:    ";	
string DIVIDER = "================================================================================"; 

vector<string> OutputConstructor::constructOutput(OutputConstructor::CurrentScreenType newScreen) {
	vector<string> filler;

	return filler;
}

void OutputConstructor::resetCurrentItemList() {
	currentDisplayedItemList.clear();
}

void OutputConstructor::addItemToDisplayList(Item* itemPtr) {
	currentDisplayedItemList.push_back(itemPtr);
}

vector<string> OutputConstructor::addItemToVector(vector<string> targetVector, Item* itemPtr) {
	vector<string> item;
	string lineContent;
	
	lineContent = TITLE + itemPtr->getTitle();
	item.push_back(lineContent);

	lineContent = DESCRIPTION + itemPtr->getDescription();
	item.push_back(lineContent);

	lineContent = START + dateToString(&(itemPtr->getStartDateTime()));
	item.push_back(lineContent);

	lineContent = END + dateToString(&(itemPtr->getEndDateTime()));
	item.push_back(lineContent);

	lineContent = VENUE + itemPtr->getVenue();
	item.push_back(lineContent);

	lineContent = PRIORITY + priorityToString(itemPtr->getPriority());
	item.push_back(lineContent);

	lineContent = CATEGORY + itemPtr->getCategory();
	item.push_back(lineContent);

	addItemToDisplayList(itemPtr);

	copy(item.begin(), item.end(), targetVector.end());
	
	return targetVector;
}

string OutputConstructor::dateToString(tm* date) {
	char buffer[MAX_SIZE];
	
	strftime(buffer, MAX_SIZE, "%d %b %I:%M%p", date);

	string str(buffer);

	return str;
}

string OutputConstructor::priorityToString(Item::PriorityLevel priority) {
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