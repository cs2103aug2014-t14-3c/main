#include "stdafx.h"
#include "CmdHome.h"

CmdHome::CmdHome(void) {
}

CmdHome::~CmdHome(void)
{
}

vector<string> CmdHome::execute() {

	DisplayScreenConstructor* displayScreenConstructor = DisplayScreenConstructor::getInstance();
	outputMessageStorage.clear();
	outputMessageStorage = displayScreenConstructor->clearScreen();
	outputMessageStorage = displayScreenConstructor->constructHomeScreen();

	OutputControl::setCurrentScreen(OutputControl::CurrentScreenType::HOME_SCREEN);

	return outputMessageStorage;
}