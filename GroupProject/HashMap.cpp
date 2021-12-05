#include "HashMap.h"
#include "node.h"

#include <string>
#include <iostream>
#include <chrono>
#include <iomanip>

using namespace std;

HashMap::HashMap(int TABLE_SIZE)
{
	buckets = TABLE_SIZE;
	noOfRecords = 0;
	hashTable = new Node * [buckets];
	// set all slots of the array to null so that it can be used for checking
	for (int i = 0; i < buckets; i++) {
		hashTable[i] = NULL;
	}
}

HashMap::~HashMap()
{
	for (int i = 0; i < buckets; i++) {
		Node* currNode = hashTable[i];
		while (currNode != NULL) {
			Node* prevNode = currNode;
			currNode = prevNode->next;
			delete prevNode;
		}
	}
	delete[] hashTable;
}

int HashMap::getBuckets()
{
	return buckets;
}

int HashMap::getNoOfRecords()
{
	return noOfRecords;
}

Node** HashMap::getHashTable()
{
	return hashTable;
}


// called after inserting and deleting records
void HashMap::setNoOfRecords(int noOfRecords)
{
	this->noOfRecords = noOfRecords;
}

// used to calculate the index of where each node should be placed
int HashMap::hashFunction(string key)
{
	size_t value = 0;
	for (int i = 0; i < (int)key.length(); i++) {
		if (key[i] != '-')
		{  
			// use 31 because its a prime number
			value = (value * 31) + key[i];
		}
	}
	return (value % buckets);
}

void HashMap::insertRecord(Person data)
{	
	int index = hashFunction(data.getPhoneNo());
	Node* hashNode = new Node(data);
	if (hashTable[index] == NULL) {
		hashTable[index] = hashNode;
	}
	// seperate chaining part
	else {
		Node* nextNode = hashTable[index]->next;
		hashTable[index]->next = hashNode;
		hashNode->next = nextNode;
	}
}

void HashMap::deleteByHash(string toDelete)
{
	bool isDeleted = false;
	int index = hashFunction(toDelete); 

	Node* current = hashTable[index];
	Node* previous = NULL;

	auto start = chrono::steady_clock::now();
	while (current && current->data.getPhoneNo() != toDelete) {
		previous = current;
		current = current->next;
	}
	if (current) {
		if (previous) {
			previous->next = current->next;
			isDeleted = true;
			delete current;
		}
		else {
			hashTable[index] = current->next;
			isDeleted = true;
			delete current;
		}
	}
	auto end = chrono::steady_clock::now();
	auto duration_micro = chrono::duration_cast<chrono::microseconds>(end - start).count();

	cout << "\n======================================================" << endl;
	if (isDeleted) {
		setNoOfRecords(getNoOfRecords() - 1);
		cout << "The phone number was found and was deleted." << endl;
		cout << "The total amount of records now is: " << getNoOfRecords() << endl;
		cout << "Elapsed time in microseconds: " << duration_micro << " micro sec" << endl;
		cout << "======================================================" << endl;
		return;
	}
	else {
		cout << "The entered phone number was not found in the records." << endl;
		cout << "Elapsed time in microseconds: " << duration_micro << " micro sec" << endl;
		cout << "======================================================" << endl;
		return;
	}
}

void HashMap::deleteByString(string toDelete)
{
	bool haveDeleted = false;
	int totalDeleted = 0;

	auto start = chrono::steady_clock::now();
	for (int i = 0; i < buckets; i++) {
		Node* current = hashTable[i];
		Node* previous = NULL;
		Node* temp = NULL;

		while (current) {
			if (current->data.getCountry() != toDelete) {
				previous = current;
				current = current->next;
			}
			else {
				++totalDeleted;
				haveDeleted = true;
				if (previous) {
					previous->next = current->next;
					temp = current;
					current = previous->next;
					delete temp;
				}
				else {
					hashTable[i] = current->next;
					temp = current;
					current = hashTable[i];
					delete temp;
				}
			}
		}
	}
	auto end = chrono::steady_clock::now();
	auto duration_micro = chrono::duration_cast<chrono::microseconds>(end - start).count();

	cout << "\n==============================================" << endl;
	if (haveDeleted) {
		setNoOfRecords(getNoOfRecords() - totalDeleted);
		cout << totalDeleted << " matching records were found and deleted" << endl;
		cout << "The total amount of records now is: " << getNoOfRecords() << endl;
		cout << "Elapsed time in microseconds: " << duration_micro << " micro sec" << endl;
		cout << "=============================================="s << endl;
		return;
	}
	else {
		cout << "0 matching records were found" << endl;
		cout << "Elapsed time in microseconds: " << duration_micro << " micro sec" << endl;
		cout << "==============================================" << endl;
		return;
	}
}

