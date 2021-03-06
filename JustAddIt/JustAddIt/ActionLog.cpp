//@author A0116781A
#include "stdafx.h"
#include "ActionLog.h"

vector<Command*> ActionLog::log;
stack<Command*> ActionLog::undoStack;
ActionLog::State ActionLog::state = READY;

const string ActionLog::MESSAGE_INVALID_UNDO = "nothing to undo!";
const string ActionLog::MESSAGE_INVALID_REDO = "nothing to redo!";
const string ActionLog::ERROR_LOGIC = "logic error in setting state when adding command";

void ActionLog::addCommand(Command* cmd) {
	log.push_back(cmd);

	assert(log.size() != 0);
	
	//reset the undo stack to zero if the current command is not redo
	if(state == READY) {
		resetUndoStack();
	} else if(state == UNDO) { 
		state = READY;
	} else if(state == REDO) {
		// do nothing
	} else {
		throw logic_error(ERROR_LOGIC);
	}
}

void ActionLog::undo() {
	if(log.size() == 0) {
		throw invalid_argument(MESSAGE_INVALID_UNDO);
	} else {
		ItemBank::getInstance()->resetBank();

		vector<Command*> tempLog = copyLog();

		resetLog();

		//executes the commands from when the software is started
		executeCmds(tempLog.size(), tempLog);

		//adds the last command in tempLog (not executed) to a stack
		undoStack.push(tempLog.back());		
	} 
}

void ActionLog::redo() {
	if(undoStack.empty()) {
		throw invalid_argument(MESSAGE_INVALID_REDO);
	} else {
		//executes the last command undone (top command in the stack)
		Command* lastUndo = undoStack.top();
		undoStack.pop();
		state = REDO;
		lastUndo->execute();
	}
}

vector<Command*> ActionLog::copyLog() {
	vector<Command*> tempLog;
		
	for(vector<Command*>::iterator iter = log.begin(); iter != log.end(); iter++) {
		tempLog.push_back(*iter);
	}

	return tempLog;
}

void ActionLog::executeCmds(int numCommands, vector<Command*> tempLog) {
	//executes the commands from when the software is started
	for(int i = 0; i < numCommands - 1; i++) {
		state = UNDO;
		tempLog[i]->execute();
	}
}

void ActionLog::resetUndoStack() {
	while(undoStack.size() != 0) {
		undoStack.pop();
	}
}

void ActionLog::resetLog() {
	log.clear();
}
