//@author A0108397W
#include "stdafx.h"
#include "CmdExport.h"

const string CmdExport::MESSAGE_EXPORT_SUCCESSFUL = "The current screen has been exported into the file \"JustAddIt_Exports.html\"!";

CmdExport::CmdExport(void) {
}


CmdExport::~CmdExport(void) {
}

//This function simply reflects a success message when it is called to provide the user with the name of the exported text file
vector<string> CmdExport::execute() {
	outputMessageStorage.push_back(MESSAGE_EXPORT_SUCCESSFUL);

	return outputMessageStorage;
}