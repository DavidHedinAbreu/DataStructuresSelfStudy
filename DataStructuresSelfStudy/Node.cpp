#include <iostream>
using namespace std;

class Node {
public:
	int* dataPtr = new int;  // create a new ptr to data on the heap
	Node* nextPtr;
	// default constructor
	Node() {
		dataPtr = 0;
		nextPtr = nullptr;
	}
	// parameterized constructor
	Node(int data) {
		this->dataPtr = &data;
		this->nextPtr = nullptr;
	}
	// destructor
	~Node() {
		delete dataPtr; // because data is on the heap, delete it
		dataPtr = nullptr;  // eliminate stale pointers
		nextPtr = nullptr;
	}
	/*
	// copy constructor (helper to copy assignment operator)
	Node(const Node &rhs) {
		*dataPtr = *rhs.dataPtr;
		*nextPtr = *rhs.nextPtr;
	}
	*/
	// swap function (helper to copy assignment operator)
	friend void swap(Node& a, Node& b) {
		swap(a.dataPtr, b.dataPtr);
		swap(a.nextPtr, b.nextPtr);
	}
	// copy assignment operator using copy-and-swap idiom
	Node& operator=(Node rhs) {
		swap(*this, rhs);
		return *this;
	}
	// move constructor
	Node(Node&& rhs) noexcept : dataPtr(nullptr), nextPtr(nullptr) {
		// copy the state from the source object
		dataPtr = rhs.dataPtr;
		nextPtr = rhs.nextPtr;
		// release the pointers from the source object so the destructor doesn't call delete multiple times
		rhs.dataPtr = nullptr; 
		rhs.nextPtr = nullptr;
	}
	// move assignment operator
	Node &operator=(Node&& rhs) noexcept {
		if (this != &rhs) {
			// free the existing resource
			delete[] dataPtr;
			delete[] nextPtr;
			// copy the state from the source object
			dataPtr = rhs.dataPtr;
			nextPtr = rhs.nextPtr;
			// release the pointers from the source object so the destructor doesn't call delete multiple times
			rhs.dataPtr = nullptr;
			rhs.nextPtr = nullptr;
		}
	}
};