#include "TNode.cpp"
// define and imports for memory leak detection
// #define _CRTDBG_MAP_ALLOC
// #include <stdlib.h>
// #include <crtdbg.h>

class Tree {
public:
	// default constructor
	Tree() {
		cout << "default constructor called." << endl;
		headPtr = nullptr;
	}

	// destructor
	~Tree() {
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
	// return nodes while traversing tree using pre-order

	// return nodes while traversing tree using in-order

	// return nodes while traversing tree using post-order

	// find pointer of TNode containing particular data

	// insert a TNode after a particular TNode with given memory location

	// delete a TNode at a particular memory location
	
	// print TNode (Should this be in TNode class?)

private:
	TNode* headPtr = new TNode();
};
