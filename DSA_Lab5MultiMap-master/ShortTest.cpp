#include "ShortTest.h"
#include "MultiMap.h"
#include "MultiMapIterator.h"
#include <assert.h>
#include <vector>
#include <exception>
#include<iostream>

void testAll() {
	MultiMap m;
	m.add(1, 100);
	m.add(2, 200);
	m.add(3, 300);
	m.add(1, 500);
	m.add(2, 600);
	m.add(4, 800);

	assert(m.size() == 6);

	assert(m.remove(5, 600) == false);
	assert(m.remove(1, 500) == true);

	assert(m.size() == 5);

    vector<TValue> v;
	v=m.search(6);
	assert(v.size()==0);

	v=m.search(1);
	assert(v.size()==1);

	assert(m.isEmpty() == false);

	MultiMapIterator im = m.iterator();
	assert(im.valid() == true);
	while (im.valid()) {
		im.getCurrent();
		im.next();
	}
	assert(im.valid() == false);
	im.first();
	assert(im.valid() == true);

	//testing the new functionality
	MultiMap m2;
	MultiMapIterator m2i = m2.iterator();

	//trying to remove the current pair from an empty table should throw an exception
    try {
        m2i.remove();
        assert(false);
    }
    catch(exception) {
        assert(true);
    }

    m2.add(1, 1);
    m2.add(1, 2);
    m2.add(1, 3);
    m2.add(1, 4);
    m2i.first();
    while(m2i.valid())
    {
        cout<<m2i.getCurrent().first<<" "<<m2i.getCurrent().second<<endl;
        try{
            m2i.next();
        }
        catch(std::exception)
        {

        }
    }
    m2i.first();
    auto removedPair = m2i.remove();   //delete the first element
    assert(m2.size() == 3); //check the element was deleted and the size updated
    assert(removedPair == TElem(1, 3));
    m2i.first();
    m2i.next();
    m2i.next();
    // we are now to the last element, we remove it and the iterator must become invalid
    m2i.remove();
    assert(!m2i.valid());
    m2i.first();
}
