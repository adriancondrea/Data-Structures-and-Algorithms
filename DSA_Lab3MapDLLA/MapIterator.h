#pragma once
#include "Map.h"
class MapIterator
{
	//DO NOT CHANGE THIS PART
	friend class Map;
private:
	Map& map;
	// representation - an index pointing to the current element
    int currentElementIndex{};
	explicit MapIterator(Map& m);
public:
	void first();
	void next();
	TElem getCurrent();
    TElem remove();
	bool valid() const;
};


