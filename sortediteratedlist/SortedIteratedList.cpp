#include "ListIterator.h"
#include "SortedIteratedList.h"
#include <iostream>
using namespace std;
#include <exception>

// BC = WC = TC = Theta(1)
SortedIteratedList::SortedIteratedList(Relation r) {
	this->head = nullptr; // Initialize the head pointer to nullptr
	this->relation = r; // Initialize the relation
	this->numeberOfElements = 0; // Initialize the number of elements to 0
}

// BC = WC = TC = Theta(numeberOfElements)
void SortedIteratedList::filter(Condition c) {
	Node* current = this->head;
	Node* prev = nullptr;
	while (current != nullptr) {
		if (!c(current->data)) {
			if (prev == nullptr) {
				Node* next = current->next;
				delete current;
				current = next;
				this->head = current;
				this->numeberOfElements--;
			}
			else {
				Node* next = current->next;
				delete current;
				current = next;
				prev->next = current;
				this->numeberOfElements--;
			}
		}
		else {
			prev = current;
			current = current->next;
		}
	}
}

// BC = WC = TC = Theta(1)
int SortedIteratedList::size() const {
	return this->numeberOfElements; // Return the number of elements in the list
}

// BC = WC = TC = Theta(1)
bool SortedIteratedList::isEmpty() const {
	return this->numeberOfElements == 0; //Return true if the list is empty, false otherwise
}

// BC = WC = TC = Theta(1)
ListIterator SortedIteratedList::first() const {
	return ListIterator(*this);  // Create a new iterator and return it, *this is the SortedIteratedList object
}

// BC = WC = TC = Theta(1)
TComp SortedIteratedList::getElement(ListIterator poz) const {
	Node* nodePtr = poz.current; // Get the current node from the iterator
	if (nodePtr == nullptr) { // if the node is null(there is no element at the current position) throw an exception
		throw exception("Invalid iterator position");
	}
	return nodePtr->data; // Return the data from the current node
}

// BC = Theta(1) when the element is the head of the list
// WC = Theta(numeberOfElements) when the element is the last element in the list or the element is not in the list
// TC = O(numeberOfElements)
TComp SortedIteratedList::remove(ListIterator& poz) {
	Node* nodePtr = poz.current; // Get the current node from the iterator
	if (nodePtr == nullptr) { // if the node is null(there is no element at the current position) throw an exception
		throw std::exception("Invalid iterator position");
	}

	poz.next(); // Move the iterator to the next position because the current node will be removed

	// We need tho nodes because we are going to remove the current node
	// so we are going to link the previous node with the next node of the current node
	Node* current = this->head; // Node user for looping through the list
	Node* prev = nullptr; // Node used to store the previous node

	while (current != nullptr && current != nodePtr) { // Loop through the list until we find the node that we want to remove
													   // we stop when we reach the end of the list or when we find the node that we want to remove
													   // the end of the list is nullptr because lasteElemet->next is a nullptr	
		prev = current;
		current = current->next;
	}

	if (current == nullptr) { //If the current node is nullptr, we reached the end of the list and we didn't find the node that we want to remove
		throw exception("Invalid iterator position");
	}

	if (prev == nullptr) { //If the previous node is nullptr, the current node is the head of the list (the first node)
		this->head = current->next; // Set the head of the list to the next node of the current node
	}
	else { // If the previous node is not nullptr(the current node is not the head of the list ) and we found the node that we want to remove
		prev->next = current->next; // Link the previous node with the next node of the current node
	}

	TComp removedData = current->data; // Store the data from the current node because we are going to delete it and we need to return the data
	delete current; // Delete the current node
	this->numeberOfElements--; //Decrease the number of elements in the list

	return removedData; // Return the data from the removed node
}

// BC = Theta(1) when the element is the head of the list
// WC = Theta(numeberOfElements) when the element is the last element in the list or the element is not in the list
// TC = O(numeberOfElements)
ListIterator SortedIteratedList::search(TComp e) const {
	Node* current = this->head; // Node used for looping through the list
	while (current != nullptr && current->data != e) { // Loop through the list until we find the element that we are looking for
													   // we stop when we reach the end of the list or when we find the node
													   // the end of the list is nullptr because lasteElemet->next is a nullptr	
		current = current->next;
	}
	ListIterator it(*this); // Create a new iterator
	it.current = current; // Set the current node of the iterator to the searched node
	return it; // Return the iterator
}

// BC = Theta(1) when the element should be added before the head of the list or the list is empty
// WC = Theta(numeberOfElements) when the element should be added at the end of the list or the element cant be added due to the relation
// TC = O(numeberOfElements)
void SortedIteratedList::add(TComp e) {
	Node* newNode = new Node(e); // Create a new node with the given data, this is the node that we are going to add to the list

	// Check if the list is empty or if the new element should be the new head
	if (this->head == nullptr) { // If the list is empty 
		newNode->next = nullptr; // The next node of the new node is nullptr because it is the only node in the list
		this->head = newNode;		// Set the head of the list to the new node
	}
	else if (!relation(head->data, e)) { // If the new element should be added before the head of the list(the relation between the head and the new element is false)
		newNode->next = this->head; // The next node of the new node is the current head
		this->head = newNode; // Set the head of the list to the new node
	}
	else { // If the new element should be added after the head of the list
		// We need two nodes because we are going to add the new node between two nodes
		Node* current = head; // Node used for looping through the list
		Node* prev = nullptr; // Node used to store the previous node

		while (current != nullptr && relation(current->data, e)) { //Loop through the list until we find the right position to add the new node
																	// we stop when we reach the end of the list or when we find the right position
																	// the end of the list is nullptr because lasteElemet->next is a nullptr
			prev = current;
			current = current->next;
		}

		newNode->next = current; // The next node of the new node is the current node
		prev->next = newNode; // Link the previous node with the new node
	}
	this->numeberOfElements++; // Increase the number of elements in the list
}

// BC = WC = TC = Theta(numeberOfElements)
SortedIteratedList::~SortedIteratedList() {
	Node* current = this->head; // Node used for looping through the list
	while (current != nullptr) { // Loop through the list until we reach the end of the list
			Node* next = current->next; // Store the next node
			delete current; // Delete the current node
			current = next; // Move to the next node
		}
}
