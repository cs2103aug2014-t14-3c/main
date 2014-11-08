#include "stdafx.h"
#include "ActionLog.h"

vector<Command*> ActionLog::log;
stack<Command*> ActionLog::undoStack;
int ActionLog::numCommands = 0;
ActionLog::State ActionLog::state = READY;

void ActionLog::resetLog() {
	log.clear();
	numCommands = 0;
}

void ActionLog::resetUndoStack() {
	while(undoStack.size() != 0) {
		undoStack.pop();
	}
}

void ActionLog::addCommand(Command* cmd) {
	log.push_back(cmd);

	numCommands++;
	assert(numCommands != 0);

	if(state == READY) {
		resetUndoStack();
	} else { // if state == REDO or UNDO
		state = READY;
	}
}

void ActionLog::undo() {

	state = READY;

	if(numCommands == 0) {
		throw invalid_argument("no previous command to undo!");
	} else {
		ItemBank::getInstance()->resetBank();

		vector<Command*> tempLog;
		
		for(vector<Command*>::iterator iter = log.begin(); iter != log.end(); iter++) {
			tempLog.push_back(*iter);
		}

		int initialNumCommands = numCommands;

		resetLog();

		for(int i = 0; i < initialNumCommands - 1; i++) {
			tempLog[i]->execute();
		}

		undoStack.push(tempLog[--initialNumCommands]);
	} 

	state = UNDO;
}

void ActionLog::redo() {
	if(undoStack.empty()) {
		throw invalid_argument("nothing to redo!");
	} else {
		Command* lastUndo = undoStack.top();
		undoStack.pop();
		lastUndo->execute();
	}
	
	state = REDO;
}