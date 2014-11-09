//@author A0108397W
#include "stdafx.h"
#include "Exporter.h"

string exportFileName = "JustAddIt_Exports.html";
Exporter* Exporter::exporter = NULL;

const string Exporter::newLine = "<br>";

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

void Exporter::writeToFile(vector<string>displayScreenToBeExported) {
	ofstream mytextfile;
	mytextfile.open(exportFileName);
	vector<string>::iterator iter;

	for (iter = displayScreenToBeExported.begin(); iter != displayScreenToBeExported.end(); iter++) {
		if (*iter != "") {
			mytextfile << *iter << newLine << endl;
		}
	}

	mytextfile.close();
	return;
}