#include "Menu.h"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <chrono>

// used to get the contents of a file and input it into the hash table
void Menu::readFile(string fname, HashMap& hashMap) {
	int count = 0;
	ifstream infile(fname);
	string line;
	if (!infile) {
		cerr << "\nFile failed to open\n" << endl;
		return;
	}

	auto start = chrono::steady_clock::now();
	while (getline(infile, line)) {
		vector <string> rv;
		split(line, '\t', rv);
		Person person(rv[0], rv[1], rv[2], rv[3], rv[4], rv[5], rv[6], rv[7]);
		hashMap.insertRecord(person);
		++count;
	}
	auto end = chrono::steady_clock::now();
	auto duration_micro = chrono::duration_cast<chrono::microseconds>(end - start).count();

	hashMap.setNoOfRecords(count);
	cout << "\n===============================================" << endl;
	cout << hashMap.getNoOfRecords() << " records have been added." << endl;
	cout << "The table size is: " << hashMap.getBuckets() << endl;
	cout << "Elapsed time in microseconds: " << duration_micro << " micro sec" << endl;
	cout << "===============================================" << endl;
}

// used to identify different attributes using '\t' and put them in a vector
void Menu::split(const string& s, char delim, vector<string>& elems) {
	stringstream ss;
	ss.str(s);
	string item;
	while (getline(ss, item, delim)) {
		elems.push_back(item);
	}
}

void Menu::chooseOption(HashMap& persons)
{
	string userOption;
	bool correctChoice = false;
	do {
		cout << "\n\t   Next Operation" << endl;
		cout << "===================================" << endl;
		cout << "\t[D] - Delete Records" << endl;
		cout << "\t[S] - Search Records" << endl;
		cout << "\t[I] - Insert New File" << endl;
		cout << "\t[B] - Back" << endl;
		cout << "===================================" << endl;
		cout << "Your choice: ";
		cin >> userOption;

		if (userOption == "D" || userOption == "d") {
			deleteRecords(persons);
		}
		else if (userOption == "S" || userOption == "s") {
			searchForRecords(persons);
		}
		else if (userOption == "I" || userOption == "i" || userOption == "B" || userOption == "b") {
			cout << endl;
			correctChoice = true;
		}
		else {
			cout << "\nEnter a valid option\n" << endl;
		}
	} while (correctChoice == false);
}

void Menu::searchForRecords(HashMap& persons)
{
	bool doneSearching = false;
	do {
		string userOption = "!";
		cout << "\n\t    Choose Search Function" << endl;
		cout << "=========================================" << endl;
		cout << "\t[1] - Single Attribute" << endl;
		cout << "\t[2] - Double Attribute" << endl;
		cout << "\t[3] - Go back" << endl;
		cout << "=========================================" << endl;
		cout << "Your Choice: ";
		cin >> userOption;

		if (userOption == "3") {
			doneSearching = true;
		}

		if (!doneSearching) {
			string toSearch1, toSearch2;
			if (userOption == "1") {
				cout << "\n Enter one of the following attributes" << endl;
				cout << "=========================================" << endl;
				cout << "             Phone Number" << endl;
				cout << "             Skills" << endl;
				cout << "             Job Title" << endl;
				cout << "             Country" << endl;
				cout << "=========================================" << endl;
				cout << "Enter Attribute: ";
				cin.get();
				getline(cin, toSearch1);
				// check if user entered phone number or the other attributes
				if (toSearch1[0] < 65) {
					persons.searchByHash(toSearch1);
				}
				else persons.searchByString(toSearch1);
			}
			else if (userOption == "2") {
				cout << "\n Enter one of the following attributes" << endl;
				cout << "=========================================" << endl;
				cout << "             Skills x Job Title" << endl;
				cout << "             Skills x Country" << endl;
				cout << "=========================================" << endl;
				cout << "Enter first attribute: ";
				cin.get();
				getline(cin, toSearch1);
				cout << "Enter second attribute: ";
				getline(cin, toSearch2);
				persons.searchByDouble(toSearch1, toSearch2);
				cin.clear();
			}
		}
	} while (!doneSearching);
}

void Menu::deleteRecords(HashMap& persons)
{
	string toDelete;
	bool exitDeleting = false;
	cin.ignore();
	do {
		cout << "\n=============================================" << endl;
		cout << "Enter Phone No OR Country(-1 to go back): ";
		getline(cin, toDelete);
		cout << "=============================================" << endl;

		if (toDelete == "-1") {
			exitDeleting = true;
		}
		// check if user entered phone number or country
		else if (toDelete[0] >= 65) {
			persons.deleteByString(toDelete);
		}
		else {
			persons.deleteByHash(toDelete);
		}
		cin.clear();
	} while (!exitDeleting);
}

// used to get the person object in the hash table and store each of its attributes in a new file
void Menu::writeToFile(string fname, HashMap& persons)
{
	Node** hashTable = persons.getHashTable();
	ofstream output(fname);
	string line = "";

	for (int i = 0; i < persons.getBuckets(); i++) {
		if (hashTable[i] != NULL) {
			Node* current = hashTable[i];
			while (current != NULL) {
				line += current->data.getID() + '\t' + current->data.getjobTitle() + '\t'
					+ current->data.getEmail() + '\t' + current->data.getLastName() + '\t'
					+ current->data.getFirstName() + '\t' + current->data.getPhoneNo() + '\t'
					+ current->data.getSkills() + '\t' + current->data.getCountry() + '\t' + '\n';
				current = current->next;
			}

		}
	}
	output << line;
	output.close();
	cout << "\nFile with new data has been created" << endl;
}



