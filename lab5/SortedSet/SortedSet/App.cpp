#include "ShortTest.h"
#include "ExtendedTest.h"
#include "SortedSet.h"
#include "SortedSetIterator.h"
#include <iostream>
#include <assert.h>

using namespace std;

bool relation(TComp e1, TComp e2) {
	if (e1 <= e2) {
		return true;
	}
	else {
		return false;
	}
}

void testGetRange()
{
	SortedSet s(relation);
	assert(s.isEmpty() == true);
	assert(s.size() == 0);
	
	assert(s.getRange() == -1);
	for (int i = 100; i >= 0; i--)
		assert(s.add(i) == true);
	for (int i = 0; i <= 100; i++)
	{
		assert(s.getRange() == 100 - i);
		assert(s.remove(i));
	}
	cout << "Get range passed\n";
}

int main() {
	testGetRange();
	testAll();
	testAllExtended();

	cout << "Test end" << endl;
	system("pause");
	_CrtDumpMemoryLeaks();
}