//@author A0108397W
#pragma once
#include "ItemBank.h"

class Exporter
{
private:
	static const string ERROR_EMPTY_VECTOR;
	static const string BLANK_SPACE;
	static const string EXPORT_FILE_NAME;
	static const string NEWLINE;
	static Exporter* exporter;

	Exporter(void);
	static void checkEmptyExport(vector<string>displayScreen);

public:
	static Exporter* getInstance(void);
	~Exporter(void);

	static void writeToFile(vector<string>displayScreen);
};