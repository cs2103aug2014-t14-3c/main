#include "stdafx.h"
#include "Executor.h"
#include <iostream>
#include <vector>

using namespace std;

int main(void) {
	string userCommand;
	vector<string> outputMessageStorage;
	vector<string>::iterator iter;
	Executor executor;

	cout << "command: ";
	getline(cin, userCommand);

	while (userCommand != "exit") {
		outputMessageStorage = executor.execute(userCommand);
		for (iter = outputMessageStorage.begin(); iter != outputMessageStorage.end(); iter++) {
			cout << *iter << endl;
		}

		outputMessageStorage.clear();
		cout << "command: ";
		cin >> userCommand;
	};

	return 0;
}