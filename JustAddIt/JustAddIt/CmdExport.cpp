#include "stdafx.h"
#include "CmdExport.h"

CmdExport::CmdExport(void) {
}


CmdExport::~CmdExport(void)
{
}

vector<string> CmdExport::execute() {
	Exporter::writeToFile(outputMessageStorage);

	outputMessageStorage.clear();
	//returns to base screen
	Command* cmdBase = new CmdGoToBaseScreen(OutputControl::getCurrentBaseScreen());
	outputMessageStorage.clear();
	outputMessageStorage = cmdBase->execute();

	outputMessageStorage.push_back("The current screen has been exported into text file \"JustAddIt_Exports.txt\"!");

	return outputMessageStorage;
}