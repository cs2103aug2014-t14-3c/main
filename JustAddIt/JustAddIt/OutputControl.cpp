#include "stdafx.h"
#include "OutputControl.h"

vector<Item*> OutputControl::currentDisplayedItemList;
OutputControl::CurrentScreenType OutputControl::currentScreen = OutputControl::CurrentScreenType::HOME_SCREEN;

/*vector<string> OutputControl::constructOutput(OutputControl::CurrentScreenType newScreen) {
	vector<string> filler;
	Item item;
	
	item.setTitle("hi");
	item.setVenue("lounge");

	filler = addItemToVector(filler, &item);

	return filler;
}*/

void OutputControl::resetCurrentItemList() {
	currentDisplayedItemList.clear();
}

void OutputControl::addItemToDisplayList(Item* itemPtr) {
	currentDisplayedItemList.push_back(itemPtr);
}

void OutputControl::setCurrentScreen(CurrentScreenType newScreen) {
	currentScreen = newScreen;
}

Item* OutputControl::getItemAddr(int itemLocationInList) {
	return currentDisplayedItemList[itemLocationInList];
}


/*vector<string> OutputControl::addItemToVector(vector<string> targetVector, Item* itemPtr) {
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

*/