#include "stdafx.h"
#include "CmdHome.h"

CmdHome::CmdHome(void) {
	time_t currentTime;
	time(&currentTime);
	localtime_s (&_currentTime, &currentTime);
}

CmdHome::~CmdHome(void)
{
}

vector<string> CmdHome::execute() {
	updateOutputControl();

	outputMessageStorage.clear();
	outputMessageStorage = storeHomeScreenForDisplay();
	
	return outputMessageStorage;
}
//This function updates the information that OutputControl
//keeps track of;base screen and current screen.
void CmdHome::updateOutputControl(){
	
	OutputControl::setCurrentScreen(OutputControl::CurrentScreenType::HOME_SCREEN);
	OutputControl::setCurrentBaseScreen(OutputControl::CurrentScreenType::HOME_SCREEN);
}
//This function returns the current home
//screen as a vector of strings.
vector<string> CmdHome::storeHomeScreenForDisplay(){
	vector<Item*> tasks;
	vector<Item*> deadlines;
	vector<Item*> events;
	
	ItemBank* itemBank = ItemBank::getInstance();

	events = itemBank->getEventsThisWeek();
	deadlines = itemBank->getDeadlinesThisWeek();
	tasks = itemBank->getAllTasks();

	DisplayScreenConstructor* displayScreenConstructor = DisplayScreenConstructor::getInstance();	 
	return displayScreenConstructor->constructHomeScreen(tasks, deadlines, events);
}