#include <iostream>
#include <string>
using namespace std;

class SLNode {
public:
	// I assumed the node would contain a large object on the heap, requiring a custom destructor.
	// Using an int datatype created on the heap is just for testing purposes.
	int* dataPtr = new int;  // create a new ptr to data on the heap
	SLNode* nextPtr;

	// default constructor
	SLNode() {
		dataPtr = 0;
		nextPtr = nullptr;
	}
	// parameterized constructor
	SLNode(int data) {
		*(this->dataPtr) = data;  // make "data" the value of the int on the heap 
		this->nextPtr = nullptr;
	}
	// destructor, recursively deletes sublist from this node to the end
	~SLNode() {
		delete dataPtr; // because data is on the heap, delete it
		dataPtr = nullptr;  // eliminate stale pointers
		delete nextPtr;
		nextPtr = nullptr;
	}

	//copy constructor 
	SLNode(const SLNode& rhs) {
		*dataPtr = *rhs.dataPtr;
		*nextPtr = *rhs.nextPtr;
	}

	// copy assignment operator NOT using copy-and-swap idiom
	SLNode& operator=(SLNode& rhs) {
		return *this;
	}

	string toString() {
		return to_string(*(this->dataPtr));
	}

};
