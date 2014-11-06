#pragma once
#include "Command.h"
#include "ItemBank.h"
#include "ActionLog.h"
#include "CmdGoToBaseScreen.h"

class CmdMarkItemDone :
	public Command
{
private:
	vector<Item*> _itemsToBeMarked;

public:
	static const string MESSAGE_MARK_SUCCESSFUL;
	static const string LOG_ITEMS_MARKED;
	static const string LOG_BASE_SCREEN_STORED;
	static const string LOG_SUCCESS_MESSAGE_STORED;
	static const string LOG_COMMAND_STORED_IN_ACTION_LOG;
	static const string ERROR_EMPTY_VECTOR;
	static const string TEXT_FILE_NAME;

	CmdMarkItemDone(vector<Item*> itemsToBeMarked);
	~CmdMarkItemDone(void);
	vector<string> CmdMarkItemDone::execute();
	void toggleItemsDone(void);
	vector<string> returnToBaseScreen(void);
	void storeCommandIntoActionLog(void);
	void writeToLog (string logEntry);
};