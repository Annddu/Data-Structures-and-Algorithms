#pragma once
//DO NOT INCLUDE BAGITERATOR


//DO NOT CHANGE THIS PART
#define NULL_TELEM -111111;
typedef int TElem;
typedef bool (*Condition)(TElem);
class BagIterator; 

// Structure of a node in the linked list
// We use this sturcture to alocate the elements in the bag dynamically
struct Node {
	TElem element; // The element stored in the node
	int frequency; // The frequency of the element
	Node* next; // The next node in the linked list which is a pointer to a Node

	// Constructor for the Node
	// The default frequency is 1
	// The default next is nullptr
	Node(TElem elem, int f = 1, Node* n = nullptr) : element(elem), frequency(f), next(n) {}
};

class Bag {

private:
	//TODO - Representation
	// The head of the linked list, the first node
	Node* head;

	// The number of elements in the bag
	int numberOfElements;

	//DO NOT CHANGE THIS PART
	friend class BagIterator;
public:
	//constructor
	Bag();

	//adds an element to the bag
	void add(TElem e);

	//removes one occurence of an element from a bag
	//returns true if an element was removed, false otherwise (if e was not part of the bag)
	bool remove(TElem e);

	//checks if an element appearch is the bag
	bool search(TElem e) const;

	//returns the number of occurrences for an element in the bag
	int nrOccurrences(TElem e) const;

	//returns the number of elements from the bag
	int size() const;

	//returns an iterator for this bag
	BagIterator iterator() const;

	//checks if the bag is empty
	bool isEmpty() const;

	void filter(Condition cond);

	//destructor
	~Bag();
};