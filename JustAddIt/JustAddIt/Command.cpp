#include "stdafx.h"
#include "Command.h"

using namespace std;

const string Command::FORMAT_TITLE = "Title:       ";
const string Command::FORMAT_DESCRIPTION = "Description: ";
const string Command::FORMAT_START = "Start:       ";
const string Command::FORMAT_END = "End:        ";
const string Command::FORMAT_VENUE = "Venue:       ";
const string Command::FORMAT_PRIORITY = "Priority:    ";
const string Command::FORMAT_CATEGORY = "Category:    ";	
const string Command::FORMAT_DIVIDER = "\n================================================================================\n"; 

const string Command::PAGE_COMMAND_TO_DO_LIST_VIEW = "[t] View To-do list";
const string Command::PAGE_COMMAND_CALENDAR_VIEW = "[c] View Calendar";
const string Command::PAGE_COMMAND_OVERDUE_TASKS = "[o] Check for overdue tasks";
const string Command::PAGE_COMMAND_SAVE = "[s] Save";
const string Command::PAGE_COMMAND_EDIT = "[e 1, e 2, ... ] Edit (entry number)";
const string Command::PAGE_COMMAND_CANCEL = "[c] Cancel";
const string Command::PAGE_COMMAND_VIEW_TWO_WEEKS = "[v2] View 2 weeks ahead";
const string Command::PAGE_COMMAND_VIEW_THREE_WEEKS = "[v3] View 3 weeks ahead";
const string Command::PAGE_COMMAND_VIEW_MONTH = "[v4] View 4 weeks ahead";
const string Command::PAGE_COMMAND_SHOW_ALL = "[a] Show all";
const string Command::PAGE_COMMAND_SORT_CATEGORY = "[sc] Sort by category";
const string Command::PAGE_COMMAND_SORT_PRIORITY = "[sp] Sort by priority";
const string Command::PAGE_COMMAND_EXPORT = "[e] Export";
const string Command::PAGE_COMMAND_MODIFY = "[m 1, m 2, ...] = Modify item no.";
const string Command::PAGE_COMMAND_DELETE = "[d 1, d 2, ...] = Delete item no.";
const string Command::PAGE_COMMAND_MARK_DONE = "[k 1, k 2, ...] = Mark item no. done";
const string Command::PAGE_COMMAND_UNDO = "[u] Undo";
const string Command::PAGE_COMMAND_CHANGE_MONTH = "[<],[>] Cycle between months";

Command::Command(void)
{
}


Command::~Command(void)
{
}

void Command::itemToString(Item* itemPtr) {
	
}

void Command::setPageCommands() {
	outputMessageStorage.clear();

	cout << string(50,'\n');
}

void Command::constructOutput() {

}

vector<string> Command::execute() {
	outputMessageStorage.clear();
	return outputMessageStorage;
}

