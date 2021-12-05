/*
	A class used to represent a whole hash table (containing node objects) and some useful functions.
*/
#ifndef HASHMAP_H
#define HASHMAP_H

#include "Node.h"
#include <iostream>
#include <vector>

using namespace std;
class HashMap {
private:
	int buckets; // size of the table 
	int noOfRecords; // total number of records in the table
	Node** hashTable; 
public:
	HashMap(int TABLE_SIZE);
	~HashMap();
	int getBuckets();
	int getNoOfRecords();
	Node** getHashTable();
	int hashFunction(string key);
	void setNoOfRecords(int noOfRecords);
	void insertRecord(Person data);

	// deleting functions
	void deleteByHash(string toDelete);
	void deleteByString(string toDelete);

	// searching functions
	void searchByHash(string toSearch);
	void searchByString(string toSearch);
	void searchByDouble(string toSearch1, string toSearch2);
	void deeperSearch(vector <Person> matchedRecords);

	vector <Person> sortRecords(vector <Person> matchedRecords);
	void displayMatchedRecords(vector <Person> matchedRecords);
};
#endif // !HASHMAP_H
