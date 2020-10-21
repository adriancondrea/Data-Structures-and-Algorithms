#include "ShortTest.h"
#include <assert.h>
#include "Map.h"
#include "MapIterator.h"
#include <exception>

void testAll() { //call each function to see if it is implemented
	Map m;
	assert(m.isEmpty() == true);
	assert(m.size() == 0); //add elements
	assert(m.add(5,5)==NULL_TVALUE);
	assert(m.add(1,111)==NULL_TVALUE);
	assert(m.add(10,110)==NULL_TVALUE);
	assert(m.add(7,7)==NULL_TVALUE);
	assert(m.add(1,1)==111);
	assert(m.add(10,10)==110);
	assert(m.add(-3,-3)==NULL_TVALUE);
	assert(m.size() == 5);
	assert(m.search(10) == 10);
	assert(m.search(16) == NULL_TVALUE);
	assert(m.remove(1) == 1);
	assert(m.remove(6) == NULL_TVALUE);
	assert(m.size() == 4);


	TElem e;
	MapIterator id = m.iterator();
	id.first();
	int s1 = 0, s2 = 0;
	while (id.valid()) {
		e = id.getCurrent();
		s1 += e.first;
		s2 += e.second;
		id.next();
	}
	assert(s1 == 19);
	assert(s2 == 19);

	// new tests
    Map map2;
    map2.add(1, 999);
    map2.add(2, 47);
    map2.add(3, 3);
    map2.add(4,4);
    MapIterator iterator2 = map2.iterator();
    // test returning value of remove
    auto removedPair = iterator2.remove();
    assert(removedPair.first == 1 && removedPair.second == 999);
    // test the size
    assert(map2.size() == 3);
    // test the current value after remove
    auto currentElement = iterator2.getCurrent();
    assert(currentElement.first == 2 && currentElement.second == 47);

    // testing throwing an exception when trying to remove with an invalid iterator
    while(iterator2.valid())
        iterator2.next();
    try {
        iterator2.remove();
        assert(false);
    }
    catch(...) {
        assert(true);
    }

    // test removing last element -> iterator becomes invalid
    Map map3;
    map3.add(1, 1);
    MapIterator iterator3 = map3.iterator();
    iterator3.remove();
    assert(!iterator3.valid());
}


