#pragma once
//DO NOt INCLUDE LISTITERATOR

//DO NOT CHANGE THIS PART
class ListIterator;
typedef int TComp;
typedef bool (*Relation)(TComp, TComp);
typedef bool(*Condition)(TComp);
#define NULL_TCOMP -11111

//We use this structure to store the elements of the list
struct Node {
	TComp data; // The data stored in the node(the element of the list)
	Node* next; // Pointer to the next node in the list
	Node(TComp val) : data(val), next(nullptr) {} // Constructor for the Node structure
};

class SortedIteratedList {
private:
	friend class ListIterator;
private:
	Node* head; // Pointer to the first node in the list
	Relation relation; // The relation used to compare the elements of the list
	int numeberOfElements; // The number of elements in the list

public:
	// constructor
	SortedIteratedList(Relation r);

	void filter(Condition c);

	// returns the number of elements from the list
	int size() const;

	// verifies if the list is empty
	bool isEmpty() const;

	// returns the first position from the list
	ListIterator first() const;

	// returns the element from the given position
	//throws an exception if the position is not valid
	TComp getElement(ListIterator pos) const;

	// adds a new element to the list
	void add(TComp e);

	// removes the element from position pos
	//returns the removed element
	//after removal pos is positioned on the next element (the one after the removed one) or it is invalid if the last element was removed
	//throws an exception if the position is not valid
	TComp remove(ListIterator& poz);

	// searches for the first occurrence of an element 
	//returns an iterator that points to the element, if it appear in the list, or an invalid iterator if the element is not in the list
	ListIterator search(TComp e) const;

	//TODO elimina
	//void print();

	//destructor
	~SortedIteratedList();

};
