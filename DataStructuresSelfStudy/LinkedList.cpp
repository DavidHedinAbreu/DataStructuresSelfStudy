#include "Node.cpp"


class LinkedList {
public:
	// default constructor
	LinkedList() {
		headPtr = nullptr;
	}
	// destructor
	~LinkedList() {
		if(headPtr != nullptr) {
			Node* currentNodePtr = headPtr;
			Node* nextNodePtr = currentNodePtr->nextPtr;
			while (nextNodePtr != nullptr) {
				headPtr = nextNodePtr;
				delete currentNodePtr;  // do I need to instantiate a new currentNodePtr?
				// Node* currentNodePtr = headPtr;
				currentNodePtr = headPtr;
				nextNodePtr = currentNodePtr->nextPtr;
			}
		}
	}
	// swap function (helper to copy assignment operator)

	// copy assignment operator using copy-and-swap idiom

	// move constructor

	// move assignment operator

	// insert a node at the beginning of the list

	// insert a node in the middle of the list

	// insert a node at the end of the list
	void insertLast(int element) {
		Node* newNode = new Node();
		newNode->dataPtr = &element;
		newNode->nextPtr = nullptr;
		if (headPtr == nullptr) {
			headPtr = newNode;
		}
		else {
			Node* temp = headPtr;
			while (temp->nextPtr != nullptr) {
				temp = temp->nextPtr;
			}
			temp->nextPtr = newNode;
		}
	}
	// delete a node

	// print the whole list
	void print() {
		Node* temp = headPtr;
		if (temp != NULL) {
			cout << "The list contains: ";
			while (temp != NULL) {
				cout << *(temp->dataPtr) << " ";
				temp = temp->nextPtr;
			}
			cout << endl;
		}
		else {
			cout << "The list is empty.\n";
		}
	}
private: 
	Node *headPtr = new Node();
};