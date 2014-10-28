// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"
#include <iostream>
#include <iomanip>
#include <tchar.h>
#include <string>
#include <iterator>
#include <vector>
#include <stack>
#include <fstream>
#include <ctime>
#include <cctype>
#include <ctype.h>
#include <sstream>
#include <exception>
#include <cassert>
#include <algorithm>

enum CommandType {
	ADD, SEARCH, VIEW_LAST_SEARCH, EDIT_FIELD, EDIT_ITEM, DELETE, MARK, SAVE, UNDO, VIEW_CALENDAR, VIEW_TODOLIST, 
	VIEW_OVERDUE, HOME, REDO, EXPORT, CLEAR_ALL_OVERDUE, CLEAR_ALL_DONE, CYCLE_LEFT, CYCLE_RIGHT
};
// TODO: reference additional headers your program requires here
