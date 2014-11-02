#pragma once
#include "stdafx.h"
#include "Command.h"
#include "ItemBank.h"
#include "OutputControl.h"
#include "ActionLog.h"
#include "CmdGoToBaseScreen.h"

class CmdDeleteItem :
	public Command {

private:
	vector<Item*> _itemsToBeDeleted;

public:
	static const string MESSAGE_DELETION_SUCCESSFUL;
	static const string LOG_ITEMS_DELETED;
	static const string LOG_BASE_SCREEN_STORED;
	static const string LOG_SUCCESS_MESSAGE_STORED;
	static const string LOG_COMMAND_STORED_IN_ACTION_LOG;
	static const string ERROR_EMPTY_VECTOR;
	static const string TEXT_FILE_NAME;

	CmdDeleteItem(vector<Item*> itemsToBeDeleted);
	~CmdDeleteItem(void);
	vector<string> CmdDeleteItem::execute();
	void deleteItemsFromBank(void);
	vector<string> returnToBaseScreen(void);
	void storeCommandIntoActionLog(void);
	void writeToLog (string logEntry);
};