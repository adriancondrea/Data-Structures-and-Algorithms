#include "ShortTest.h"
#include <assert.h>
#include "Bag.h"
#include "BagIterator.h"
#include <iostream>
#include <exception>
void testAll() { 
	Bag b;
	assert(b.isEmpty());
	assert(b.size() == 0);

	//testing the new functionality
	for(int i=0; i< 10; i++)
	    b.add(100);
    assert(b.removeOccurrences(1, 5) == 0);     //removing an element that doesn't exist should return 0
    assert(b.removeOccurrences(3, 100) == 3);   //removing 3 occurences of 100
    assert(b.nrOccurrences(100) == 7);           //we should still have 7 occurences
    assert(b.removeOccurrences(15, 100) == 7);  //if we want to remove more occurences than it has, it removes all of them
    assert(b.isEmpty());                         //the bag should now be empty
    //if number of occurences is negative it should throw an exception
    try {
        b.removeOccurrences(-5, 99);
        assert (false);
    }
    catch (std::exception&) {
        assert (true);
    }
    for(int i=0; i<5; i++)
    {
        b.add(1);
        b.add(2);
        b.add(3);
    }
    //removing an element that isn't head
    assert(b.removeOccurrences(6, 2) == 5);
    assert(b.nrOccurrences(1) == 5);
    assert(b.nrOccurrences(3) == 5);
    assert(b.size() == 10);
    assert(b.nrOccurrences(2) == 0);
    b.removeOccurrences(5, 1);
    b.removeOccurrences(5, 3);
    assert(b.isEmpty());
    //done testing the new functionality

    b.add(5);
	b.add(1);
	b.add(10);
	b.add(7);
	b.add(1);
	b.add(11);
	b.add(-3);
	assert(b.size() == 7);
	assert(b.search(10) == true);
	assert(b.search(16) == false);
	assert(b.nrOccurrences(1) == 2);
	assert(b.nrOccurrences(7) == 1);
	assert(b.remove(1) == true);
	assert(b.remove(6) == false);
	assert(b.size() == 6);
	assert(b.nrOccurrences(1) == 1);
	BagIterator it = b.iterator();
	it.first();
	while (it.valid()) {
		TElem e = it.getCurrent();
		it.next();
	}
}
