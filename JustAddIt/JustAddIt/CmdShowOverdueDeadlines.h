//@author A0108397W
#pragma once
#include "command.h"
#include "DisplayScreenConstructor.h"

class CmdShowOverdueDeadlines :
	public Command
{	
private:
	static const string LOG_OVERDUE_SCREEN_STORED;
	static const string LOG_OUTPUTCONTROL_UPDATED;
	static const string LOG_OVERDUE_DEADLINES_RETRIEVED;
	static const string TEXT_FILE_NAME;

	vector<Item*> getOverdueDeadlinesFromBank(void);
	vector<string> storeOverdueScreenForDisplay(vector<Item*> overdueDeadlines);
	void updateOutputControl(vector<Item*> overdueDeadlines);
	void writeToLog (string logEntry);

public:
	CmdShowOverdueDeadlines(void);
	~CmdShowOverdueDeadlines(void);
	vector<string> execute(void);
};