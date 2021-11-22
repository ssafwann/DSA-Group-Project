/*
	A class is used to perform some functions such as reading to files and more
*/

#ifndef MENU_H
#define MENU_H
#include <vector>
#include "Person.h"
#include "HashMap.h"
using namespace std;
class Menu {
private:
public:
	void readFile(string fname, HashMap& hashMap);
	void split(const string& s, char delim, vector<string>& elems);
	void chooseOption(HashMap& hashTable);
	void searchForRecords(HashMap& persons);
	void deleteHashRecords(HashMap& persons);
	void writeToFile(string fname, HashMap& persons);
};


#endif // !MENU_H