void HashMap::searchByString(string toSearch)
{
	int totalMatches = 0;
	vector <Person> matchedRecords;
	auto start = chrono::steady_clock::now();
	for (int i = 0; i < buckets; i++) {
		if (hashTable[i] != NULL) {
			Node* current = hashTable[i];
			while (current != NULL) {
				if (toSearch == current->data.getCountry() || toSearch == current->data.getjobTitle() ||
					toSearch == current->data.getSkills() || toSearch == current->data.getPhoneNo()) {
					++totalMatches;
					matchedRecords.push_back(current->data);
				}
				current = current->next;
			}
		}
	}
	auto end = chrono::steady_clock::now();
	auto duration_micro = chrono::duration_cast<chrono::microseconds>(end - start).count();

	if (matchedRecords.size() != 0) {
		// auto start = chrono::steady_clock::now();
		matchedRecords = sortRecords(matchedRecords);
		// auto end = chrono::steady_clock::now();
		// auto duration_micro = chrono::duration_cast<chrono::microseconds>(end - start).count();
		displayMatchedRecords(matchedRecords);
		cout << "\nElapsed time in microseconds: " << duration_micro << " micro sec\n" << endl;
	}

	cout << "\n===============================================" << endl;
	cout << totalMatches << " matching records were found" << endl;
	cout << "Elapsed time in microseconds: " << duration_micro << " micro sec" << endl;
	cout << "===============================================\n" << endl;

	if (matchedRecords.size() != 0) {
		string userInput;
		cout << "\nWould you like to do a deeper search on the matched records?" << endl;
		cout << "Your choice (Y/N): ";
		cin >> userInput;
		if (toupper(userInput[0]) == 'Y') {
			deeperSearch(matchedRecords);
		}
	}
}

void HashMap::searchByHash(string toSearch)
{
	int index = hashFunction(toSearch);
	int totalMatches = 0;
	vector <Person> matchedRecords;
	Node* current = hashTable[index];

	auto start = chrono::steady_clock::now();
	while (current != NULL) {
		if (toSearch == current->data.getPhoneNo()) {
			matchedRecords.push_back(current->data);
			++totalMatches;
		}
		current = current->next;
	}
	auto end = chrono::steady_clock::now();
	auto duration_micro = chrono::duration_cast<chrono::microseconds>(end - start).count();

	if (totalMatches != 0) {
		displayMatchedRecords(matchedRecords);
	}
	cout << "\n===============================================" << endl;
	cout << totalMatches << " matching record was found" << endl;
	cout << "Elapsed time in microseconds: " << duration_micro << " micro sec" << endl;
	cout << "===============================================\n" << endl;
}

void HashMap::deeperSearch(vector<Person> matchedRecords)
{
	string toSearch;
	cout << "\nEnter one of the following attributes" << endl;
	cout << "Only enter the one you havent entered already" << endl;
	cout << "=============================================" << endl;
	cout << "             Skills x Job Title" << endl;
	cout << "             Skills x Country" << endl;
	cout << "             Job Title x Country" << endl;
	cout << "==============================================" << endl;
	cout << "Enter Attribute: ";
	cin.get();
	getline(cin, toSearch);
	int totalMatches = 0;
	vector <Person> newRecords;

	auto start = chrono::steady_clock::now();
	for (int i = 0; i < (int) matchedRecords.size(); i++) {
		if (matchedRecords[i].getjobTitle() == toSearch || matchedRecords[i].getCountry() == toSearch || matchedRecords[i].getSkills() == toSearch) {
			++totalMatches;
			newRecords.push_back(matchedRecords[i]);
		}
	}
	auto end = chrono::steady_clock::now();
	auto duration_micro = chrono::duration_cast<chrono::microseconds>(end - start).count();

	if (newRecords.size() != 0) {
		auto start = chrono::steady_clock::now();
		newRecords = sortRecords(newRecords);
		auto end = chrono::steady_clock::now();
		auto duration_micro = chrono::duration_cast<chrono::microseconds>(end - start).count();
		displayMatchedRecords(newRecords);
		cout << "\nElapsed time in microseconds: " << duration_micro << " micro sec\n" << endl;
	}

	cout << "\n===============================================" << endl;
	cout << totalMatches << " matching records were found" << endl;
	cout << "Elapsed time in microseconds: " << duration_micro << " micro sec" << endl;
	cout << "===============================================\n" << endl;
}

