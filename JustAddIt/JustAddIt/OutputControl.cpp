#include "stdafx.h"
#include "OutputControl.h"

vector<Item*> OutputControl::currentDisplayedItemList;
OutputControl::CurrentScreenType OutputControl::currentScreen = OutputControl::CurrentScreenType::HOME_SCREEN;
OutputControl::CurrentScreenType OutputControl::currentBaseScreen = OutputControl::CurrentScreenType::HOME_SCREEN;

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
Item* OutputControl::getItemAddr(int itemLocationInList) {
	return currentDisplayedItemList[itemLocationInList-1];
}

vector<Item*>::iterator OutputControl::getCurrentDisplayedItemList(){
	return currentDisplayedItemList.begin();
}
OutputControl::CurrentScreenType OutputControl::getCurrentScreen(){
	return currentScreen;
}

//Command* OutputControl::constructCmdBaseScreen(){
//	switch (OutputControl::currentBaseScreen) {
//		case HOME_SCREEN: {
//			CmdHome* myHome = new CmdHome();
//			return myHome;
//						  }
//		//case TO_DO_LIST_VIEW: {
//		//	CmdGoToListView* myList = new CmdGoToListView();
//		//	return myList;
//		//					  }
//		//case CALENDAR_VIEW: {
//		//	CmdGoToCalendarView* myCal = new CmdGoToCalendarView();
//		//	return myCal;
//		//					}
//		//default:{
//		//	CmdHome* myHome = new CmdHome();
//		//	return myHome;
//		//		}
//	}
//	//Command* myCmd = new Command();
//	//return myCmd;
//}