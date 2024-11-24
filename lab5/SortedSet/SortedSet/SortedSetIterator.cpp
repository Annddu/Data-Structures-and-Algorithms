#include "SortedSetIterator.h"
#include <exception>

using namespace std;

// BC = WC = TC = Theta(1)
SortedSetIterator::SortedSetIterator(const SortedSet& multime) : multime(multime) {
	this->current = 0; // Start from the first element
	this->values = new TComp[multime.size()]; // Allocate memory for the elements
	this->inOrder(multime.root); // Parse the tree in order
	this->current = 0; // Start from the first element
}

// BC = WC = TC = Theta(1)
SortedSetIterator::~SortedSetIterator() {
	delete[] this->values;
}

// BC = WC = TC = Theta(1)
void SortedSetIterator::first() {
	this->current = 0;
}

// BC = WC = TC = Theta(1)
void SortedSetIterator::next() {
	if (!this->valid()) {
		throw exception();
	}
	this->current++;
}

// BC = WC = TC = Theta(1)
TElem SortedSetIterator::getCurrent()
{
	if (!this->valid()) {
		throw exception();
	}

	return this->values[this->current];
}

// BC = WC = TC = Theta(1)
bool SortedSetIterator::valid() const {
	return this->current < this->multime.size();
}

// BC = O(number of elements) when the tree is balanced
// WC = O(number of elements) when the tree is unbalanced
// TC = O(number of elements) 
void SortedSetIterator::inOrder(SortedSet::Node* node) {
	SortedSet::Node* current = node; // Start from the root
	while (current != nullptr) { // Parse the tree in order
		if (current->left == nullptr) { // If the left child is null, then the current node is the leftmost node
			this->values[this->current++] = current->data; // Add the current node to the array
			current = current->right; // Move to the right child
        }
		else { // If the left child is not null, then the current node has a left subtree
			SortedSet::Node* predecessor = current->left; // Find the inorder predecessor of the current node
			while (predecessor->right != nullptr && predecessor->right != current) { // Find the rightmost node of the left subtree
				predecessor = predecessor->right; // Move to the right child
            }

			if (predecessor->right == nullptr) { // If the right child of the inorder predecessor is null, then the current node is not yet visited
				predecessor->right = current; // Make the current node the right child of the inorder predecessor
				current = current->left; // Move to the left child
            }
            else { // Revert the changes made in the if part to restore the original tree
				predecessor->right = nullptr; // Make the right child of the inorder predecessor null
				this->values[this->current++] = current->data; // Add the current node to the array
				current = current->right; // Move to the right child
            }
        }
    }
	delete current; // Delete the current node
}