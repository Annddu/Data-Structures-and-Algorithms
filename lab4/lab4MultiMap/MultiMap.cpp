#include "MultiMap.h"
#include "MultiMapIterator.h"
#include <exception>
#include <iostream>

using namespace std;

// BC: Theta(numElements) we need to initialize the table with nullptr
// WC: Theta(numElements)
// TC: O(numElements)
MultiMap::MultiMap() {
	this->capacity = 10;
	this->numElements = 0;
	this->loadFactor = 0.7;
	this->table = new Node * [this->capacity];
	for (int i = 0; i < this->capacity; i++) {
		this->table[i] = nullptr;
	}
}

// BC: Theta(1)
// WC: Theta(1)
// TC: Theta(1)
int MultiMap::hashFunction(TKey c) const {
	return abs(c) % this->capacity; // returns the hash value of the key, which is the remainder of the division 
									// of the absolute value of the key by the capacity of the table
}

// BC: Theta(numElements)
// WC: Theta(numElements)
// TC: O(numElements)
void MultiMap::resizeAndRehash() {
	Node** newTable = new Node * [2 * this->capacity]; // creates a new table with double the capacity of the current table
	for (int i = 0; i < 2 * this->capacity; i++) { // initializes the new table with nullptr
		newTable[i] = nullptr; 
	}
	for (int i = 0; i < this->capacity; i++) { // rehashes the elements from the current table to the new table
		Node* current = this->table[i]; // iterates through the current table
		while (current != nullptr) { // rehashes the current element
			Node* next = current->next; // saves the next element
			int newHash = abs(current->key) % (2 * this->capacity); // calculates the new hash value of the current element
			current->next = newTable[newHash]; // adds the current element to the new table
			newTable[newHash] = current; // updates the new table
			current = next; // moves to the next element
		}
	}
	delete[] this->table; // deletes the current table
	this->table = newTable; // updates the current table
	this->capacity *= 2; // updates the capacity of the table
}

// BC: Theta(1)
// WC: Theta(1)
// TC: Theta(1)
void MultiMap::add(TKey c, TValue v) {
	if (this->numElements >= this->loadFactor * this->capacity) { // checks if the load factor is exceeded
		this->resizeAndRehash(); // resizes and rehashes the table
	}
	int hash = this->hashFunction(c); // calculates the hash value of the key
	Node* newNode = new Node; // creates a new node
	newNode->key = c; // initializes the key of the new node
	newNode->value = v; // initializes the value of the new node
	newNode->next = this->table[hash]; // adds the new node to the table
	this->table[hash] = newNode; // updates the table
	this->numElements++; // updates the number of elements
}

// BC: Theta(1) when the element is the first in the list
// WC: Theta(numElements) when the element is the last in the list and and all the elements have the same hash value(not that probable)
// TC: O(numElements)
bool MultiMap::remove(TKey c, TValue v) {
	int hash = this->hashFunction(c); // calculates the hash value of the key
	Node* current = this->table[hash]; // initializes the current node
	Node* previous = nullptr; // initializes the previous node
	while (current != nullptr) { // iterates through the elements with the same hash value
		if (current->key == c && current->value == v) { // checks if the current element is the one to be removed
			if (previous == nullptr) { // case when the element is the first in the list
				this->table[hash] = current->next; // updates the table
			}
			else { // case when the element is not the first in the list
				previous->next = current->next; // updates the table
			}
			delete current; // deletes the element
			this->numElements--; // updates the number of elements
			return true; // returns true
		}	
		previous = current; // updates the previous node
		current = current->next; // moves to the next node
	}
	return false; // returns false
}

// BC: Theta(numElements)
// WC: Theta(numElements)
// TC: O(numElements)
vector<TValue> MultiMap::removeKey(TKey key) {
	vector<TValue> values; // initializes the vector of values
	int hash = this->hashFunction(key); // calculates the hash value of the key
	Node* current = this->table[hash]; // initializes the current node
	Node* previous = nullptr; // initializes the previous node

	while (current != nullptr) { // iterates through the elements with the same hash value
		if (current->key == key) { // checks if the current element has the same key as the one to be removed
			if (previous == nullptr) { // case when the element is the first in the list
				this->table[hash] = current->next; // updates the table
			}
			else { // case when the element is not the first in the list
				previous->next = current->next; // updates the table
			}
			values.push_back(current->value); // adds the value of the current element to the vector
			Node* next = current->next; // saves the next element
			delete current; // deletes the current element
			this->numElements--; // updates the number of elements
			current = next; // moves to the next element
		}
		else { // case when the current element is not the one to be removed
			previous = current; // updates the previous node
			current = current->next; // moves to the next node
		}
	}
	return values; // returns the vector of values
}

// BC: Theta(1) when the element is the first in the list
// WC: Theta(numElements) when the element is the last in the list and and all the elements have the same hash value(not that probable)
// TC: O(numElements)
vector<TValue> MultiMap::search(TKey c) const {
	vector<TValue> values; // initializes the vector of values
	int hash = this->hashFunction(c); // calculates the hash value of the key
	Node* current = this->table[hash]; // initializes the current node
	while (current != nullptr) { // iterates through the elements with the same hash value
		if (current->key == c) { // checks if the current element has the same key as the one searched
			values.push_back(current->value); // adds the value of the current element to the vector
		}
		current = current->next; // moves to the next element
	}
	return values; // returns the vector of values
}

// BC: Theta(1)
// WC: Theta(1)
// TC: Theta(1)
int MultiMap::size() const {
	return numElements;
}

// BC: Theta(1)
// WC: Theta(1)
// TC: Theta(1)
bool MultiMap::isEmpty() const {
	return numElements == 0;
}

// BC: Theta(1)
// WC: Theta(1)
// TC: Theta(1)
MultiMapIterator MultiMap::iterator() const {
	return MultiMapIterator(*this);
}

// BC: Theta(numElements)
// WC: Theta(numElements)
// TC: O(numElements)
MultiMap::~MultiMap() {
	for (int i = 0; i < this->capacity; i++) { // iterates through the table
		Node* current = this->table[i]; // initializes the current node
		while (current != nullptr) { // iterates through the elements with the same hash value
			Node* next = current->next; // saves the next element
			delete current; // deletes the current element
			current = next; // moves to the next element
		}
	}
}

