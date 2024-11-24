#pragma once
//DO NOT INCLUDE LISTITERATOR

//DO NOT CHANGE THIS PART
class ListIterator;
typedef int TComp;
typedef bool (*Relation)(TComp, TComp);
#define NULL_TCOMP -11111

class SortedIndexedList {
private:
	friend class ListIterator;
private:
	// ADT SortedList (interface with Tpozition = Integer, SortedIndexedList) - using a SLLA where the elements are ordered based on a relation
	int head; // The index of the first element in the list 
	int firstEmpty; // The index of the first empty position in the list
	int capacity; // The maximum number of elements that can be stored in the list
	int* next; // Array of integers where next[i] is the index of the next element in the list after the element at index i
	int nrOfElements; // The current number of elements in the list
	TComp* elements; // Array of TComp where elements[i] is the element at index i in the list
	
	Relation relation; // The relation used to order the elements in the list

public:
	// constructor
	SortedIndexedList(Relation r);

	// returns the size of the list
	int size() const;

	//checks if the list is empty
	bool isEmpty() const;

	// returns an element from a position
	//throws exception if the position is not valid
	TComp getElement(int pos) const;

	// adds an element in the sortedList (to the corresponding position)
	void add(TComp e);

	// removes an element from a given position
	//returns the removed element
	//throws an exception if the position is not valid
	TComp remove(int pos);

	// searches for an element and returns the first position where the element appears or -1 if the element is not in the list
	int search(TComp e) const;

	// returns an iterator set to the first element of the list or invalid if the list is empty
	ListIterator iterator();

	//destructor
	~SortedIndexedList();

	//returns the last index of a given element
	//returns -1 if the element is not in the list
	int lastIndexOf(TComp e) const;

};
