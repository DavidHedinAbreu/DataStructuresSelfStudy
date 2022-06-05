#include <iostream>
#include <string>
using namespace std;

class BTNode {
public:
	// I assumed the node would contain a large object on the heap, requiring a custom destructor.
	// Using an int datatype created on the heap is just for testing purposes.
	int* dataPtr = new int;  // create a new ptr to data on the heap
	BTNode* rightPtr, *leftPtr;

	// default constructor
	BTNode() {
		cout << "BTNode default constructor called." << endl;
		dataPtr = nullptr;
		leftPtr = rightPtr = nullptr;
		leftPtr = rightPtr = nullptr;
	}
	// parameterized constructor
	BTNode(int data) {
		cout << "BTNode parameterized constructor called." << endl;
		*(dataPtr) = data;  // make "data" the value of the int on the heap 
		leftPtr = rightPtr = nullptr;
	}
	// destructor, recursively deletes the entire subtree from this node down.
	~BTNode() {
		cout << "BTNode destructor called." << endl;
		delete dataPtr; // because data is on the heap, delete it
		dataPtr = nullptr;  // eliminate stale pointers
		delete leftPtr;  
		leftPtr = nullptr;
		delete rightPtr;
		rightPtr = nullptr;
	}

	//copy constructor 
	BTNode(const BTNode& rhs) {
		//cout << "BTNode copy constructor called on node " << *(rhs.dataPtr) << endl;
		*dataPtr = *rhs.dataPtr;
		*leftPtr = *rhs.leftPtr;
		*rightPtr = *rhs.rightPtr;
	}

	// copy assignment operator NOT using copy-and-swap idiom
	BTNode& operator=(BTNode& rhs) {
		//cout << "BTNode copy assignment operator called on node " << *(rhs.dataPtr) << endl;
		return *this;
	}

	string toString() {
		return to_string(*(this->dataPtr));
	}

};
