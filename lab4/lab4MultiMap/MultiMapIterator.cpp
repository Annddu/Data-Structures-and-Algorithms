#include "MultiMapIterator.h"
#include "MultiMap.h"


// WC: Theta(1)
// BC: Theta(1)
// AC: Theta(1)
MultiMapIterator::MultiMapIterator(const MultiMap& c): col(c) {
	first();
}

// WC: Theta(1)
// BC: Theta(1)
// AC: Theta(1)
TElem MultiMapIterator::getCurrent() const {
	if (!valid())
		throw std::exception();
	return TElem(currentNode->key, currentNode->value); // returns the current element
}

// WC: Theta(1)
// BC: Theta(1)
// AC: Theta(1)
bool MultiMapIterator::valid() const {
	return bucketIndex < col.capacity; // checks if the bucket index is less than the capacity of the table
}

// WC: Theta(1)
// BC: Theta(1)
// AC: Theta(1)
void MultiMapIterator::next() {
	if (!valid()) // checks if the current element is valid
		throw std::exception();
	if (currentNode->next != nullptr) { // checks if the current node has a next element
		currentNode = currentNode->next; // moves to the next element
	}
	else {
		bucketIndex++; // moves to the next bucket
		while (bucketIndex < col.capacity && col.table[bucketIndex] == nullptr) // searches for the next non-empty bucket
			bucketIndex++;
		if (bucketIndex < col.capacity) // checks if the bucket index is less than the capacity of the table
			currentNode = col.table[bucketIndex];
	}
}

// WC: Theta(1)
// BC: Theta(1)
// AC: Theta(1)
void MultiMapIterator::first() {
	bucketIndex = 0; // initializes the bucket index
	while (bucketIndex < col.capacity && col.table[bucketIndex] == nullptr) // searches for the first non-empty bucket
		bucketIndex++; 
	if (bucketIndex < col.capacity) // checks if the bucket index is less than the capacity of the table
		currentNode = col.table[bucketIndex]; // initializes the current node
}

