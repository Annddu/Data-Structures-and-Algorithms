#pragma once
#include "SortedIteratedList.h"

//DO NOT CHANGE THIS PART
class ListIterator{
	friend class SortedIteratedList;
private:
	const SortedIteratedList& list; // Reference to the list
	ListIterator(const SortedIteratedList& list); // Constructor

	Node* current; // Pointer to the current node
	
public:
	void first();
	void next();
	bool valid() const;
    TComp getCurrent() const;
};


