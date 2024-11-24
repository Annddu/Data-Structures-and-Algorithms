#include "Bag.h"
#include "ShortTest.h"
#include "ExtendedTest.h"
#include <iostream>
#include <assert.h>

using namespace std;

void testFilter() {
	Bag b;
	Condition c = [](int x) {return x % 2 == 0; };
	b.filter(c);
	assert(b.size() == 0);
	for (int i = 0; i < 10000; i++) {
		b.add(i);
		b.add(i);
	}
	b.filter(c);
	assert(b.size() == 10000);
	for (int i = 0; i < 10000; i+=2) {
		assert(b.nrOccurrences(i) == 2);
	}

}

int main() {
	testFilter();
	testAll();
	cout << "Short tests over" << endl;
	//testAllExtended();

	cout << "All test over" << endl;
}