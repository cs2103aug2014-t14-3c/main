#pragma once
#include "stdafx.h"
#include "Command.h"
#include "ItemBank.h"

class ActionLog
{
private:
	static vector<Command> log;
	static int numberOfCommands;

public:
	static void addCommands(Command cmd);
	static void undo();
	static void redo();
};