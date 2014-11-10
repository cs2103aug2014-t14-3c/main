//@author A0108397W
#pragma once
#include "Command.h"
#include "ItemBank.h"
#include "DisplayScreenConstructor.h"
#include "ActionLog.h"

class CmdEditItem :
	public Command
{
private:
	Item* _itemAddr;
	int _editFieldNumber;
	string _newFieldInfo;
	tm _newTimeInfo;
	Item::PriorityLevel _newPriorityInfo;
	bool _isEditField;

	static const string MESSAGE_EDIT_SUCCESSFUL;
	static const string ERROR_INVALID_FIELD;
	static const string ERROR_PROGRAM_MALFUNCTION;
	static const string ERROR_INVALID_FIELD_NUMBER;
	static const string ERROR_EMPTY_FIELD;
	static const string LOG_OUTPUTCONTROL_UPDATED;
	static const string LOG_ACTION_LOG_UPDATED;
	static const string LOG_SUCCESS_MESSAGE_STORED;
	static const string LOG_EDIT_SCREEN_STORED;
	static const string LOG_EDIT_FIELD_DETERMINED;
	static const string LOG_ITEM_EDITED;
	static const string TEXT_FILE_NAME;
	static const string TASK;
	static const string DEADLINE;

	void editItem();
	enum FIELD_TO_BE_EDITED determineEditField();
	vector<string> storeEditScreenForDisplay();
	void storeSuccessMessage();
	void updateOutputControl();
	void updateActionLog();
	void writeToLog (string logEntry);

public:
	CmdEditItem(vector<Item*>::iterator itemPtr, int fieldNum, string newFieldInfo);
	CmdEditItem(vector<Item*>::iterator itemPtr, int fieldNum, tm newTimeInfo);
	CmdEditItem(vector<Item*>::iterator itemPtr, int fieldNum, Item::PriorityLevel newPriorityInfo);
	CmdEditItem(vector<Item*>::iterator itemPtr);
	~CmdEditItem(void);

	vector<string> execute();
};