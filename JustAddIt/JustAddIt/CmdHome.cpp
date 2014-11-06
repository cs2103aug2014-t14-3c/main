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
	
	eventsToBeDisplayed = ItemBank::getEvents();
	deadlinesToBeDisplayed = ItemBank::getDeadlines();
	tasksToBeDisplayed = ItemBank::getTasks();

	DisplayScreenConstructor* displayScreenConstructor = DisplayScreenConstructor::getInstance();
	outputMessageStorage.clear();
	//outputMessageStorage = displayScreenConstructor->clearScreen();
	outputMessageStorage = displayScreenConstructor->constructHomeScreen(tasksToBeDisplayed, deadlinesToBeDisplayed, eventsToBeDisplayed);
	OutputControl::setCurrentScreen(OutputControl::CurrentScreenType::HOME_SCREEN);
	OutputControl::setCurrentBaseScreen(OutputControl::CurrentScreenType::HOME_SCREEN);

	return outputMessageStorage;
}