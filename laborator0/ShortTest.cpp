#include "ShortTest.h"
#include <assert.h>
#include "FixedCapBiMap.h"
#include "FixedCapBiMapIterator.h"
#include <utility>


void testAll() { //call each function to see if it is implemented
	FixedCapBiMap m(10);
	assert(m.isEmpty() == true);
	assert(m.size() == 0); //add elements
	assert(m.add(5,5)==true);
	assert(m.add(1,111)==true);
	assert(m.add(10,110)==true);
	assert(m.add(7,7)==true);
	assert(m.add(1,1)==true); // this is the second value for key 1
	assert(m.add(1, 3) == false); // we cannot add a third value
	assert(m.add(10,10)==true);
	assert(m.add(-3,-3)==true);
	assert(m.size() == 7);
	std::pair<TValue, TValue> res = m.search(10);
	std::pair<TValue, TValue> ans1(110, 10);
	std::pair<TValue, TValue> ans2(10, 110);
	std::pair<TValue, TValue> ans3(NULL_TVALUE, NULL_TVALUE);
	assert(((res == ans1) || (res == ans2)));
	assert(m.search(16) == ans3);
	assert(m.remove(1,1) == true);
	assert(m.remove(6, 6) == false);
	assert(m.remove(5, 7) == false);
	assert(m.isEmpty() == false);
	assert(m.isFull() == false);
	assert(m.size() == 6);


	TElem e;
	FixedCapBiMapIterator id = m.iterator();
	id.first();
	int s1 = 0, s2 = 0;
	while (id.valid()) {
		e = id.getCurrent();
		s1 += e.first;
		s2 += e.second;
		id.next();
	}
	assert(s1 == 30);
	assert(s2 == 240);

}

void testRemoveKey() {
	FixedCapBiMap m(10);
	assert(m.add(5, 5) == true);
	assert(m.add(1, 111) == true);
	assert(m.add(1, 1) == true);
	assert(m.add(10, 110) == true);
	assert(m.add(7, 7) == true);

	std::pair<TValue, TValue> test1 = m.search(5);
	std::pair<TValue, TValue> test2 = m.search(1);
	std::pair<TValue, TValue> test3 = m.search(10);
	std::pair<TValue, TValue> test4 = m.search(7);


	assert(m.removeKey(5) == test1);
	assert(m.removeKey(1) == test2);
	assert(m.removeKey(10) == test3);
	assert(m.removeKey(7) == test4);

}

void testPrevious() {
	FixedCapBiMap m(100);
	FixedCapBiMapIterator it = m.iterator();
	for (int i = 0; i < 100; i++) {
		m.add(i, i);
	}
	for (int i = 0; i < 50; i++) {
		it.next();
	}

	for (int i = 49; i >= 0; i--) {
		it.previous();
		TElem el = it.getCurrent();
		assert(el.first == i);
	}

	try {
		it.previous();
		assert(false);
	}
	catch (exception&) {
		assert(true);
	}
}