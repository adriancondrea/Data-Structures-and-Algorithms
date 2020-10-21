#pragma once
#include <utility>
#include "dynamicVector.h"

typedef int TKey;
typedef int TValue;
typedef std::pair<TKey, TValue> TElem;
#define NULL_TVALUE -11111
#define NULL_TELEM pair<TKey, TValue>(-11111, -11111)
class MapIterator;


class Map {
	friend class MapIterator;
	private:
        // representation
        struct Node
        {
            TElem element;
            int previous;
            int next;
        };
		DynamicVector<Node> nodes;
		int capacity;
		int head, tail, indexFirstEmpty;
	public:
	// implicit constructor
	Map();

	// adds a pair (key,value) to the map
	//if the key already exists in the map, then the value associated to the key is replaced by the new value and the old value is returned
	//if the key does not exist, a new pair is added and the value null is returned
	TValue add(TKey c, TValue v);

	//searches for the key and returns the value associated with the key if the map contains the key or null: NULL_TVALUE otherwise
	TValue search(TKey c) const;

	//removes a key from the map and returns the value associated with the key if the key existed ot null: NULL_TVALUE otherwise
	TValue remove(TKey c);

	//returns the number of pairs (key,value) from the map
	int size() const;

	//checks whether the map is empty or not
	bool isEmpty() const;

	//returns an iterator for the map
	MapIterator iterator();

	// destructor
	// ~Map();

	// a new element will be allocated and its position returned. If it can not allocate an element, returns -1
	int allocate();

	// frees the element at given position
	void free(int position);

	// searches for the key and returns the index at which node with given key exists. returns -1 if no such node exists
	int searchReturnIndex(TKey c);


	// resizes the array, doubling its capacity
	void resizeArray();
};