vector <Person> HashMap::sortRecords(vector<Person> matchedRecords)
{
	// insertion sort algorithm
	int i, j;
	Person key;
	for (i = 1; i < (int)matchedRecords.size(); i++)
	{
		key = matchedRecords[i];
		j = i - 1;

		while (j >= 0 && matchedRecords[j].getCountry() > key.getCountry())
		{
			matchedRecords[j + 1] = matchedRecords[j];
			j = j - 1;
		}
		matchedRecords[j + 1] = key;
	}
	return matchedRecords;
}

void HashMap::displayMatchedRecords(vector<Person> matchedRecords)
{
	cout << left;
	cout << "\n\t    Matched Records" << endl;
	cout << "========================================" << endl;

	for (int i = 0; i < (int)matchedRecords.size(); i++) {
		cout << "Matched Record #" << i + 1 << ":" << endl;
		cout << "----------------------------------------" << endl;
		cout << "ID: " << matchedRecords[i].getID() << endl;
		cout << "Job Title: " << matchedRecords[i].getjobTitle() << endl;
		cout << "Email: " << matchedRecords[i].getEmail() << endl;
		cout << "Last Name: " << matchedRecords[i].getLastName() << endl;
		cout << "First Name: " << matchedRecords[i].getFirstName() << endl;
		cout << "Phone No: " << matchedRecords[i].getPhoneNo() << endl;
		cout << "Skills: " << matchedRecords[i].getSkills() << endl;
		cout << "Country: " << matchedRecords[i].getCountry() << endl;
		if (i + 1 != matchedRecords.size()) {
			cout << "----------------------------------------\n" << endl;
		}
	}
	cout << "========================================\n" << endl;
}

void HashMap::searchByDouble(string toSearch1, string toSearch2)
{
	int totalMatches = 0;
	vector <Person> matchedRecords;

	auto start = chrono::steady_clock::now();

	for (int i = 0; i < buckets; i++) {
		if (hashTable[i] != NULL) {
			Node* current = hashTable[i];
			while (current != NULL) {
				if ((toSearch1 == current->data.getCountry() && toSearch2 == current->data.getSkills()) ||
					(toSearch2 == current->data.getCountry() && toSearch1 == current->data.getSkills()) ||
					(toSearch1 == current->data.getSkills() && toSearch2 == current->data.getjobTitle()) ||
					(toSearch2 == current->data.getSkills() && toSearch1 == current->data.getjobTitle()) ||
					(toSearch1 == current->data.getCountry() && toSearch2 == current->data.getjobTitle()) ||
					(toSearch2 == current->data.getjobTitle() && toSearch1 == current->data.getCountry	())){
					++totalMatches;
					matchedRecords.push_back(current->data);
				}
				current = current->next;
			}
		}
	}
	auto end = chrono::steady_clock::now();
	auto duration_micro = chrono::duration_cast<chrono::microseconds>(end - start).count();

	if (matchedRecords.size() != 0) {
		matchedRecords = sortRecords(matchedRecords);
		displayMatchedRecords(matchedRecords);
	}
	cout << "\n===============================================" << endl;
	cout << totalMatches << " matching records were found" << endl;
	cout << "Elapsed time in microseconds: " << duration_micro << " micro sec" << endl;
	cout << "===============================================\n" << endl;
}





