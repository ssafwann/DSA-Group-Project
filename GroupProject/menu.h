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
	void readFile(string fname, HashMap& persons);
	void split(const string& s, char delim, vector<string>& elems);
	void chooseOption();
	void searchForRecords();
	void deleteHashRecords();
};


#endif // !MENU_H
