//@author A0108397W
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
	static const string MESSAGE_DELETION_SUCCESSFUL;
	static const string LOG_ITEMS_DELETED;
	static const string LOG_BASE_SCREEN_STORED;
	static const string LOG_SUCCESS_MESSAGE_STORED;
	static const string LOG_ACTION_LOG_UPDATED;
	static const string ERROR_EMPTY_VECTOR;
	static const string TEXT_FILE_NAME;

	vector<Item*> _itemsToDelete;

	void deleteItemsFromBank(void);
	vector<string> returnToBaseScreen(void);
	void storeSuccessMessage(void);
	void storeCommandIntoActionLog(void);
	void writeToLog (string logEntry);

public:
	CmdDeleteItem(vector<Item*> itemsToDelete);
	~CmdDeleteItem(void);

	vector<string> CmdDeleteItem::execute();
};