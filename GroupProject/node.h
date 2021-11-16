/*
	A class used to represent a single node object
*/
#ifndef NODE_H
#define NODE_H

#include "person.h"

class Node {
public:
	Node* next;
	Person data;
	Node(Person data) {
		this->data = data;
	}
};

#endif // !NODE_H
