#include "stdafx.h"
#include "ActionLog.h"

vector<Command> ActionLog::log;
int ActionLog::numCommands = 0;

void ActionLog::addCommand(Command cmd) {
	log[numCommands++] = cmd;
}

void ActionLog::undo() {
	if(numCommands == 0) {
		// cannot undo!
		// throw exception
	} else {
		ItemBank::resetBank();

		for(int i = 0; i < numCommands - 1; i++) {
			log[i].execute();
		}

		numCommands--;
	} 
}

void ActionLog::redo() {
	if(numCommands == log.size()) {
		// nothing to redo!
		// throw exception
	} else {
		log[++numCommands].execute();
	}
}