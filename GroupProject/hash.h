#ifndef HASH_H
#define HASH_H

using namespace std;
#include <string>

class Hash {
private:
	int bucket;
public:
	Hash();
	void insertItem(int index); // in the insert call the hash function?
	void deleteItem(int key);
	int hashFunction(string key);
	void test();
};


#endif // !HASH_H
