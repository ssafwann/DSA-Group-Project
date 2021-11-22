/*
	A class used to represent a whole hash table (containing nodes)
*/
#ifndef HASHMAP_H
#define HASHMAP_H

#include "Node.h"

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

	void deleteByHash(string toDelete); // this function is for deleting phone num
	void deleteByString(string toDelete); // this function is for deleting country

};
#endif // !HASHMAP_H
