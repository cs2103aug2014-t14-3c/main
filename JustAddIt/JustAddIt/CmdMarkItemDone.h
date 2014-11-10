//@author A0108397W
#pragma once
#include "Command.h"
#include "ItemBank.h"
#include "ActionLog.h"
#include "CmdGoToBaseScreen.h"

class CmdMarkItemDone :
	public Command {
private:
	static const string MESSAGE_MARK_SUCCESSFUL;
	static const string LOG_ITEMS_MARKED;
	static const string LOG_BASE_SCREEN_STORED;
	static const string LOG_SUCCESS_MESSAGE_STORED;
	static const string LOG_ACTION_LOG_UPDATED;
	static const string ERROR_EMPTY_VECTOR;
	static const string TEXT_FILE_NAME;

	vector<Item*> _itemsToBeMarked;

	void toggleItemsDone(void);
	vector<string> returnToBaseScreen(void);
	void storeSuccessMessage(void);
	void storeCommandIntoActionLog(void);
	void writeToLog (string logEntry);

public:
	CmdMarkItemDone(vector<Item*> itemsToBeMarked);
	~CmdMarkItemDone(void);
	vector<string> execute();
};