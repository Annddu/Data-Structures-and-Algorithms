#include "ListIterator.h"
#include "SortedIndexedList.h"
#include <iostream>

using namespace std;

// BC = WC = AC = Theta(1)
ListIterator::ListIterator(const SortedIndexedList& list) : list(list) {
	this->current = list.head; // Initialize the current element with the first element in the list
} 

// BC = WC = AC = Theta(1)
void ListIterator::first(){
	this->current = list.head; // Set the current element to the first element in the list to restart the iteration
}

// BC = WC = AC = Theta(1)
void ListIterator::next(){
	if (valid()) { // Check if the current element is valid
		this->current = list.next[this->current]; // Move to the next element in the list
	}
	else { // If the current element is not valid, throw an exception
		throw exception("Invalid position");
	}
}

// BC = WC = AC = Theta(1)
bool ListIterator::valid() const{
	return this->current != -1; // Check if the current element is valid, -1 marks the end of the list
}

// BC = WC = AC = Theta(1)
TComp ListIterator::getCurrent() const{
	return list.elements[this->current]; // Return the current element
}


