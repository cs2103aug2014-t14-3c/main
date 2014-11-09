//@author A0108397W
#pragma once
#include "ItemBank.h"

class Exporter
{
private:
	static string exportFilename;
	static Exporter* exporter;

	static const string newLine;

	Exporter(void);

public:
	static Exporter* getInstance(void);
	~Exporter(void);

	static void writeToFile(vector<string>displayScreenToBeExported);
};