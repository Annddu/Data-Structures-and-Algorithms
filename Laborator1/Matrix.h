#pragma once

//DO NOT CHANGE THIS PART
typedef int TElem;
#define NULL_TELEM 0

// Structure to represent a triple <line, column, value>
struct Triple {
	int line;
	int column;
	TElem value;
};

class Matrix {

private:
	int lines, columns;
	int capacity; // Capacity of the dynamic array
	int size; // Current size of the dynamic array
	Triple* data; // Dynamic array to hold matrix elements

	void resize() {
		if (size == capacity) {
			// Double the capacity
			capacity *= 2;
			Triple* newData = new Triple[capacity];
			// Copy elements to the new array
			for (int i = 0; i < size; ++i) {
				newData[i] = data[i];
			}
			delete[] data;
			data = newData;
		}
	}

public:
	//constructor
	Matrix(int nrLines, int nrCols);

	//destructor
	~Matrix();

	//returns the number of lines
	int nrLines() const;

	//returns the number of columns
	int nrColumns() const;

	//returns the element from line i and column j (indexing starts from 0)
	//throws exception if (i,j) is not a valid position in the Matrix
	TElem element(int i, int j) const;

	//modifies the value from line i and column j
	//returns the previous value from the position
	//throws exception if (i,j) is not a valid position in the Matrix
	TElem modify(int i, int j, TElem e);

	void setMainDiagonal(TElem e);
};
