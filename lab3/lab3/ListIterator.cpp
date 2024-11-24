#include "ListIterator.h"
#include "SortedIndexedList.h"
#include <iostream>

using namespace std;

ListIterator::ListIterator(const SortedIndexedList& list) : list(list) {
	//TODO - Implementation
	position = list.head;
}

void ListIterator::first(){
	//TODO - Implementation
	position = list.head;
}

void ListIterator::next(){
	//TODO - Implementation
	if (!valid()) {
		throw std::runtime_error("Iterator is not valid.");
	}

	// Move to the next element in the list
	position = list.elements[position].next;
}

bool ListIterator::valid() const{
	//TODO - Implementation
	return position >= 0 && position < list.Tposition;
}

TComp ListIterator::getCurrent() const{
	//TODO - Implementation
	if(!valid()) {
		throw exception("Iterator is not valid.");
	}
	// Return the data of the current element
	return list.elements[position].data;
}


