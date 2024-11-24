#pragma once
#include "MultiMap.h"

class MultiMap;

class MultiMapIterator
{
	friend class MultiMap;

	// ADT MultiMap – using a hashtable with separate chaining in which (key, value) pairs are 
	// stored.If a key has multiple values, it appears in multiple pairs.
private:
	const MultiMap& col;
	//TODO - Representation
	int bucketIndex; // the index of the current bucket, which is the index of the current element in the table
	MultiMap::Node* currentNode; // the current node

	//DO NOT CHANGE THIS PART
	MultiMapIterator(const MultiMap& c);

public:
	TElem getCurrent()const;
	bool valid() const;
	void next();
	void first();
};

