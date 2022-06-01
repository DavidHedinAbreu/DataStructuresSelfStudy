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

	// Deep copy constructor, new BTree contains copy of all nodes in original.
	
	// Return vector of node data while traversing tree using pre-order algorithm.  Parameter should be root node.
	vector<int> preOrderTraverse(BTNode *node) {
		cout << "BTree preOrderTraverse called." << endl;
		nodeData.push_back(*(node->dataPtr));
		cout << node->dataPtr << " " << node->leftPtr << " " << node->rightPtr << endl;
		if(node->leftPtr != nullptr)
			preOrderTraverse(node->leftPtr);
		if (node->rightPtr != nullptr)
			preOrderTraverse(node->rightPtr);
		return nodeData;
	}

	// Return vector of nodes while traversing tree using in-order algorithm.
	vector<int> inOrderTraverse(BTNode* node) {
		cout << "BTree inOrderTraverse called." << endl;
		nodeData.push_back(*(node->dataPtr));
		if (node->leftPtr != nullptr)
			preOrderTraverse(node->leftPtr);
		cout << node->dataPtr << " " << node->leftPtr << " " << node->rightPtr << endl;
		if (node->rightPtr != nullptr)
			preOrderTraverse(node->rightPtr);
		return nodeData;
	}

	// Return vector of nodes while traversing tree using post-order algorithm.
	vector<int> postOrderTraverse(BTNode* node) {
		cout << "BTree postOrderTraverse called." << endl;
		nodeData.push_back(*(node->dataPtr));
		if (node->leftPtr != nullptr)
			preOrderTraverse(node->leftPtr);
		if (node->rightPtr != nullptr)
			preOrderTraverse(node->rightPtr);
		cout << node->dataPtr << " " << node->leftPtr << " " << node->rightPtr << endl;
		return nodeData;
	}

	// Find pointer of BTNode containing particular data.

	// Insert a BTNode after a particular BTNode with given memory location.

	// Delete a BTNode at a particular memory location.
	
	// Print vector of BTNodes.
	string toString() {
		string output = "";
		for (int data : nodeData)
			output.append(to_string(data));
			output.append(" ");
		return output;
	}


};
