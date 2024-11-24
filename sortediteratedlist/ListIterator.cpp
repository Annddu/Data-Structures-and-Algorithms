#include "ListIterator.h"
#include "SortedIteratedList.h"
#include <exception>

using namespace std;

// BC = WC = TC = Theta(1)
ListIterator::ListIterator(const SortedIteratedList& list) : list(list) {
	this->current = this->list.head; // Initialize the current node with the head of the list for the first iteration
}

// BC = WC = TC = Theta(1)
void ListIterator::first(){
	this->current = this->list.head; // Set the current node to the head of the list, like in the constructor
}

// BC = WC = TC = Theta(1)
void ListIterator::next(){
	if (valid()) { // If the current node is valid (not nullptr, not the end of the list), move to the next node
		this->current = this->current->next; // Move to the next node
	}
	else { // If the current node is invalid, throw an exception
		throw std::exception("Invalid iterator position");
	}
}

// BC = WC = TC = Theta(1)
bool ListIterator::valid() const{
	return this->current != nullptr; // Return true if the current node is not nullptr(not the end of the list), false otherwise
}

// BC = WC = TC = Theta(1)
TComp ListIterator::getCurrent() const{
	return this->current->data; // Return the data of the current node
}