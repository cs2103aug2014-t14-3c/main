#include "stdafx.h"
#include "ActionLog.h"

vector<Command*> ActionLog::log;
Command* ActionLog::lastUndo;
int ActionLog::numCommands = 0;

void ActionLog::resetLog() {
	log.clear();
}

void ActionLog::addCommand(Command* cmd) {
	log.push_back(cmd);
	numCommands++;
	assert(numCommands != 0);
}

void ActionLog::undo() {
	if(numCommands == 0) {
		// cannot undo!
		// throw exception
	} else {
		ItemBank::resetBank();

		vector<Command*> tempLog;
		
		for(vector<Command*>::iterator iter = log.begin(); iter != log.end(); iter++) {
			tempLog.push_back(*iter);
		}

		resetLog();

		for(int i = 0; i < numCommands - 1; i++) {
			tempLog[i]->execute();
		}

		lastUndo = tempLog[--numCommands];
	} 
}

void ActionLog::redo() {
	if(numCommands == log.size()) {
		// nothing to redo!
		// throw exception
	} else {
		lastUndo->execute();
	}
}