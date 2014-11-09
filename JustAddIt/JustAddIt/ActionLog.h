//@author A0116781A
//
//-----------------------------------------------
//This is the ActionLog class. Whenever a command
//that creates, modifies or deletes an item, the 
//command will be stored in this log. This log is 
//used to facilitate "undo" and "redo" capability.
//
//The command that is passed in will be stored in
//a vector. 
//
//When "undo" is called, the ActionLog will reset 
//all the items to its original state when 
//JustAddIt first initializes, then performs all
//actions from the beginning of the log until the
//second last one. The last command will be moved 
//to another stack to for "redo" capability.
//
//When "redo" is called, the ActionLog will 
//execute the action at the top of the stack of 
//undone actions.
//
//If the next command after "undo" is not "redo",
//the stack of undone actions is reset.
//
//-----------------------------------------------

#pragma once
#include "stdafx.h"
#include "Command.h"
#include "ItemBank.h"

class ActionLog
{
private:
	enum State { READY, UNDO, REDO };
	static vector<Command*> log;
	static stack<Command*> undoStack;
	static State state;

	static const string MESSAGE_INVALID_UNDO;
	static const string MESSAGE_INVALID_REDO;
	static const string ERROR_LOGIC;

	static vector<Command*> copyLog();
	
	static void resetUndoStack();

	//ActionLog();

public:
	//~ActionLog();
	//static ActionLog* getInstance();
	static void addCommand(Command* cmd);
	static void undo();
	static void redo();
	static void resetLog();
};