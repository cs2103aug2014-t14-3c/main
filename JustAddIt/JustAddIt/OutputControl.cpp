#include "stdafx.h"
#include "Command.h"
#include "OutputControl.h"

vector<Item*> OutputControl::currentDisplayedItemList;
OutputControl::CurrentScreenType OutputControl::currentScreen = OutputControl::CurrentScreenType::HOME_SCREEN;
OutputControl::CurrentScreenType OutputControl::currentBaseScreen = OutputControl::CurrentScreenType::HOME_SCREEN;
string OutputControl::currentKeywordSearched;
void OutputControl::resetCurrentItemList() {
	currentDisplayedItemList.clear();
}

void OutputControl::addItemToDisplayList(Item* itemPtr) {
	currentDisplayedItemList.push_back(itemPtr);
}

void OutputControl::setCurrentScreen(CurrentScreenType newScreen) {
	currentScreen = newScreen;
}
void OutputControl::setCurrentBaseScreen(CurrentScreenType newScreen){
	currentBaseScreen = newScreen;
}

void OutputControl::setCurrentDisplayedItemList(vector<Item*> newList){
	resetCurrentItemList();
	currentDisplayedItemList=newList;
}

void OutputControl::setCurrentKeywordSearched(string keyword){
	currentKeywordSearched=keyword;
}

int OutputControl::getNumberOfDisplayedItems(){
	return currentDisplayedItemList.size();
}
Item* OutputControl::getItemAddr(int itemLocationInList) {
	return currentDisplayedItemList[itemLocationInList-1];
}

vector<Item*>::iterator OutputControl::getCurrentDisplayedItemList(){
	return currentDisplayedItemList.begin();
}
OutputControl::CurrentScreenType OutputControl::getCurrentScreen(){
	return currentScreen;
}

OutputControl::CurrentScreenType OutputControl::getCurrentBaseScreen(){
	return currentBaseScreen;
}

string OutputControl::getCurrentKeywordSearched(){
	return currentKeywordSearched;
}
