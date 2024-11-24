#include <iostream>
#include "MultiMap.h"
#include "ExtendedTest.h"
#include "ShortTest.h"
#include "MultiMapIterator.h"
#include <assert.h>

using namespace std;

void testRemoveKey()
{
	MultiMap mm;
	vector<TValue> v;
	
	for (int j = 0; j < 10; j++)
		for (int i = 0; i < 10; i++)
			mm.add(j, i);

	for (int j = 0; j < 10; j++)
	{
		v = mm.removeKey(j);

		int fr[10] = { 0 };
		assert(v.size() == 10);
		for (int i = 0; i < 10; i++)
			fr[v[i]]++;
		for (int i = 0; i < 10; i++)
			assert(fr[i] == 1);
	}
	assert(mm.size() == 0);
	assert(mm.isEmpty());
	cout << "Test removeKey passed!" << endl;
}

int main() {

	testRemoveKey();
	testAll();
	testAllExtended();
	cout << "End" << endl;
	system("pause");

}
