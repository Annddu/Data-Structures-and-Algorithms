#include "Bag.h"

class BagIterator
{
	//DO NOT CHANGE THIS PART
	friend class Bag;
	
private:
	const Bag& bag; // Reference to the bag we are iterating
	Node* currentNode; // Pointer to the current node in the bag
	int currentFrequency; // The frequency of the current element (we need this to know how many times we have to iterate over the same element)

	BagIterator(const Bag& c);
public:
	void first();
	void next();
	TElem getCurrent() const;
	bool valid() const;
};
