#include "HashMap.h"
#include "node.h"

#include <string>
#include <iostream>
using namespace std;


HashMap::HashMap(int TABLE_SIZE)
{
	buckets = TABLE_SIZE;
	noOfRecords = 0;
	hashTable = new Node * [buckets];
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



// function will be called after inserting all the rows from the file
void HashMap::setNoOfRecords(int noOfRecords)
{
	this->noOfRecords = noOfRecords;
}

int HashMap::hashFunction(string key)
{
	size_t value = 0;
	for (int i = 0; i < (int)key.length(); i++) {
		if (key[i] != '-')
		{  
			//value += (key[i] * (int)pow(33, i)) % buckets;
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
	else {
		Node* nextNode = hashTable[index]->next;
		hashTable[index]->next = hashNode;
		hashNode->next = nextNode;
	}

}


void HashMap::displayWholeTable() {
	for (int i = 0; i < buckets; i++) {
		if (hashTable[i] == NULL) {
			cout << "Bucket " << i + 1 << " is empty\n" << endl;
		}
		else {
			Node* current = hashTable[i];
			while (current != NULL) {
				cout << "Bucket " << i + 1 << ": " << current->data.getID() << endl;
				current = current->next;
			}
			cout << endl;
		}
	}
	cout << endl;
}

void HashMap::deleteByHash(string toDelete)
{
	int index = hashFunction(toDelete); // position of where the phone number is 

}

void HashMap::deleteByString(string toDelete)
{
	// loop through whole hashtable to check if any record matches "toDelete" string.
	// if matches then delete
}




