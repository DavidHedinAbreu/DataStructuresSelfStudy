#include <iostream>
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
	time_t start, end;
	time(&start);
	// memory state checkpoint 1, for debugging memory leaks
	_CrtMemState s1, s2, s3;
	_CrtMemCheckpoint(&s1);

	BTree *tree = new BTree();
	/*
	tree->rootPtr = new BTNode(10);
	tree->rootPtr->leftPtr = new BTNode(8);
	tree->rootPtr->rightPtr = new BTNode(12);
	tree->rootPtr->leftPtr->leftPtr = new BTNode(7);
	tree->rootPtr->leftPtr->rightPtr = new BTNode(9);
	tree->rootPtr->rightPtr->leftPtr = new BTNode(11);
	tree->rootPtr->rightPtr->rightPtr = new BTNode(13);
	*/
	tree->insert(tree->rootPtr, 10);
	tree->insert(tree->rootPtr, 8);
	tree->insert(tree->rootPtr, 12);
	tree->insert(tree->rootPtr, 7);
	tree->insert(tree->rootPtr, 9);
	tree->insert(tree->rootPtr, 11);
	tree->insert(tree->rootPtr, 13);

	tree->preOrderTraverse(tree->rootPtr);  // loads nodeData vector; assumes nodeData has been cleared.
	cout << tree->toString() << endl;  // prints nodeData vector
	tree->nodeData.clear();
	tree->inOrderTraverse(tree->rootPtr);  // loads nodeData vector; assumes nodeData has been cleared.
	cout << tree->toString() << endl;  // prints nodeData vector
	tree->nodeData.clear();
	tree->postOrderTraverse(tree->rootPtr);  // loads nodeData vector; assumes nodeData has been cleared.
	cout << tree->toString() << endl;  // prints nodeData vector
	delete tree;

	_CrtMemCheckpoint(&s2);
	if (_CrtMemDifference(&s3, &s1, &s2))
		_CrtMemDumpStatistics(&s3);

	// execution time end, time taken
	time(&end);
	double timeTaken = double(end - start);
	cout << "Time taken is " << timeTaken << " sec." << endl;
	// memory leak report
	_CrtDumpMemoryLeaks();
}
