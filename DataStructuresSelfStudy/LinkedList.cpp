#include "Node.cpp"


class LinkedList {
public:
	// default constructor
	LinkedList() {
		headPtr = nullptr;
	}
	// destructor
	~LinkedList() {
		if (headPtr == nullptr) {  // delete the head pointer if there's no head
			delete headPtr;
		} 
		else while(headPtr->nextPtr != nullptr) {  // delete each node so long as there is a next one
			Node* temp = nullptr;
			temp = headPtr;
			headPtr = headPtr->nextPtr;
			delete temp;
		}
		delete headPtr;  // delete the head pointer if there's no next node
	}

	// copy assignment operator NOT using copy-and-swap idiom


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
	void insertAfterPointer(Node *ptr, int newData) {
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