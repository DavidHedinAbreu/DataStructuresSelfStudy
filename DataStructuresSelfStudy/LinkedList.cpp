#include "Node.cpp"
// define and imports for memory leak detection
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

class LinkedList {
public:
	// default constructor
	LinkedList() {
		cout << "default constructor called." << endl;
		headPtr = nullptr;
	}

	// destructor
	~LinkedList() {
		cout << "destructor called." << endl;
		// memory state checkpoint 1, for debugging memory leaks
		//_CrtMemState s1,s2,s3;
		//_CrtMemCheckpoint(&s1);
		if (headPtr == nullptr) {  // delete the head pointer if there's no head
			delete headPtr;
		}
		else {
			Node *temp2 = headPtr->nextPtr;
			delete headPtr;
			Node* temp1 = nullptr;
			while (temp2->nextPtr != nullptr) {  // delete each node so long as there is a next one
				temp1 = temp2;
				temp2 = temp2->nextPtr;
				delete temp1;
				temp1 = nullptr;   // eliminate stale pointers
			}
			delete temp2;  // delete the last node if there's no next node
			temp2 = nullptr;  // eliminate stale pointers
		}
		// memory state checkpoint 2, for debugging memory leaks
		//_CrtMemCheckpoint(&s2);
		//if (_CrtMemDifference(&s3, &s1, &s2))
		//	_CrtMemDumpStatistics(&s3);
	}

	// copy constructor
	LinkedList(const LinkedList& rhs) {
		cout << "copy constructor called" << endl;
		// if there is nothing in the rhs list, the new headPtr should be nullptr
		if (rhs.headPtr == nullptr)
			headPtr = nullptr;
		else {
			// if there is a header in rhs, assign a copy the header of rhs to it.
			headPtr = new Node(*(rhs.headPtr->dataPtr));
			// if there is only one node in the rhs, null the nextPtr for the head 
			if (rhs.headPtr->nextPtr == nullptr)
				headPtr->nextPtr = nullptr;
			else {
				// copy data from rhs head to lhs head
				Node* lhsTemp2 = new Node(*(rhs.headPtr->nextPtr->dataPtr));
				headPtr->nextPtr = lhsTemp2;
				Node* rhsTemp2 = rhs.headPtr->nextPtr;
				Node* lhsTemp1 = headPtr;
				lhsTemp1->nextPtr = lhsTemp2;
				// continue traversing rhs, creating a new node of lhs and copying data 
				// of the corresponding node from rhs into the new lhs node
				while (rhsTemp2->nextPtr != nullptr) {
					lhsTemp2 = new Node(*(rhsTemp2->nextPtr->dataPtr));
					rhsTemp2 = rhsTemp2->nextPtr;
					lhsTemp1 = lhsTemp1->nextPtr;
					lhsTemp1->nextPtr = lhsTemp2;
				}
			}
		}
	}
	// insert a node at the beginning of the list
	void insertFirst(int element) {
		Node* newNode = new Node(element);
		if (headPtr == nullptr) {
			headPtr = newNode;
			return;
		}
		else {
			Node* temp = headPtr;
			headPtr = newNode;
			headPtr->nextPtr = temp;
		}
	}

	// insert a node after the first instance of a node containing particular data
	void insertAfterNodeContaining(int searchData, int newData) {
		Node* newNode = new Node(newData);
		// if the list has no elements, the new node cannot be added after search data
		if (headPtr == nullptr) {
			return;
		}
		else {
			// initialize node temp1, and if the list has more than one element, temp2
			Node* temp1 = headPtr;
			Node* temp2 = nullptr;
			if (temp1->nextPtr != nullptr) {
				temp2 = headPtr->nextPtr;
			}
			// if temp1 does not contain the search data...
			while (*(temp1->dataPtr) != searchData) {
				if (temp2 == nullptr) {  // and there is no temp2
					return;  // the new node could not be added
				}
				else if (temp2->nextPtr != nullptr) {  // and there is another node after temp1, update temp1 and temp2
					temp1 = temp2;
					temp2 = temp2->nextPtr;
				}
				else {  // else there is no next node
					temp1 = temp2;
					temp2 = nullptr;
				}
			}
			temp1->nextPtr = newNode;
			if (temp2 == nullptr) {
				return;
			}
			newNode->nextPtr = temp2;
		}
	}

	// insert a node at the end of the list
	void insertLast(int element) {
		Node* newNode = new Node(element);
		if (headPtr == nullptr) {
			headPtr = newNode;
			return;
		}
		else {
			Node* temp = headPtr;
			while (temp->nextPtr != nullptr) {
				temp = temp->nextPtr;
			}
			temp->nextPtr = newNode;
		}
	}

	// insert a node after a particular node by memory location
	void insertAfterPointer(Node* ptr, int newData) {
		Node* newNode = new Node(newData);
		if (ptr->nextPtr == nullptr) {
			ptr->nextPtr = newNode;
		}
		else {
			newNode->nextPtr = ptr->nextPtr;
			ptr->nextPtr = newNode;
		}
	}

	// find pointer of node after the first instance of a node containing particular data
	Node* findPointerOfNodeContaining(int searchData) {
		Node* temp = headPtr;
		while (*(temp->dataPtr) != searchData) {
			cout << *(temp->dataPtr) << endl;
			if (temp->nextPtr != nullptr)
				temp = temp->nextPtr;
			else
				return nullptr;
		}
		return temp;
	}

	// print the whole list
	void print() {
		Node* temp = headPtr;
		if (temp != NULL) {
			cout << "The list contains: ";
			while (temp != NULL) {
				cout << temp->toString() << " ";
				temp = temp->nextPtr;
			}
			cout << endl;
		}
		else {
			cout << "The list is empty.\n";
		}
	}
private:
	Node* headPtr = new Node();
};
