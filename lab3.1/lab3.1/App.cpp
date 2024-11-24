#include <iostream>

#include "ShortTest.h"
#include "ExtendedTest.h"

#include "SortedIndexedList.h"
#include "ListIterator.h"
#include <assert.h>

void testLastIndexOf()
{
    SortedIndexedList s1{[](TComp e1, TComp e2) { return e1 <= e2; }};
    for (int i = 9999; i >= 0; i--)
    {
		s1.add(i);
        s1.add(i);
	}

    for(int i = 0; i < 10000; i++)
		assert(s1.lastIndexOf(i) == 2*i+1);

    for(int i = 10000; i < 20000; i++)
        assert(s1.lastIndexOf(i) == -1);

    std::cout << "Last Index List Done" << std::endl;
}

//27. ADT SortedList (interface with Tpozition, SortedIndexedList) - using a SLLA where elements are ordered based on a relation
int main(){
    testLastIndexOf();
    testAll();
    testAllExtended();
    std::cout<<"Finished IL Tests!"<<std::endl;
	system("pause");
}