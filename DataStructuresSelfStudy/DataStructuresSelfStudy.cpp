#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include "LinkedList.cpp"
// define and imports for memory leak detection
#include <stdlib.h>
#include <crtdbg.h>
#define _CRTDBG_MAP_ALLOC  // detailed debug report

using namespace std;

SLNode bogus(SLNode n) {
	cout << "bogus method called" << endl;
	return n;
}

int main()
{
	// execution time start
	time_t start, end;
	time(&start);
	// memory state checkpoint 1, for debugging memory leaks
	_CrtMemState s1, s2, s3;
	_CrtMemCheckpoint(&s1);

	LinkedList* l1 = new LinkedList();
	for (int i = 0; i < 10; i++) {
		l1->insertLast(i);
	}

	vector<LinkedList> v;
	for (int i = 0; i < 100; i++) {
		v.push_back(*l1);
		// memory state checkpoint 2, for debugging memory leaks
	}
	for (LinkedList l : v) {
		l.print();
	}

	_CrtMemCheckpoint(&s2);
	if (_CrtMemDifference(&s3, &s1, &s2))
		_CrtMemDumpStatistics(&s3);



	delete l1;
	//delete &v;  // all elements of container are deleted when container is deleted.
	//delete &l2;

	// execution time end, time taken
	time(&end);
	double timeTaken = double(end - start);
	cout << "Time taken is " << timeTaken << " sec." << endl;
	// memory leak report
	_CrtDumpMemoryLeaks();
}
