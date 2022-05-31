#include "SLNode.cpp"
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
			SLNode *temp2 = headPtr->nextPtr;
			delete headPtr;
			SLNode* temp1 = nullptr;
			while (temp2->nextPtr != nullptr) {  // delete each SLNode so long as there is a next one
				temp1 = temp2;
				temp2 = temp2->nextPtr;
				delete temp1;
				temp1 = nullptr;   // eliminate stale pointers
			}
			delete temp2;  // delete the last SLNode if there's no next SLNode
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
			headPtr = new SLNode(*(rhs.headPtr->dataPtr));
			// if there is only one SLNode in the rhs, null the nextPtr for the head 
			if (rhs.headPtr->nextPtr == nullptr)
				headPtr->nextPtr = nullptr;
			else {
				// copy data from rhs head to lhs head
				SLNode* lhsTemp2 = new SLNode(*(rhs.headPtr->nextPtr->dataPtr));
				headPtr->nextPtr = lhsTemp2;
				SLNode* rhsTemp2 = rhs.headPtr->nextPtr;
				SLNode* lhsTemp1 = headPtr;
				lhsTemp1->nextPtr = lhsTemp2;
				// continue traversing rhs, creating a new SLNode of lhs and copying data 
				// of the corresponding SLNode from rhs into the new lhs SLNode
				while (rhsTemp2->nextPtr != nullptr) {
					lhsTemp2 = new SLNode(*(rhsTemp2->nextPtr->dataPtr));
					rhsTemp2 = rhsTemp2->nextPtr;
					lhsTemp1 = lhsTemp1->nextPtr;
					lhsTemp1->nextPtr = lhsTemp2;
				}
			}
		}
	}
	// insert a SLNode at the beginning of the list
	void insertFirst(int element) {
		SLNode* newSLNode = new SLNode(element);
		if (headPtr == nullptr) {
			headPtr = newSLNode;
			return;
		}
		else {
			SLNode* temp = headPtr;
			headPtr = newSLNode;
			headPtr->nextPtr = temp;
		}
	}

	// insert a SLNode after the first instance of a SLNode containing particular data
	void insertAfterSLNodeContaining(int searchData, int newData) {
		SLNode* newSLNode = new SLNode(newData);
		// if the list has no elements, the new SLNode cannot be added after search data
		if (headPtr == nullptr) {
			return;
		}
		else {
			// initialize SLNode temp1, and if the list has more than one element, temp2
			SLNode* temp1 = headPtr;
			SLNode* temp2 = nullptr;
			if (temp1->nextPtr != nullptr) {
				temp2 = headPtr->nextPtr;
			}
			// if temp1 does not contain the search data...
			while (*(temp1->dataPtr) != searchData) {
				if (temp2 == nullptr) {  // and there is no temp2
					return;  // the new SLNode could not be added
				}
				else if (temp2->nextPtr != nullptr) {  // and there is another SLNode after temp1, update temp1 and temp2
					temp1 = temp2;
					temp2 = temp2->nextPtr;
				}
				else {  // else there is no next SLNode
					temp1 = temp2;
					temp2 = nullptr;
				}
			}
			temp1->nextPtr = newSLNode;
			if (temp2 == nullptr) {
				return;
			}
			newSLNode->nextPtr = temp2;
		}
	}

	// insert a SLNode at the end of the list
	void insertLast(int element) {
		SLNode* newSLNode = new SLNode(element);
		if (headPtr == nullptr) {
			headPtr = newSLNode;
			return;
		}
		else {
			SLNode* temp = headPtr;
			while (temp->nextPtr != nullptr) {
				temp = temp->nextPtr;
			}
			temp->nextPtr = newSLNode;
		}
	}

	// insert a SLNode after a particular SLNode by memory location
	void insertAfterPointer(SLNode* ptr, int newData) {
		SLNode* newSLNode = new SLNode(newData);
		if (ptr->nextPtr == nullptr) {
			ptr->nextPtr = newSLNode;
		}
		else {
			newSLNode->nextPtr = ptr->nextPtr;
			ptr->nextPtr = newSLNode;
		}
	}

	// find pointer of SLNode after the first instance of a SLNode containing particular data
	SLNode* findPointerOfSLNodeContaining(int searchData) {
		SLNode* temp = headPtr;
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
		SLNode* temp = headPtr;
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
	SLNode* headPtr = new SLNode();
};
