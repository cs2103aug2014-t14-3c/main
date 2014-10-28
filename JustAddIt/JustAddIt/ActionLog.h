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
	static int numCommands;
	static State state;

	static void resetLog();
	static void resetUndoStack();

public:
	static void addCommand(Command* cmd);
	static void undo();
	static void redo();
};