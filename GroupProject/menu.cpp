#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "Menu.h"
using namespace std;

void Menu::readFile(string fname, vector<Person*>& pe) {
	ifstream infile(fname);
	string line;
	if (!infile) {
		cerr << "File failed to open" << endl;
	}
	while (getline(infile, line)) {
		vector <string> rv;
		split(line, 't', rv);
		pe.push_back(new Person(rv[0], rv[1], rv[2], rv[3], rv[4], rv[5], rv[6], rv[7]));
	}
	cout << pe.size() << " number of records inserted" << endl;
	}


void Menu::split(const string& s, char delim, vector<string>& elems) {
	stringstream ss;
	ss.str(s); 
	string item;
	while (getline(ss, item, delim)) {	 
		elems.push_back(item);
	}
}
