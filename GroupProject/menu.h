#ifndef MENU_H
#define MENU_H
#include <vector>
#include "Person.h"
using namespace std;
class Menu {
private:
	vector<Person*>& pe;
public:
	void readFile(string fname, vector <Person*> &pe);
	void split(const string& s, char delim, vector<string>& elems)
};


#endif // !MENU_H
