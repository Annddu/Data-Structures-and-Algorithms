#include <exception>
#include "BagIterator.h"
#include "Bag.h"

using namespace std;

// We use this function to initialize the iterator
// It is the same with the first function because we initialize the iterator from the beginning of the list
// BC = WC = AC = Theta(1)
BagIterator::BagIterator(const Bag& c): bag(c)
{
	this->currentNode = bag.head; // Initialize the current node with the first node in the list
	this->currentFrequency = 0; // Initialize the current frequency with 0
}

// We use this function to start the iterator from the beginning of the list
// BC = WC = AC = Theta(1)
void BagIterator::first() {
	this->currentNode = bag.head; // Initialize the current node with the first node in the list
	this->currentFrequency = 0; // Initialize the current frequency with 0
}

// We use this function to move the iterator to the next element in the list
// BC = WC = AC = Theta(1)
void BagIterator::next() {
	if (!valid()) { // If the iterator is not valid, we throw an exception
		throw exception();
	}

	// Move to the next occurrence or next node
	if (this->currentFrequency + 1 < this->currentNode->frequency) { // If we have more occurrences of the current element move to the next occurrence of the current element
		this->currentFrequency++;
	}
	else { // If we don't have more occurrences of the current element move to the next node
		this->currentNode = this->currentNode->next;
		this->currentFrequency = 0;
	}
}

// We use this function to check if the iterator is valid (if it is not at the end of the list)
// When the last node is alocated, the next field is set to nullptr
// BC = WC = AC = Theta(1)
bool BagIterator::valid() const {
	// If the current node is not null, the iterator is valid
	return this->currentNode != nullptr;
}


// We use this function to get the current element in the list
// BC = WC = AC = Theta(1)
TElem BagIterator::getCurrent() const
{
	if (!valid()) { // If the iterator is not valid, we throw an exception
		throw exception();
	}
	return this->currentNode->element; // Return the current element if the iterator is valid
}
