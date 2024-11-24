#include "Matrix.h"
#include <exception>
using namespace std;


Matrix::Matrix(int nrLines, int nrCols) {   
	lines = nrLines;
	columns = nrCols;
	capacity = 10;
	size = 0;
	data = new Triple[capacity];
}

// BC = WC = TC = Theta(1)
Matrix::~Matrix() { 
	delete[] data;
}

// BC = WC = TC = Theta(1)
int Matrix::nrLines() const {
	return this->lines;
}

// BC = WC = TC = Theta(1)
int Matrix::nrColumns() const {
	return this->columns;
}

// BC = Theta(1) - if the element is the first in the dynamic array or the index is invalid
// WC = Theta(nr. of elements from the matrix) - if the element is the last in the dynamic array or the element is not found
// TC = O(nr. of elements from the matrix)
TElem Matrix::element(int i, int j) const {
	if (i < 0 || i >= lines || j < 0 || j >= columns) {
		throw exception("Invalid position");
	}
	// Search for the element in the dynamic array
	for (int k = 0; k < size; ++k) {
		if (data[k].line == i && data[k].column == j) {
			return data[k].value;
		}
	}
	return NULL_TELEM; // Element not found
}

// BC = Theta(1) - if the element is the first in the dynamic array or the index is invalid
// WC = Theta(nr. of elements from the matrix) - if the element is the last in the dynamic array or the element is not found
// TC = O(nr. of elements from the matrix)
TElem Matrix::modify(int i, int j, TElem e) {
	if (i < 0 || i >= lines || j < 0 || j >= columns) {
		throw exception("Invalid position");
	}
	// Search for the element in the dynamic array
	for (int k = 0; k < size; ++k) {
		if (data[k].line == i && data[k].column == j) {
			TElem oldValue = data[k].value;
			data[k].value = e;
			return oldValue;
		}
	}
	// Element not found, add it to the dynamic array
	resize(); // Resize the array if needed
	data[size++] = { i, j, e };
	return NULL_TELEM; // Previous value not found, return 0
}


// BC = Theta(1) - if the matrix is not square
// WC = Theta(nr. of elements from the matrix * nr. of lines) - if the matrix is square
// TC = O(nr. of elements from the matrix * nr. of lines)
void Matrix::setMainDiagonal(TElem e) {
	// Check if the matrix is square, if not throw an exception
	if (this->lines != this->columns) {
		throw exception("The matrix is not a square matrix");
	}

	// Search for the elements on the main diagonal and modify them
	for (int i = 0; i < this->lines; i++) {
		modify(i, i, e);
	}
}