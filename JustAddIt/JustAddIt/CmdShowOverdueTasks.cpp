#include "stdafx.h"
#include "CmdShowOverdueTasks.h"


CmdShowOverdueTasks::CmdShowOverdueTasks(void)
{
	time_t myTempTime;
	time(&myTempTime);
	_currentTime = myTempTime;
}


CmdShowOverdueTasks::~CmdShowOverdueTasks(void)
{
}

vector<string> CmdShowOverdueTasks::execute() {
	vector<Item*>itemsToBeDisplayed;

	itemsToBeDisplayed = ItemBank::getOverdueTasks(_currentTime);

	DisplayScreenConstructor* displayScreenConstructor = DisplayScreenConstructor::getInstance();
	outputMessageStorage.clear();
	outputMessageStorage = displayScreenConstructor->clearScreen();
	outputMessageStorage = displayScreenConstructor->constructOverdueScreen(itemsToBeDisplayed);
	OutputControl::setCurrentScreen(OutputControl::CurrentScreenType::OVERDUE_TASKS_SCREEN);

	return outputMessageStorage;
}