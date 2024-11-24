#pragma once
#include "SortedSet.h"

//DO NOT CHANGE THIS PART
class SortedSetIterator
{
	friend class SortedSet;
private:
	const SortedSet& multime;
	SortedSetIterator(const SortedSet& m);

	//TODO - Representation
	TComp current; // Current index in the array
	TComp* values; // Array of elements

	// function to parse the tree in order
	// and store the elements in the array
	// for the iterator
	void inOrder(SortedSet::Node* root);

public:
	~SortedSetIterator();
	void first();
	void next();
	TElem getCurrent();
	bool valid() const;
};

