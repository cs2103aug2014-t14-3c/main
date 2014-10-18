#include "stdafx.h"
#include "Command.h"

using namespace std;

Command::Command(void)
{
}

Command::~Command(void)
{
}

vector<string> Command::execute() {
	outputMessageStorage.clear();
	return outputMessageStorage;
}