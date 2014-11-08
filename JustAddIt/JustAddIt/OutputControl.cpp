#include "stdafx.h"
//@author A0110770U
#include "Command.h"
#include "OutputControl.h"

vector<Item*> OutputControl::currentDisplayedItemList;
OutputControl::CurrentScreenType OutputControl::currentScreen = OutputControl::CurrentScreenType::HOME_SCREEN;
OutputControl::CurrentScreenType OutputControl::currentBaseScreen = OutputControl::CurrentScreenType::HOME_SCREEN;
string OutputControl::currentKeywordSearched;

//This function clears the vector that stores the displayed items.
void OutputControl::resetCurrentItemList() {
	currentDisplayedItemList.clear();
}

//This function adds an input Item* to the vector of displayed items.
void OutputControl::addItemToDisplayList(Item* itemPtr) {
	currentDisplayedItemList.push_back(itemPtr);
}

//setters
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

//getters
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
