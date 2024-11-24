#include "SortedSet.h"
#include "SortedSetIterator.h"

// BC = WC = TC = Theta(1)
SortedSet::SortedSet(Relation r) {
	this->root = nullptr; // Empty tree, first node is the root
	this->num_elements = 0; // No elements in the tree
	this->relation = r; // Set the relation
}

// BC = Theta(height) and the height is log2(n)
// WC = Theta(height) and the height in n
// TC = O(height)
// height between log2(n) and n
int SortedSet::getRange()  const {
	if (root == nullptr) { // Tree is empty
		return -1; // Return -1
	}

	Node* current = root; // Start from the root

	// Find the minimum element in the tree
	while (current->left != nullptr) { // Traverse the left subtree
		current = current->left; // Move to the left child
	}
	int min = current->data; // Minimum element

	current = root; // Start from the root

	// Find the maximum element in the tree
	while (current->right != nullptr) { // Traverse the right subtree
		current = current->right; // Move to the right child
	}
	int max = current->data; // Maximum element

	return max - min; // Return the difference between the maximum and the minimum element
}

// BC = Theta(1) child of root
// WC = Theta(height) and the height is n
// TC = O(height)
// height between log2(n) and n
bool SortedSet::add(TComp elem) {
	Node* newNode = new Node(elem); // node to be added

	if (root == nullptr) { // Tree is empty
		root = newNode; // Add the node as the root
		num_elements++; // Increment the number of elements
		return true; // Element added
    }

	Node* current = root; // Start from the root
	Node* parent = nullptr; // Parent of the current node


	// Find the parent of the node to be added
	while (current != nullptr) { // Traverse the tree
		parent = current; // Update the parent
		if (elem == current->data) { // If the element already exists
			delete newNode; // Clear the memory
			return false; // Element not added
        }
		else if (relation(elem, current->data)) { // Verify if the relation is true for parsing the left child
			current = current->left; // Move to the left child
        }
		else { // If not, parse the right child
			current = current->right; // Move to the right child
        }
    }

	// Add the node to the tree
	if (relation(elem, parent->data)) {  // If the relation is true for the left child
		parent->left = newNode; // Add the node as the left child
    }
	else { // If not, add the node as the right child
		parent->right = newNode; // Add the node as the right child
    }
	delete current; // Clear the memory

	num_elements++; // Increment the number of elements
	return true; // Element added
}

// BC: Theta(1) when the element is the root
// WC: Theta(height) when the element is a leaf
// TC: O(height)
// height between log2(n) and n
bool SortedSet::remove(TComp elem) {
	if (root == nullptr) { // Tree is empty
		return false; // Element not found
    }

	Node* current = root; // Start from the root
	Node* parent = nullptr; // Parent of the current node
	bool found = false; // Element not found

	// Find the node to be deleted
	while (current != nullptr && !found) { // Traverse the tree
		if (current->data == elem) { // Element found
			found = true; // Element found
        }
        else {
			parent = current; // Update the parent
			if (relation(elem, current->data)) { // Verify if the relation is true for parsing the left child
				current = current->left; // Move to the left child
            }
			else { // If not, parse the right child
				current = current->right; // Move to the right child
            }
        }
    }

	if (!found) { // Element not found
        return false;
    }

	if (current->left == nullptr || current->right == nullptr) { // Node with one child or no child
		Node* temp = nullptr; // Temporary node
        if (current->left == nullptr) { // If the left child is null
			temp = current->right; // Get the right child
        }
		else { // If the right child is null
			temp = current->left; // Get the left child
        }

        if (parent == nullptr) { // If the node to be deleted is the root node
			root = temp; // Update the root
        }
		else if (relation(elem, parent->data)) { // If the relation is true for the left child
			parent->left = temp; // Update the left child
        }
		else { // If the relation is true for the right child
			parent->right = temp; // Update the right child
        }
    }
	else { // Node with two children
		Node* successorParent = current; // Parent of the successor
		Node* successor = current->right; // Successor 

		// Find the maximum element in the left subtree
		while (successor->left != nullptr) { // If the left child of the successor is not null
			successorParent = successor; // Update the parent of the successor
			successor = successor->left; // Move to the left child
        }

		// Move it to the node to be deleted
		current->data = successor->data; // Update the data of the current node

        // Fix successor's parent's child, delete the maximum
		if (successorParent != current) { // If the parent of the successor is not the current node
			successorParent->left = successor->right; // Update the left child of the parent of the successor
        }
		else { // If the parent of the successor is the current node
			successorParent->right = successor->right; // Update the right child of the parent of the successor
        }

        current = successor; // Current now points to successor which will be deleted
    }

	delete current; // Clear the memory
	num_elements--; // Decrement the number of elements
	return true; // Element removed
}


// BC = Theta(1) when the element is the root
// WC = Theta(height) when the element is a leaf
// TC = O(height)
// height between log2(n) and n
bool SortedSet::search(TComp elem) const {
	Node* current = root; // Start from the root

	while (current != nullptr) { // Traverse the tree
		if (current->data == elem) { // If the element is found
            return true; // Element found
        }
		else if (relation(elem, current->data)) { // Verify if the relation is true for parsing the left child
			current = current->left; // Move to the left child
        }
		else { // If not, parse the right child
			current = current->right; // Move to the right child
        }
    }
	//delete current; // Clear the memory
    return false; // Element not found
}

// BC = WC = TC = Theta(1)
int SortedSet::size() const {
	return num_elements;
}

// BC = WC = TC = Theta(1)
bool SortedSet::isEmpty() const {
	return num_elements == 0;
}

// BC = WC = TC = Theta(1)
SortedSetIterator SortedSet::iterator() const {
	return SortedSetIterator(*this);
}

// BC = Theta(num_elements)
// WC = Theta(num_elements)
// TC = O(num_elements)
SortedSet::~SortedSet() {
	Node** stack = new Node * [num_elements]; // Stack for the inorder traversal
	int top = -1; // Top of the stack
	Node* current = root; // Start from the root

	while (current != nullptr || top != -1) { // Traverse the tree
		while (current != nullptr) { // Traverse the left subtree
			stack[++top] = current; // Push the current node to the stack
			current = current->left; // Move to the left child
        }

		current = stack[top--]; // Pop the node from the stack
		Node* temp = current; // Temporary node
		current = current->right; // Move to the right child
		delete temp; // Clear the memory
    }
	delete[] stack; // Clear the memory
}