#include <iostream>

#include "ShortTest.h"
#include "ExtendedTest.h"
#include "SortedIndexedList.h"
#include "ListIterator.h"
#include <assert.h>


//27. ADT SortedList (interface with Tpozition = Integer, SortedIndexedList) - using a SLLA where the elements are ordered based on a relation
int main(){
    //testAll();
    testAllExtended();
    std::cout<<"Finished IL Tests!"<<std::endl;
	system("pause");
}