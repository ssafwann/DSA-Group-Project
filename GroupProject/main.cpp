#include <iostream>

#include "menu.h"
#include "person.h"
#include "Node.h"
#include "HashMap.h"

using namespace std;
string getFileName() {
	string fname = "!";
	cout << "\t     File Names" << endl;
	cout << "===================================" << endl;
	cout << "\t[1] - DS_10K.txt" << endl;
	cout << "\t[2] - DS_30K.txt" << endl;
	cout << "\t[3] - DS_70K.txt" << endl;
	cout << "\t[4] - DS_100K.txt" << endl;
	cout << "===================================" << endl;
	cout << "Enter file Name(-1 to stop): ";
	while (!(cin >> fname)) {
		cout << "\nEnter a valid name only\n " << endl;
		cin.clear();
		cin.ignore(123, '\n');
	}
	return fname;
}


int main() {
	bool exitProgram = false;
	do {
		string fname = getFileName();
		if (fname == "-1") {
			exitProgram = true;
		}
		else {
			HashMap persons(10007);
			Menu menu;
			menu.readFile(fname, persons);
		}
	} while (!exitProgram);
	return 0;
}