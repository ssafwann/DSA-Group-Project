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
	int noOfRecords; 
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
	//void removeRecord(Person data);


	void displayWholeTable();

};
#endif // !HASHMAP_H
