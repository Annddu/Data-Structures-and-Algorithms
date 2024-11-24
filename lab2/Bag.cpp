#include "Bag.h"
#include "BagIterator.h"
#include <exception>
#include <iostream>
using namespace std;

// We need to initialize the linked list with the head set to null and the number of elements set to 0
// BC = WC = TC = Theta(1)
Bag::Bag() {
	//Initialize an empty bag
	this->head = nullptr; //The head of the linked list is set to null
	this->numberOfElements = 0; //The number of elements is set to 0
}

// Add the element to the linked list
// BC = Theta(1) when the element is found at the head of the list
// WC = Theta(numberOfElements) when the element is not found in the list or is found at the end of the list
// TC = O(numberOfElements)
void Bag::add(TElem elem) {
	//Search for the element in the list
	Node* foundNode = this->head; //Start from the head of the list (a pointer to the first node)
	while (foundNode != nullptr) {
		if (foundNode->element == elem) { //If the element is found exit the loop
			break;
		}
		foundNode = foundNode->next;
	}

	if (foundNode != nullptr) { //If the element is found increment the frequency and the number of elements
		foundNode->frequency++;
		this->numberOfElements++;
	}
	else { //If the element is not found add it to the linked list by creating a new node and connecting it to the head, the new node will become the head
		Node* newNode = new Node(elem);
		newNode->next = this->head;
		this->head = newNode;
		this->numberOfElements++;
	}
}

// Remove the element from the linked list
// BC = Theta(1) when the element is found at the head of the list
// WC = Theta(numberOfElements) when the element is not found in the list or is found at the end of the list
// TC = O(numberOfElements)
bool Bag::remove(TElem elem) {
	//We need to loop through the linked list with two nodes because we need to connect the previous node
	//to the next node (the one after current node) when we remove the current node
	Node* prev = nullptr; //The previous node is set to null
	Node* current = this->head; //The current node is set to the head of the list
	while (current != nullptr) { //Search for the element in the list
		if (current->element == elem) { //If the element is found
			if (current->frequency > 1) { //If the frequency is greater than 1 decrement the frequency and the number of elements adn return true
				current->frequency--;
				this->numberOfElements--;
				return true;
			}
			else { //If the frequency is 1 delete the node and connect the previous node to the next node
				if (prev == nullptr) { //If the element is the head of the list set the head to the next node (start of the list)
					this->head = current->next;
				}
				else { //If the element is not the head of the list connect the previous node to the next node
					prev->next = current->next;
				}
				delete current; //Delete the node
				this->numberOfElements--; //Decrement the number of elements
			}
			return true; //Return true after the element is removed
		}
		prev = current; //Move the previous node to the current node, this is for looping through the list
		current = current->next; //Move the current node to the next node, this is for looping through the list
	}
	return false; //If the element is not found return false
}

// Search for the element in the linked list
// We cant use this function for remove or add because we need the memory address of the that node
// BC = Theta(1) when the element is found at the head of the list
// WC = Theta(numberOfElements) when the element is not found in the list or is found at the end of the list
// TC = O(numberOfElements)
bool Bag::search(TElem elem) const {
	//Search for the element in the list
	Node* current = this->head; //Start from the head of the list (a pointer to the first node)
	while (current != nullptr) { //Loop through the list
		if (current->element == elem) { //If the element is found return true
			return true;
		}
		current = current->next; //Move to the next node
	}
	return false; //If the element is not found return false
}

// Count the number of occurrences of the element in the linked list
// BC = Theta(1) when the element is found at the head of the list
// WC = Theta(numberOfElements) when the element is not found in the list or is found at the end of the list
// TC = O(numberOfElements)
int Bag::nrOccurrences(TElem elem) const {
	//First we need to search for the element in the list because we need the frequency of the element and we dont have a pointer to the node
	Node* foundNode = this->head; //Start from the head of the list (a pointer to the first node)
	while (foundNode != nullptr) { //Loop through the list
		if (foundNode->element == elem) { //If the element is found exit the loop
			break;
		}
		foundNode = foundNode->next; //Move to the next node
	}
	
	if (foundNode != nullptr) { //If the element is found return the frequency of the element
		return foundNode->frequency;
	}
	return 0; //If the element is not found return 0
}

// The number of elements in the linked list
// BC = WC = TC = Theta(1)
int Bag::size() const {
	//Return the number of elements in the linked list
	return this->numberOfElements;
}

// Check if the linked list is empty
// BC = WC = TC = Theta(1)
bool Bag::isEmpty() const {
	//Return true if the number of elements is 0 (the linked list is empty) and false otherwise
	return this->numberOfElements == 0;
}

// Create an iterator for the linked list
// BC = WC = TC = Theta(1)
BagIterator Bag::iterator() const {
	//Return an iterator for the linked list
	return BagIterator(*this);
}

// BC = WC = TC = Theta(numberOfElements) 
void Bag::filter(Condition cond) {
	//We need to loop through the linked list with two nodes because we need to connect the previous node
	//to the next node (the one after current node) when we remove the current node
	Node* prev = nullptr; //The previous node is set to null
	Node* current = this->head; //The current node is set to the head of the list
	while (current != nullptr) { //Loop through the list
		if (!cond(current->element)) { //If the condition is not met
			if (prev == nullptr) { //If the element is the head of the list set the head to the next node (start of the list)
				this->head = current->next;
			}
			else { //If the element is not the head of the list connect the previous node to the next node
				prev->next = current->next;
			}
			this->numberOfElements = this->numberOfElements - current->frequency;
			Node* next = current->next; //Save the next node
			delete current; //Delete the current node
			current = next; //Move to the next node
		}
		prev = current; //Move the previous node to the current node
		current = current->next; //Move the current node to the next 
	}
}

// Destructor for the linked list
// BC = WC = TC = O(numberOfElements)
Bag::~Bag() {
	//Clear the memory allocated for the linked list
	Node* current = this->head; //Start from the head of the list (a pointer to the first node)
	while (current != nullptr) { //Loop through the list
		Node* next = current->next; //Save the next node
		delete current; //Delete the current node
		current = next; //Move to the next node
	}
}

