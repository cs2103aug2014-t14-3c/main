#include "stdafx.h"
#include "OutputControl.h"

vector<Item*> OutputControl::currentDisplayedItemList;
OutputControl::CurrentScreenType OutputControl::currentScreen = OutputControl::CurrentScreenType::HOME_SCREEN;

void OutputControl::resetCurrentItemList() {
	currentDisplayedItemList.clear();
}

void OutputControl::addItemToDisplayList(Item* itemPtr) {
	currentDisplayedItemList.push_back(itemPtr);
}

void OutputControl::setCurrentScreen(CurrentScreenType newScreen) {
	currentScreen = newScreen;
}
void OutputControl::setCurrentDisplayedItemList(vector<Item*> newList){
	resetCurrentItemList();
	currentDisplayedItemList=newList;
}
Item* OutputControl::getItemAddr(int itemLocationInList) {
	return currentDisplayedItemList[itemLocationInList];
}

vector<Item*>::iterator OutputControl::getCurrentDisplayedItemList(){
	return currentDisplayedItemList.begin();
}
OutputControl::CurrentScreenType OutputControl::getCurrentScreen(){
	return currentScreen;
}