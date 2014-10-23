#include "stdafx.h"
#include "CmdGoToListView.h"
#define DEFAULT_NUM_WEEKS 1

CmdGoToListView::CmdGoToListView(int numWeeks)
{
	_numWeeks = numWeeks;
}

CmdGoToListView::CmdGoToListView()
{
	_numWeeks = DEFAULT_NUM_WEEKS;
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

	for(vector<string>::iterator iter = deadlines.begin(); iter != deadlines.end(); iter++) {
		outputMessageStorage.push_back(to_string(i) + ")");
		outputMessageStorage.push_back(*iter);
		i++;
	}

	outputMessageStorage.push_back("");
	outputMessageStorage.push_back("----------\nTasks\n----------");
	for(vector<string>::iterator iter = tasks.begin(); iter != tasks.end(); iter++) {
		outputMessageStorage.push_back(to_string(i) + ")");
		outputMessageStorage.push_back(*iter);
		i++;
	}

	return outputMessageStorage;
}