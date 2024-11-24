#include "FixedCapBiMap.h"
#include "FixedCapBiMapIterator.h"
#include <exception>
using namespace std;


FixedCapBiMapIterator::FixedCapBiMapIterator(const FixedCapBiMap& d) : map(d) // BC = WC = TC = Theta(1)
{
	//the iterator contains a position
	this->currentPosition = 0;
}


void FixedCapBiMapIterator::first() { // BC = WC = TC = Theta(1)
	this->currentPosition = 0;
}

void FixedCapBiMapIterator::next() { // BC = WC = TC = Theta(1)
	if (this->currentPosition == this->map.mapSize) {
		throw exception();
	}
	this->currentPosition++;
}

TElem FixedCapBiMapIterator::getCurrent(){ // BC = WC = TC = Theta(1)
	if (this->currentPosition == this->map.mapSize) {
		throw exception();
	}
	return this->map.elements[this->currentPosition];
}

bool FixedCapBiMapIterator::valid() const { // BC = WC = TC = Theta(1)
	return this->currentPosition <  this->map.mapSize;
}

void FixedCapBiMapIterator::previous() {
	if (this->currentPosition == 0) {
		this->currentPosition = this->map.mapSize;
	}
	else {
		this->currentPosition--;
	}
	if (!valid()) {
		throw exception();
	}
}