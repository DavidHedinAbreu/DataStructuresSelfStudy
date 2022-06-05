#include "BTNode.cpp"
#include <vector>
#include <string>
#include <queue>
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

	// parameterized constructor
	BTree(vector<int> data) {
		cout << "BTree parameterized constructor called." << endl;
		rootPtr = new BTNode(data[0]);
		for (int i = 1; i < data.size(); i++) {
			this->insert(rootPtr, data[i]);
		}
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
	// If there is no root, insert the new node.  If data < root, insert it on the left.  If data > root, 
	// insert on right.  Otherwise, return the root.
	BTNode* insert(BTNode *root, int data) {
		if (root == nullptr) {
			return new BTNode(data);
		}
			
		if (data < *(root->dataPtr)) {
			root->leftPtr = insert(root->leftPtr, data);
		}
		else if (data > *(root->dataPtr)) {
			root->rightPtr = insert(root->rightPtr, data);
		}
		return root;
	}

	/* Deep copy function, new BTree contains copy of all nodes in original.
	* if you want to create a replica of a tree, put the nodes in an array with a pre-order traversal. 
	* Then perform an Insert operation on a new tree for each value in the array. You will end up with a copy of your original tree.
	*/

	BTree* copy() {
		if (rootPtr == nullptr)
			return new BTree();
		else {
			preOrderTraverse(rootPtr);
			BTree *newBTree = new BTree(nodeData);
			nodeData.clear();
			return newBTree;
		}
	}

	// Return vector of node data while traversing tree using pre-order algorithm.  Parameter should be root node of tree.
	void preOrderTraverse(BTNode *node) {
		cout << "BTree preOrderTraverse called." << endl;
		if (node == nullptr)
			return;
		nodeData.push_back(*(node->dataPtr));
		preOrderTraverse(node->leftPtr);
		preOrderTraverse(node->rightPtr);
	}

	// Return vector of nodes while traversing tree using in-order algorithm.
	void inOrderTraverse(BTNode* node) {
		cout << "BTree inOrderTraverse called." << endl;
		if (node == nullptr)
			return;
		inOrderTraverse(node->leftPtr);
		nodeData.push_back(*(node->dataPtr));
		inOrderTraverse(node->rightPtr);
	}

	// Return vector of nodes while traversing tree using post-order algorithm.
	void postOrderTraverse(BTNode* node) {
		cout << "BTree postOrderTraverse called." << endl;
		if (node == nullptr)
			return;
		postOrderTraverse(node->leftPtr);
		postOrderTraverse(node->rightPtr);
		nodeData.push_back(*(node->dataPtr));
	}

	// Find pointer of BTNode containing particular data.  Parameters are starting root, key.
	// If key not found, returns nullptr.
	BTNode* find(BTNode *root, int key) {
		if (root == nullptr) {
			return nullptr;  // tree is empty
		}
		if (key == *(root->dataPtr)) {
			return root; // root found
		}
		if (root != nullptr && key < *(root->dataPtr)) {
			root = find(root->leftPtr, key);
		}
		if (root != nullptr && key > *(root->dataPtr)) {
			root = find(root->rightPtr, key);
		}
		return root; 
	}

	// Delete the BTNode with a particular data value, given the root node of the tree and the key data value.
	// Assume the key does exist in the tree (the find function was successful).
	BTNode* deleteNode(BTNode* root, int key) {
		if (root == nullptr)
			return root;
		// if the key is smaller, look in the left subtree
		else if (key < *(root->dataPtr) )
			root->leftPtr = deleteNode(root->leftPtr, key);
		// if the key is greater, look in the right subtree
		else if (key > *(root->dataPtr) )
			root->rightPtr = deleteNode(root->rightPtr, key);
		// else this is the node to be deleted
		else if (key == *(root->dataPtr)) {
			// 1.  Remove a leaf from the tree, and set the prececessor's leftPtr and rightPtr to nullptr. 
			if (root->leftPtr == nullptr && root->rightPtr == nullptr) {
				cout << "Node " << *(root->dataPtr) << " is a leaf." << endl;
				return nullptr; // becomes the leftPtr
			}
			// 2.  If the node to be deleted has only one child, copy the child to the predecessor and delete the child.
			else if (root->leftPtr == nullptr) {
				cout << "Node " << *(root->dataPtr) << " has a right child only." << endl;
				BTNode* temp = root->rightPtr;
				delete root;
				root = nullptr;
				return temp;
			} else if (root->rightPtr == nullptr) {
				cout << "Node " << *(root->dataPtr) << " has a left child only." << endl;
				BTNode* temp = root->leftPtr;
				delete root;
				root = nullptr;
				return temp;
			} 
			// 3.  If the root to be deleted has two children, look for the smallest in the right subtree as the inorder successor
			//     Copy the contents of the inorder successor to the note marked for deletion. 
			//     Delete the inorder successor using the function developed for #1.
			else {
				cout << "Node " << *(root->dataPtr) << " has two children." << endl;
				BTNode* temp = minValueNode(root->rightPtr);
				cout << "The inorder successor is node " << *(temp->dataPtr) << endl;
				root->dataPtr = temp->dataPtr;
				root->rightPtr = deleteNode(root->rightPtr, *(temp->dataPtr));
				cout << "Copied the inorder successor to the node and deleted the inorder successor." << endl;
			}
		}
		return root;
	}

	// Helper function for delete.
	BTNode* minValueNode(BTNode* node)
	{
		BTNode* current = node;

		// loop down to find the leftmost leaf 
		while (current && current->leftPtr != NULL)
			current = current->leftPtr;

		return current;
	}

	// Print vector of data from BTNodes.
	string toString() {
		string output = "";
		for (int data : nodeData) {
			output.append(to_string(data));
			output.append(", ");
		}
		return output;
	}

	// Print level order.
	void diagram() {
		if (rootPtr == nullptr)
			return;
		queue<BTNode*> q;
		q.push(rootPtr);
		while (q.empty() == false) {
			int nodeCount = q.size();
			while (nodeCount > 0) {
				BTNode* node = q.front();
				cout << " " << *(node->dataPtr) ;
				q.pop();
				if (node->leftPtr != nullptr)
					q.push(node->leftPtr);
				if (node->rightPtr != nullptr)
					q.push(node->rightPtr);
				nodeCount--;
			}
			cout << endl;
		}
	}
};
