#include "ListIterator.h"
#include "SortedIndexedList.h"
#include <iostream>
using namespace std;
#include <exception>


// BC = WC = Theta(number of elements in the list)
// TC = O(number of elements in the list)
SortedIndexedList::SortedIndexedList(Relation r) {
	this->capacity = 1; // Initial capacity
	this->elements = new TComp[this->capacity]; // Allocate memory for elements
	this->next = new int[this->capacity]; // Allocate memory for next pointers
	this->head = -1; // Initialize head to -1
	for (int i = 0; i <= this->capacity -1; i++) { // Initialize next pointers to point to the next slot
		this->next[i] = i + 1;
	}
	this->next[this->capacity - 1] = -1; // Last slot points to -1, as it is the last slot
	this->firstEmpty = 0; // Initialize firstEmpty to 0
	this->nrOfElements = 0; // Initialize list size to 0
	this->relation = r; // Initialize relation
}

// BC = WC = AC = Theta(1)
int SortedIndexedList::size() const {
	return this->nrOfElements; // Return the size of the list
}

// BC = WC = AC = Theta(1)
bool SortedIndexedList::isEmpty() const {
	return this->nrOfElements == 0; // Return true if the list is empty, false otherwise
}

// BC = Theta(1) if the element is the first in the list
// WC = Theta(number of elements in the list) if the element is the last in the list 
//TC = O(number of elements in the list)
TComp SortedIndexedList::getElement(int i) const{
	if (i < 0 || i >= this->nrOfElements) { // Check if the position is valid
        throw exception("Invalid position"); // Throw exception if the position is invalid
    }

    int current = this->head; // Start from the head
    int currentPos = 0; // Initialize the current position to 0
    while (current != -1 && currentPos < i) { // Iterate through the list until the position is reached
        current = this->next[current]; // Move to the next element
        currentPos++; // Increment the current position
    }
    if (current != -1) { // Check if the position was reached
        return this->elements[current]; // Return the element at the position
    }
    else { // If the position was not reached, throw exception
        throw exception("Invalid position");
    }
}

// BC = Theta(1) if the element is the first in the list
// WC = Theta(number of elements in the list) if the element is the last in the list
// TC = O(number of elements in the list)
TComp SortedIndexedList::remove(int i) {
	if (i < 0 || i >= this->nrOfElements) { // Check if the position is valid
		throw exception("Invalid position");
	}

	// Get the position of the element to be removed
	int current = this->head; // Start from the head
	int previous = -1; // Initialize the previous element to -1
	int currentPos = 0; // Initialize the current position to 0
	while (current != -1 && currentPos < i) { // Iterate through the list until the position is reached
		previous = current; // Update the previous element
		current = this->next[current]; // Move to the next element
		currentPos++; // Increment the current position
	}

	if (previous == -1) { // Check if the element to be removed is the head
		this->head = this->next[current]; // Update the head to the next element
	}
	else {
		this->next[previous] = this->next[current]; // Removing a non-head element, update the next pointer of the previous element
	}

	this->next[current] = this->firstEmpty; // Update next[current] to point to first empty slot
	this->firstEmpty = current; // Update firstEmpty to the removed element
	this->nrOfElements--; // Decrement list size

	return this->elements[current]; // Return the removed element
}

// BC = Theta(1) if the element is the first in the list
// WC = Theta(number of elements in the list) if the element is the last in the list or the element is not in the list
// TC = O(number of elements in the list)
int SortedIndexedList::search(TComp e) const {
	int poz = 0; // Initialize the position to 0
	int current = this->head; // Start from the head
	while (current != -1 && this->elements[current] != e) { // Iterate through the list until the element is found
		current = this->next[current]; // Move to the next element
		poz++; // Increment the position
	}
	if (current != -1) { // Check if the element was found
		return poz; // Return the position of the element
	}
	else { // If the element was not found, return -1
		return -1;
	}
}


// BC = Theta(1) if the element is the elemet needs to be added is the first in the list
// WC = Theta(number of elements in the list) if the element needs to be added is the last in the list or can t be added
// TC = O(number of elements in the list)
void SortedIndexedList::add(TComp e) {
	if (this->nrOfElements == this->capacity -1) { // Check if the list is full and resize if necessary
		TComp* newElements = new TComp[this->capacity * 2]; // Allocate memory for new elements
		int* newNext = new int[this->capacity * 2]; // Allocate memory for new next pointers
		
		for (int i = 0; i <= this->capacity - 1; i++) { // Copy old elements and next pointers
			newElements[i] = this->elements[i]; 
			newNext[i] = this->next[i];
		}

		for (int i = this->capacity; i < this->capacity * 2 - 1; i++) { // Initialize new empty slots in next array like in initial constructor
			newNext[i] = i + 1;
		}
		newNext[this->capacity * 2 - 1] = -1;  // Last slot points to -1

		delete[] this->elements; // Delete old elements
		delete[] this->next; // Delete old next pointers

		this->elements = newElements; // Update elements
		this->next = newNext; // Update next pointers
		this->firstEmpty = this->capacity; // Update firstEmpty

		this->capacity *= 2; // Update capacity
	}

	// Find position to insert
	int poz = 0; // Initialize position to 0
	int current = this->head; // Start from the head
	int previous = -1; // Initialize previous element to -1
	while (current != -1 && relation(this->elements[current], e)) { // Iterate through the list until the position is found
		previous = current; // Update previous element
		current = this->next[current]; // Move to the next element
		poz++; // Increment position
	}

	// Insert the element
	int newPosition = this->firstEmpty; // Get the first empty slot
	this->elements[newPosition] = e; // Insert the element
	this->firstEmpty = this->next[this->firstEmpty];  // Update firstEmpty

	if (previous == -1) { // Check if the element is the head, if it is
		this->next[newPosition] = this->head; // Update next pointer of the new element this the head
		this->head = newPosition; // Update head to the new element
	}
	else { // If the element is not the head
		this->next[newPosition] = this->next[previous]; // Update next pointer of the new element to the next pointer of the previous element
		this->next[previous] = newPosition; // Update next pointer of the previous element to the new element
	}
	this->nrOfElements++; // Increment list size
}

// BC = WC = AC = Theta(1)
ListIterator SortedIndexedList::iterator(){
	return ListIterator(*this); // Return an iterator for the list
}

// BC = WC = AC = Theta(1)
SortedIndexedList::~SortedIndexedList() {
	delete[] this->elements; // Delete elements
	delete[] this->next; // Delete next pointers
}

// BC = WC = Theta(number of elements in the list) 
// TC = O(number of elements in the list)
int SortedIndexedList::lastIndexOf(TComp e) const {
	int poz = -1; // Initialize position to -1
	int current = this->head; // Start from the head
	int currentPos = 0; // Initialize current position to 0
	while (current != -1) { // Iterate through the list
			if (this->elements[current] == e) { // Check if the element is the one we are looking for
						poz = currentPos; // Update position
					}
			current = this->next[current]; // Move to the next element
			currentPos++; // Increment current position
		}
	return poz; // Return the position
}