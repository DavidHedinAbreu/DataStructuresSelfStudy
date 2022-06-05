#include <iostream>
#include <time.h>
#include <iomanip>
#include <string>
#include <vector>
#include "BTree.cpp"
// define and imports for memory leak detection
#include <stdlib.h>
#include <crtdbg.h>
#define _CRTDBG_MAP_ALLOC  // detailed debug report

using namespace std;

int main()
{
	// execution time start
	clock_t start, end;
	double timeTaken;
	start = clock();
	// memory state checkpoint 1, for debugging memory leaks
	// memory state checkpoint 1, for debugging memory leaks
	_CrtMemState s1, s2, s3;
	_CrtMemCheckpoint(&s1);
	 
	vector<int> data{ 10, 8, 12, 7, 13 };
	BTree *tree = new BTree(data);
	tree->diagram();

	//cout << "Get the pointer to the node containing the key that is to be deleted." << endl;
	//BTNode* nodeToDelete = tree->find(tree->rootPtr, 13);
	int x = 8;
	cout << "Delete node " << x << "." << endl;
	BTNode* newRoot = tree->deleteNode(tree->rootPtr, x);
	tree->diagram();

	//BTree* tree2 = tree->copy();

	//tree->preOrderTraverse(tree->rootPtr);  // loads nodeData vector; assumes nodeData has been cleared.
	//cout << tree->toString() << endl;  // prints nodeData vector
	//tree->nodeData.clear();

	delete tree;

	_CrtMemCheckpoint(&s2);
	if (_CrtMemDifference(&s3, &s1, &s2))
		_CrtMemDumpStatistics(&s3);

	// execution time end, time taken
	end = clock();
	timeTaken = (double)(end - start)/CLOCKS_PER_SEC;
	cout << "Time taken is " << fixed << setprecision(3) << timeTaken << " sec." << endl;
	// memory leak report
	_CrtDumpMemoryLeaks();
}
