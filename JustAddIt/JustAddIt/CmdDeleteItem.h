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
	static const string CmdDeleteItem::MESSAGE_DELETION_SUCCESSFUL;
	static const string CmdDeleteItem::LOGGING_ITEMS_DELETED;
	static const string CmdDeleteItem::LOGGING_BASE_SCREEN_STORED;
	static const string CmdDeleteItem::LOGGING_SUCCESS_MESSAGE_STORED;
	static const string CmdDeleteItem::LOGGING_COMMAND_STORED_IN_ACTION_LOG;
	static const string CmdDeleteItem::TEXT_FILE_NAME;

	CmdDeleteItem(vector<Item*> itemsToBeDeleted);
	~CmdDeleteItem(void);
	vector<string> CmdDeleteItem::execute();
	void deleteItemsFromBank(void);
	vector<string> returnToBaseScreen(void);
	void storeCommandIntoActionLog(void);
	void writeToLog (string logEntry);
};