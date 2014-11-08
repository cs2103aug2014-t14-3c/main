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
	vector<Item*> tasks;
	vector<Item*> deadlines;
	vector<Item*> events;
	
	ItemBank* itemBank = ItemBank::getInstance();

	events = itemBank->getEventsThisWeek();
	deadlines = itemBank->getDeadlinesThisWeek();
	tasks = itemBank->getAllTasks();

	DisplayScreenConstructor* displayScreenConstructor = DisplayScreenConstructor::getInstance();
	outputMessageStorage.clear();
	outputMessageStorage = displayScreenConstructor->constructHomeScreen(tasks, deadlines, events);
	OutputControl::setCurrentScreen(OutputControl::CurrentScreenType::HOME_SCREEN);
	OutputControl::setCurrentBaseScreen(OutputControl::CurrentScreenType::HOME_SCREEN);

	return outputMessageStorage;
}