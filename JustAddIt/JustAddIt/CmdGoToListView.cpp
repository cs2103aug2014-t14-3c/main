#include "stdafx.h"
#include "CmdGoToListView.h"


CmdGoToListView::CmdGoToListView(int numWeeks)
{
	_numWeeks = numWeeks;
}


CmdGoToListView::~CmdGoToListView(void)
{
}

vector<string> CmdGoToListView::execute() {
	vector<string> deadlines;
	vector<string> tasks;
	int i = 1;

	deadlines = ItemBank::getDeadlines(1);
	tasks = ItemBank::getTasks();

	outputMessageStorage.push_back("--------------------\nDeadlines in a week\n---------------------");

	for(vector<string>::iterator iter = deadlines.begin(); iter != deadlines.end(); i++) {
		outputMessageStorage.push_back(to_string(i) + ")");
		outputMessageStorage.push_back(*iter);
		i++;
	}

	outputMessageStorage.push_back("");
	outputMessageStorage.push_back("----------\nTasks\n----------");
	for(vector<string>::iterator iter = tasks.begin(); iter != tasks.end(); i++) {
		outputMessageStorage.push_back(to_string(i) + ")");
		outputMessageStorage.push_back(*iter);
		i++;
	}

	return outputMessageStorage;
}