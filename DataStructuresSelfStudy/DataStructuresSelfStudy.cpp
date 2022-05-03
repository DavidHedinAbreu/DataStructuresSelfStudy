#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include "LinkedList.cpp"

using namespace std;

Node bogus(Node n) {
	cout << "bogus method called" << endl;
	return n;
}

int main()
{
	time_t start, end;
	time(&start);

	LinkedList *l = new LinkedList();
	for (int i = 0; i < 100000; i++) {
		l->insertLast(i);
	}
	//l->print();
	
	time(&end);
	double timeTaken = double(end - start);
	cout << "Time taken is " << timeTaken << setprecision(3) << " sec." << endl;
}
