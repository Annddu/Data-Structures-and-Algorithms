#include "ExtendedTest.h"
#include "ShortTest.h"

#include "FixedCapBiMap.h"


#include <iostream>
using namespace std;


int main() {
	testAll();
	testRemoveKey();
	testPrevious();
	//testAllExtended();

	cout << "That's all!" << endl;
	system("pause");
	return 0;
}


