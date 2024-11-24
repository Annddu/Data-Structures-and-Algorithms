#include <iostream>

#include "ShortTest.h"
#include "ExtendedTest.h"
#include <assert.h>
#include <exception>
#include "SortedIteratedList.h"
#include "ListIterator.h"

using namespace std;

bool relation3(TComp e1, TComp e2) {
	if (e1 <= e2) {
		return true;
	}
	else {
		return false;
	}
}

void testFilter() {
	SortedIteratedList list = SortedIteratedList(relation3);
	for (int i = 0; i < 10; i++) {
		list.add(i);
	}
	assert(list.size() == 10);
	Condition c = [](TComp e) {return e % 2 == 0; };
	list.filter(c);
	assert(list.size() == 5);
}

int main(){
	testFilter();
    testAll();
    testAllExtended();
    std::cout<<"Finished IL Tests!"<<std::endl;
	system("pause");
}