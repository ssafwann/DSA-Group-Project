#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

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
	while (getline(infile, line)) {
		vector <string> rv;
		split(line, '\t', rv);
		Person person(rv[0], rv[1], rv[2], rv[3], rv[4], rv[5], rv[6], rv[7]);
		persons.insertRecord(person);
		++count;
	}
	persons.setNoOfRecords(count);
	cout << "\n" << persons.getNoOfRecords() << " records have been added." << endl;
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


