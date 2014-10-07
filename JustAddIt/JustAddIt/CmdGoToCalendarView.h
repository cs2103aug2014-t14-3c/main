#pragma once
#include "command.h"
class CmdGoToCalendarView :
	public Command
{
private:
	vector<Item*> calList;
	vector<Item*> toDoList;

	void constructOutput();
	void itemToString(Item* itemPtr);
	void setPageCommands();

public:
	CmdGoToCalendarView(void);
	~CmdGoToCalendarView(void);

	vector<string> execute();
};

