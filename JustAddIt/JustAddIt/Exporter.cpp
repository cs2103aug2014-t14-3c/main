//@author A0108397W
#include "stdafx.h"
#include "Exporter.h"

const string Exporter::ERROR_EMPTY_VECTOR = "Woops! An empty screen has been exported!";
const string Exporter::BLANK_SPACE = "";
const string Exporter::EXPORT_FILE_NAME = "JustAddIt_Exports.html";
const string Exporter::NEWLINE = "<br>";

Exporter* Exporter::exporter = NULL;

Exporter::Exporter(void) {
}

Exporter::~Exporter(void) {
}

Exporter* Exporter::getInstance(void) {
	if (exporter == NULL) {
		exporter = new Exporter();
	}
	return exporter;
}

//This function exports the current display screen by writing it into a HTML file
void Exporter::writeToFile(vector<string>displayScreen) {
	ofstream myHtmlFile;
	myHtmlFile.open(EXPORT_FILE_NAME);

	if (displayScreen.size() == 0) {
		throw invalid_argument(ERROR_EMPTY_VECTOR);
	}

	for (vector<string>::iterator iter = displayScreen.begin(); iter != displayScreen.end(); iter++) {
		if (*iter != BLANK_SPACE) {
			myHtmlFile << *iter << NEWLINE << endl;
		}
	}

	myHtmlFile.close();
}