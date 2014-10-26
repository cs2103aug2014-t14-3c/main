#include "stdafx.h"
#include "ActionLog.h"

vector<Command> ActionLog::log;
int ActionLog::numberOfCommands = 0;

void ActionLog::addCommands(Command cmd) {
	log.push_back(cmd);
	numberOfCommands++;
}

void ActionLog::undo() {
	if(numberOfCommands == 0) {
		//cannot undo!
		//throw exception
	} else {
		ItemBank::resetBank();

		for(int index = 0; index < numberOfCommands - 1; index++) {
			log[index].execute();
		}

		numberOfCommands--;
	} 
}

void ActionLog::redo() {
	if(numberOfCommands == log.size()) {
		//nothing to redo!
		//throw exception
	} else {
		log[++numberOfCommands].execute();
	}
}