#include <iostream>
#include "menu.h"
#include "person.h"
#include "hash.h"
using namespace std;



int main() {
	string userInput = "!";
	string fname;
	bool fileChosen = true;
	bool exitProgram = false;
	do {
		cout << "  Choose a file to insert records" << endl;
		cout << "===================================" << endl;
		cout << "\t[1] - 10k file" << endl;
		cout << "\t[2] - 30k file" << endl;
		cout << "\t[3] - 70k file" << endl;
		cout << "\t[4] - 100k file" << endl;
		cout << "\t[5] - Exit" << endl;
		cout << "===================================" << endl;
		cout << "Your choice: ";
		cin >> userInput;

		fileChosen = true;

		if (userInput == "1") {
			fname = "DS_10K.txt";
		}
		else if (userInput == "2") {
			fname = "DS_30K.txt";
		}
		else if (userInput == "3") {
			fname = "DS_70K.txt";
		}
		else if (userInput == "4") {
			fname = "DS_100K.txt";
		}
		else if (userInput == "5") {
			exitProgram = true;
		}
		else {
			fileChosen = false;
			cout << "\nEnter valid Input\n" << endl;
		}
	} while (!fileChosen);

	if (!exitProgram) {
		cout << "next";
	}


	return 0;
}