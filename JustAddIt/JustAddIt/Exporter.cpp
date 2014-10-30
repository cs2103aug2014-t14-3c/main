#include "stdafx.h"
#include "Exporter.h"

string exportFileName = "JustAddIt_Exports.txt";
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

void Exporter::writeToFile(vector<string>screenToBeExported) {
	ofstream mytextfile;
	mytextfile.open(exportFileName);
	vector<string>::iterator iter;

	for (iter = screenToBeExported.begin(); iter != screenToBeExported.end(); iter++) {
		mytextfile << *iter << endl;
	}

	mytextfile.close();
	return;
}