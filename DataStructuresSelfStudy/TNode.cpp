#include <iostream>
#include <string>
using namespace std;

class TNode {
public:
	// I assumed the node would contain a large object on the heap, requiring a custom destructor.
	// Using an int datatype created on the heap is just for testing purposes.
	int* dataPtr = new int;  // create a new ptr to data on the heap
	TNode* rightPtr, *leftPtr;

	// default constructor
	TNode() {
		dataPtr = 0;
		leftPtr = rightPtr = nullptr;
	}
	// parameterized constructor
	TNode(int data) {
		*(this->dataPtr) = data;  // make "data" the value of the int on the heap 
		this->leftPtr = this->rightPtr;
	}
	// destructor, recursively deletes the entire subtree from this node down.
	~TNode() {
		delete dataPtr; // because data is on the heap, delete it
		dataPtr = nullptr;  // eliminate stale pointers
		delete leftPtr;  
		leftPtr = nullptr;
		delete rightPtr;
		rightPtr = nullptr;
	}

	//copy constructor 
	TNode(const TNode& rhs) {
		*dataPtr = *rhs.dataPtr;
		*leftPtr = *rhs.leftPtr;
		*rightPtr = *rhs.rightPtr;
	}

	// copy assignment operator NOT using copy-and-swap idiom
	TNode& operator=(TNode& rhs) {
		return *this;
	}

	string toString() {
		return to_string(*(this->dataPtr));
	}

};
