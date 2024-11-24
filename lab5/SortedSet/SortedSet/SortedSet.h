#pragma once
//DO NOT INCLUDE SETITERATOR

//DO NOT CHANGE THIS PART
typedef int TElem;
typedef TElem TComp;
typedef bool(*Relation)(TComp, TComp);
#define NULL_TELEM -11111
class SortedSetIterator;


class SortedSet {
	friend class SortedSetIterator;
private:
	// ADT Sorted Set - using BST with linked representation with dynamic allocation
	// BST - Binary Search Tree
	struct Node { // struct for a node in the BST
		TComp data; // data of the node
		Node* left; // pointer to the left child
		Node* right; // pointer to the right child
		Node(TComp data) : data{ data }, left{ nullptr }, right{ nullptr } {} // constructor for a node
	};

	Node* root; // pointer to the root of the BST
	int num_elements; // number of elements in the BST
	Relation relation; // relation used for mentaining a order in the BST

public:
	//constructor
	SortedSet(Relation r);

	//return the difference between the maximum and the minimum element in the sorted set
	//if the SortedSet is empty the range is -1
	int getRange() const;

	//adds an element to the sorted set
	//if the element was added, the operation returns true, otherwise (if the element was already in the set) 
	//it returns false
	bool add(TComp e);

	
	//removes an element from the sorted set
	//if the element was removed, it returns true, otherwise false
	bool remove(TComp e);

	//checks if an element is in the sorted set
	bool search(TElem elem) const;

	//returns the number of elements from the sorted set
	int size() const;

	//checks if the sorted set is empty
	bool isEmpty() const;

	//returns an iterator for the sorted set
	SortedSetIterator iterator() const;

	// destructor
	~SortedSet();


};
