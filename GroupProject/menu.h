/*
	A class which is responsible for printing out the menu and getting user inputs.
*/

#ifndef MENU_H
#define MENU_H

#include "Person.h"
#include "HashMap.h"

#include <vector>

class Menu {
private:
public:
	void readFile(string fname, HashMap& hashMap);
	void split(const string& s, char delim, vector<string>& elems);
	void chooseOption(HashMap& hashTable);
	void searchForRecords(HashMap& persons);
	void deleteRecords(HashMap& persons);
	void writeToFile(string fname, HashMap& persons);
};

#endif // !MENU_H
