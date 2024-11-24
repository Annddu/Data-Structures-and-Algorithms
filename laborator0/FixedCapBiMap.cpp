#include "FixedCapBiMap.h"
#include "FixedCapBiMapIterator.h"

FixedCapBiMap::FixedCapBiMap(int capacity) { // BC: Theta(1), WC: Theta(1), TC: Theta(1)
	// the role of the constructor is to initialize your atributes
	if (capacity <= 0) {
		throw exception();
	}
	this->capacity = capacity;
	this->mapSize = 0;
	this->elements = new TElem[this->capacity]; //new means dynamic allocation, we are asking to use memory, we have to manually free it in the destructor
}

FixedCapBiMap::~FixedCapBiMap() { // BC = WC = TC = Theta(1)
	//destructor!
	delete[] this->elements;
}

bool FixedCapBiMap::add(TKey c, TValue v){ // BC: Theta(1) - when the first two keys from the map are equal to c
										   // WC: Theta(mapSize) - when the key c appears only once or zero times in the map 
										   // TC: O(mapSize) - 
	//check for space
	if (this->mapSize == this->capacity) {
		throw exception();
	}
	//count how many times we find this key in the map
	//if we find 2 it makes no sense to continue, so we use a while loop beacuse we can stop
	int count = 0;
	int index = 0;
	while (count < 2 && index < this->mapSize) {
		if (this->elements[index].first == c) {
			count++;
		}
		index++;
	}
	if (count == 2) {
		return false;
	}
	this->elements[this->mapSize].first = c;
	this->elements[this->mapSize].second = v;
	this->mapSize++;
	return true;
}

ValuePair FixedCapBiMap::removeKey(TKey k) {
	// BC: Theta(1) - when the first two keys from the are equal to k
	// WC: Theta(mapSize) - when the key k appears only once or zero times in the map
	// TC: O(mapSize)
	ValuePair result;
	result.first = NULL_TVALUE;
	result.second = NULL_TVALUE;
	int nrfound = 0;
	int index = 0;
	while (nrfound < 2 && index < this->mapSize) {
		if (this->elements[index].first == k) {
			if (nrfound == 0) {
				result.first = this->elements[index].second;
				nrfound++;
				this->elements[index] = this->elements[this->mapSize - 1];
				this->mapSize--;
			}
			else {
				result.second = this->elements[index].second;
				nrfound++;
				this->elements[index] = this->elements[this->mapSize - 1];
				this->mapSize--;
			}
		}
		index++;
	}
	return result;
}

ValuePair FixedCapBiMap::search(TKey c) const{ // BC: Theta(1) - when the first two keys from the are equal to c
										       // WC: Theta(mapSize) - when the key c appears only  once or zero times in the map
											   // TC: O(mapSize)
	ValuePair result;
	result.first = NULL_TVALUE;
	result.second = NULL_TVALUE;
	int nrfound = 0;
	int index = 0;
	while (nrfound < 2 && index < this->mapSize) {
		if (this->elements[index].first == c) {
			if (nrfound == 0) {
				result.first = this->elements[index].second;
				nrfound++;
			}
			else {
				result.second = this->elements[index].second;
				nrfound++;
			}
		}
		index++;
	}
	return result;
}

bool FixedCapBiMap::remove(TKey c, TValue v){ // WC: Theta(1) - whe the pair we want to remove is on the first position
											  // WC: Theta(mapSize) - when the pair is not in the array or it is in the last positon
											  // TC: O(n)
	//put the last element in the position of the removed element and decrease the mapSize, we can do that because the order does not matter
	int index = 0;
	while (index < this->mapSize) {
		if (this->elements[index].first == c && this->elements[index].second == v) {
			this->elements[index] = this->elements[this->mapSize - 1];
			this->mapSize--;
			return true;
		}
		index++;
	}
	return false;
}


int FixedCapBiMap::size() const { // BC = WC = TC = Theta(1)
	return this->mapSize;
}

bool FixedCapBiMap::isEmpty() const{ // BC = WC = TC = Theta(1)
	return this->mapSize == 0;
}

bool FixedCapBiMap::isFull() const { // BC = WC = TC = Theta(1)
	return this->mapSize == this->capacity;
}

FixedCapBiMapIterator FixedCapBiMap::iterator() const { // BC = WC = TC = Theta(1)
	return FixedCapBiMapIterator(*this);
}



