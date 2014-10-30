#pragma once
#include "ItemBank.h"

class Exporter
{
private:
	static string exportFilename;
	static Exporter* exporter;

	Exporter(void);

public:
	static Exporter* getInstance(void);
	~Exporter(void);

	static void writeToFile(vector<string>screenToBeExported);
};