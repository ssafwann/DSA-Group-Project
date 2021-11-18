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

int determineTableSize(string &fname) {
	for (int i = 0; i < fname.length(); i++) {
		fname[i] = toupper(fname[i]);
	}

	if (fname == "DS_10K.TXT") {
		return 10007;
	}
	else if (fname == "DS_30K.TXT") {
		return 30011;
	}
	else if (fname == "DS_70K.TXT") {
		return 70003;
	}
	else if (fname == "DS_100K.TXT") {
		return 100019;
	}
	return 0;
}


int main() {
	bool exitProgram = false;
	do {
		string fname = getFileName();
		int size = determineTableSize(fname);
		if (fname == "-1") {
			exitProgram = true;
		}
		else {
			HashMap persons(size);
			Menu menu;
			menu.readFile(fname, persons);
			menu.chooseOption();
		}
	} while (!exitProgram);
	return 0;
}