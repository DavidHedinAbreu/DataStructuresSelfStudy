#include <iostream>
#include <string>
using namespace std;

class Node {
public:
	// I assumed the node would contain a large object on the heap, requiring a custom destructor.
	// Using an int datatype here is just for testing purposes.
	int* dataPtr = new int;  // create a new ptr to data on the heap
	Node* nextPtr;

	// default constructor
	Node() {
		dataPtr = 0;
		nextPtr = nullptr;
	}
	// parameterized constructor
	Node(int data) {
		*(this->dataPtr) = data;  // make "data" the value of the int on the heap 
		this->nextPtr = nullptr;
	}
	// destructor
	~Node() {
		delete dataPtr; // because data is on the heap, delete it
		dataPtr = nullptr;  // eliminate stale pointers
		nextPtr = nullptr;
	}
	
	//copy constructor 
	Node(const Node &rhs) {
		*dataPtr = *rhs.dataPtr;
		*nextPtr = *rhs.nextPtr;
	}
	
	// copy assignment operator NOT using copy-and-swap idiom
	Node &operator=(Node &rhs)  {
		return *this;
	}

	string toString() {
		return to_string(* (this->dataPtr) );
	}
	
};