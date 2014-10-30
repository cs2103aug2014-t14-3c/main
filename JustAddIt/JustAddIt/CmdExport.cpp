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
	outputMessageStorage.push_back("The current screen has been exported into text file \"JustAddIt_Exports.txt\"!");

	return outputMessageStorage;
}