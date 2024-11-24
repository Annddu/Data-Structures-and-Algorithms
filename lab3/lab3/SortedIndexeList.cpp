#include "ListIterator.h"
#include "SortedIndexedList.h"
#include <iostream>
using namespace std;
#include <exception>

SortedIndexedList::SortedIndexedList(Relation r) {
	//TODO - Implementation
	capacity = 10;  // Initial capacity, you can adjust this as needed
	elements = new Node[capacity];
	head = -1;
	Tposition = 0;
	relation = r;
}

int SortedIndexedList::size() const {
	//TODO - Implementation
	return Tposition;
	//return 0;
}

bool SortedIndexedList::isEmpty() const {
	//TODO - Implementation
	return size() == 0;
	//return false;
}

TComp SortedIndexedList::getElement(int i) const{
	//TODO - Implementation
	//return NULL_TCOMP;
	if (i < 0 || i >= Tposition) {
		throw exception("Invalid position");
	}
	int current = head;
	while (i > 0) {
		current = elements[current].next;
		i--;
	}
	return elements[current].data;
}

TComp SortedIndexedList::remove(int i) {
	//TODO - Implementation
	if (i < 0 || i >= Tposition) {
		throw std::runtime_error("Invalid position");
	}

	int current = head;
	int prev = -1;

	// Traverse to the element to be removed
	while (i > 0) {
		prev = current;
		current = elements[current].next;
		i--;
	}

	// Update list pointers to remove the element
	if (prev == -1) {
		// Removing the first element (head)
		head = elements[current].next;
	}
	else {
		elements[prev].next = elements[current].next;
	}

	// Clear the removed element's next pointer and update size
	TComp e = elements[current].data;
	elements[current].next = -1;
	Tposition--;
	return e;
}

int SortedIndexedList::search(TComp e) const {
	//TODO - Implementation
	int current = head;
	int pos = 0;

	while (current != -1 && elements[current].data != e) {
		current = elements[current].next;
		pos++;
	}

	if (current == -1) {
		return -1; // Element not found
	}
	else {
		return pos;
	}
}

void SortedIndexedList::add(TComp e) {
	//TODO - Implementation
	// Resize array if necessary
	if (Tposition == capacity) {
		capacity *= 2;
		Node* newElements = new Node[capacity];
		for (int i = 0; i < Tposition; i++) {
			newElements[i] = elements[i];
		}
		delete[] elements;
		elements = newElements;
	}

	// Find the position to insert the new element
	int current = head;
	int prev = -1;
	while (current != -1 && relation(elements[current].data, e)) {
		prev = current;
		current = elements[current].next;
	}

	// Create a new node for the new element
	Node newNode;
	newNode.data = e;
	newNode.next = current;

	// Insert the new element
	if (prev == -1) {
		// Inserting at the beginning of the list
		head = Tposition;
	}
	else {
		elements[prev].next = Tposition;
	}

	elements[Tposition] = newNode;
	Tposition++;


}

ListIterator SortedIndexedList::iterator(){
	return ListIterator(*this);

}

//destructor
SortedIndexedList::~SortedIndexedList() {
	//TODO - Implementation
	delete[] elements;
}
