#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <iostream>
#include <chrono>

#include "Menu.h"
#include "HashMap.h"
using namespace std;

void Menu::readFile(string fname, HashMap& persons) {
	int count = 0;
	ifstream infile(fname);
	string line;
	if (!infile) {
		cerr << "\nFile failed to open\n" << endl;
		return;
	}

	// Record start time
	auto start = chrono::steady_clock::now();

	while (getline(infile, line)) {
		vector <string> rv;
		split(line, '\t', rv);
		Person person(rv[0], rv[1], rv[2], rv[3], rv[4], rv[5], rv[6], rv[7]);
		persons.insertRecord(person);
		++count;
	}

	// Record end time
	auto end = chrono::steady_clock::now();
	// Compute duration
	auto duration_micro = chrono::duration_cast<chrono::microseconds>(end - start).count();

	persons.setNoOfRecords(count);
	cout << "\n" << persons.getNoOfRecords() << " records have been added." << endl;
	cout << "The table size is: " << persons.getBuckets() << endl;
	cout << "Elapsed time in microseconds: " << duration_micro << " micro sec" << endl;
	persons.displayWholeTable(); // temporary delete later
}

void Menu::split(const string& s, char delim, vector<string>& elems) {
	stringstream ss;
	ss.str(s);
	string item;
	while (getline(ss, item, delim)) {
		elems.push_back(item);
	}
}

void Menu::chooseOption()
{
	string userOption;
	bool correctChoice = false;
	do {
		cout << "\nWhat would you like to do next" << endl;
		cout << "===================================" << endl;
		cout << "\t[D] - Delete Records" << endl;
		cout << "\t[S] - Search Records" << endl;
		cout << "\t[I] - Insert New Records(Back)" << endl;
		cout << "===================================" << endl;
		cout << "Your choice: ";
		cin >> userOption;

		if (userOption == "D" || userOption == "d") {
			deleteHashRecords();
		}
		else if (userOption == "S" || userOption == "s") {
			searchForRecords();
		}
		else if (userOption == "I" || userOption == "i") {
			correctChoice = true;
		}
		else {
			cout << "\nEnter a valid option\n" << endl;
		}
	} while (correctChoice == false);
}

// modify this
void Menu::searchForRecords()
{

}

// modify this
void Menu::deleteHashRecords()
{
	bool stopDeleting = false;
	string userOption;
	do {
		cout << "\nYou can delete by single record: Phone Number" << endl;
		cout << "Yan also delete by batch: Country" << endl;
		cout << "Your choice(-1 to stop): ";
		cin >> userOption;
		if (userOption == "-1") {
			stopDeleting = true;
		}
	} while (stopDeleting == false);
}



