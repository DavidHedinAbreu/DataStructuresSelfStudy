#include "BTNode.cpp"
#include <vector>
#include <string>
// define and imports for memory leak detection
// #define _CRTDBG_MAP_ALLOC
// #include <stdlib.h>
// #include <crtdbg.h>

class BTree {
public:
	BTNode* rootPtr = new BTNode();
	vector<int> nodeData;

	// default constructor
	BTree() {
		cout << "BTree default constructor called." << endl;
		rootPtr = nullptr;
	}

	// destructor, recursively deletes entire tree from root node downward
	~BTree() {
		cout << "Btree destructor called." << endl;
		// memory state checkpoint 1, for debugging memory leaks
		//_CrtMemState s1,s2,s3;
		//_CrtMemCheckpoint(&s1);
		delete rootPtr;
		rootPtr = nullptr; 
		// memory state checkpoint 2, for debugging memory leaks
		//_CrtMemCheckpoint(&s2);
		//if (_CrtMemDifference(&s3, &s1, &s2))
		//	_CrtMemDumpStatistics(&s3);
	}

	// Shallow copy constructor, new BTree points to SAME nodes as original.
	BTree(const BTree& rhs) {
		cout << "BTree copy constructor called" << endl;
		rootPtr = rhs.rootPtr;
	}

	// Insert a new BTNode containing the given data after a particular root node with given memory location.
	// If data < root, insert it on the left.  If data > root, insert on right.  If there is no root, 
	// insert the new node.  Otherwise, return the root.
	BTNode* insert(BTNode *root, int data) {
		if (root == nullptr)
			return new BTNode(data);
		BTNode *newNode = new BTNode(data);
		if (data < *(root->dataPtr))
			root->leftPtr = insert(root->leftPtr, data);
		else if (data > *(root->dataPtr))
			root->rightPtr = insert(root->rightPtr, data);
		return root;
	}

	/* Deep copy function, new BTree contains copy of all nodes in original.
	* if you want to create a replica of a tree, put the nodes in an array with a pre-order traversal. 
	* Then perform an Insert operation on a new tree for each value in the array. You will end up with a copy of your original tree.
	*/
	BTree* copy(BTree rhs) {
		BTree *newBTree = new BTree();
		if (rhs.rootPtr == nullptr)
			return newBTree;  // return empty BTree

		return newBTree;
	}

	BTNode* copyHelper(BTNode *node) {
		if (node == nullptr)
			return nullptr;
		BTNode next = *node;
		next.leftPtr = copyHelper(node->leftPtr);
		next.rightPtr = copyHelper(node->rightPtr);
		return &next;
	}


	// Return vector of node data while traversing tree using pre-order algorithm.  Parameter should be root node.
	void preOrderTraverse(BTNode *node) {
		if (node == nullptr)
			return;
		cout << "BTree preOrderTraverse called on node " << *(node->dataPtr) << "." << endl;
		nodeData.push_back(*(node->dataPtr));
		preOrderTraverse(node->leftPtr);
		preOrderTraverse(node->rightPtr);
	}

	// Return vector of nodes while traversing tree using in-order algorithm.
	void inOrderTraverse(BTNode* node) {
		if (node == nullptr)
			return;
		cout << "BTree inOrderTraverse called on node " << *(node->dataPtr) << "." << endl;
		inOrderTraverse(node->leftPtr);
		nodeData.push_back(*(node->dataPtr));
		inOrderTraverse(node->rightPtr);
	}

	// Return vector of nodes while traversing tree using post-order algorithm.
	void postOrderTraverse(BTNode* node) {
		if (node == nullptr)
			return;
		cout << "BTree postOrderTraverse called on node " << *(node->dataPtr) << "." << endl;
		postOrderTraverse(node->leftPtr);
		postOrderTraverse(node->rightPtr);
		nodeData.push_back(*(node->dataPtr));
	}

	// Find pointer of BTNode containing particular data.

	// Delete a BTNode at a particular memory location.
	
	// Print vector of BTNodes.
	string toString() {
		string output = "";
		for (int data : nodeData) {
			output.append(to_string(data));
			output.append(", ");
		}
		return output;
	}


};
