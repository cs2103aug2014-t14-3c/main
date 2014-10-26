#pragma once
#include "stdafx.h"
#include "Command.h"
#include "ItemBank.h"

class ActionLog
{
private:
	static vector<Command*> log;
	static stack<Command*> undoStack;
	static int numCommands;

	static void resetLog();

public:
	static void addCommand(Command* cmd);
	static void undo();
	static void redo();
};