#pragma once
#include "CommandLogic.h"
class GoToCalendarView :
	public CommandLogic
{
public:
	GoToCalendarView();
	~GoToCalendarView();

	vector<string> execute();
};

