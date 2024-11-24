/*
1. ADT Matrix – represented as a sparse matrix, using a dynamic array of triples <line, column, 
value> (value ≠ 0), ordered lexicographically considering the <line, column> of every 
element. 
*/
#include <iostream>
#include <assert.h>
#include "Matrix.h"
#include "ExtendedTest.h"
#include "ShortTest.h"

using namespace std;

void testDiagonal() {
	Matrix m(10000, 10000);
	m.setMainDiagonal(5);
	for (int i = 0; i < 9999; i++) {
		assert(m.element(i, i) == 5);
	}

	Matrix m1(123, 321);
	try {
		m1.setMainDiagonal(5);
	}
	catch (exception&) {
		assert(true);
	}

	std::cout << "Test diagonal" << std::endl;
}

int main() {
	testDiagonal();
	testAll();
	testAllExtended();
	cout << "Test End" << endl;
	system("pause");
}