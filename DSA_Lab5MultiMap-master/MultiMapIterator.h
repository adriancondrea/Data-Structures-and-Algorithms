#pragma once
#include "MultiMap.h"

class MultiMap;

class MultiMapIterator
{
	friend class MultiMap;

private:
	MultiMap& col;
	// our iterator is an idex in the array of elements
    int index;
	MultiMapIterator(MultiMap& c);

public:
	TElem getCurrent()const;
	bool valid() const;
	void next();
	void first();
	TElem remove();
};

