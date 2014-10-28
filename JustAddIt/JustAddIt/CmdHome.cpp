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
	vector<Item*>tasksToBeDisplayed;
	vector<Item*>deadlinesToBeDisplayed;
	vector<Item*>eventsToBeDisplayed;
	struct tm cutOffDateTimeInStruct_tm;
	time_t cutOffDateTimeInTime_t;

	_currentTime.tm_mday += 7;
	cutOffDateTimeInTime_t = mktime(&(_currentTime));
	localtime_s (&cutOffDateTimeInStruct_tm, &cutOffDateTimeInTime_t);
	
	eventsToBeDisplayed = ItemBank::getEvents(cutOffDateTimeInStruct_tm);
	deadlinesToBeDisplayed = ItemBank::getDeadlines(cutOffDateTimeInStruct_tm);
	tasksToBeDisplayed = ItemBank::getTasks();

	DisplayScreenConstructor* displayScreenConstructor = DisplayScreenConstructor::getInstance();
	outputMessageStorage.clear();
	outputMessageStorage = displayScreenConstructor->clearScreen();
	outputMessageStorage = displayScreenConstructor->constructHomeScreen(tasksToBeDisplayed, deadlinesToBeDisplayed, eventsToBeDisplayed);
	OutputControl::setCurrentScreen(OutputControl::CurrentScreenType::HOME_SCREEN);
	OutputControl::setCurrentBaseScreen(OutputControl::CurrentScreenType::HOME_SCREEN);

	return outputMessageStorage;
}