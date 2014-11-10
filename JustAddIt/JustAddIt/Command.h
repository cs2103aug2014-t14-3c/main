#pragma once
//@author A0110770U
//-----------------------------------------------
//This is the Command super class in which
//all other Cmds inherit from. Command objects 
//should not be created.
//
//When adding new Cmds, inherit as a subclass of
//Command. New Cmds should have should a execute
//function, similar to existing Cmds.
//-----------------------------------------------

#include "stdafx.h"

#include "ItemBank.h"
#include "OutputControl.h"
enum CommandType {
	ADD, SEARCH, VIEW_LAST_SEARCH, EDIT_FIELD, EDIT_ITEM, DELETE, MARK, SAVE, UNDO, VIEW_CALENDAR, VIEW_TODOLIST, 
	VIEW_OVERDUE, HOME, REDO, EXPORT, CLEAR_ALL_OVERDUE, CLEAR_ALL_DONE, CYCLE_LEFT, CYCLE_RIGHT
};
using namespace std;

class Command
{
protected:
	vector<string> outputMessageStorage;

public:
	Command(void);
	~Command(void);
	virtual vector<string> execute();
};