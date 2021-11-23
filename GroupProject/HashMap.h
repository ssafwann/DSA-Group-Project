/*
	A class used to represent a whole hash table (containing nodes)
*/
#ifndef HASHMAP_H
#define HASHMAP_H

#include "Node.h"
#include <iostream>

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
	void displayWholeTable(); // will delete later, just for testing

	void deleteByHash(string toDelete); 
	void deleteByString(string toDelete); 

	void searchByString(string toSearch);
	void searchByHash(string toSearch);

};
#endif // !HASHMAP_H
