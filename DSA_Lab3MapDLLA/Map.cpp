#include <iostream>
#include "Map.h"
#include "MapIterator.h"
// for complexities n - number of keys in the map

// complexity: tetha(n). Since n is initially 10, we can say tetha(1)
Map::Map() {
    // constructor
	this->capacity = ARRAY_INITIAL_CAPACITY;
    this->nodes = DynamicVector<Node>(this->capacity + 1);
    // we keep the head and tail of the list, as well as the index of the first empty node
    this->head = -1;
    this->tail = -1;
    this->indexFirstEmpty = 1;
    // set the corresponding links for keeping track of empty nodes. At the beginning all the nodes are empty and
    // the next field points to the next empty node
    for(int i = 1; i< this->capacity; i++)
        this->nodes[i].next = i + 1;
    this->nodes[this->capacity].next = -1;

}

/**
Map::~Map() {
	// no need for destructor i think? because it gets called automatically when the map goes out of scope, and
 that also calls the destructor for the dynamicArray that is defined.

}
**/

// complexity: O(n)
TValue Map::add(TKey c, TValue v){
	int indexOfKey = this->searchReturnIndex(c);
	// if the key already exists in the map, we update its value and return its old value
	if(indexOfKey != -1)
    {
	    auto oldValue = this->nodes[indexOfKey].element.second;
	    this->nodes[indexOfKey].element.second = v;
        return oldValue;
    }
	// allocate a new element at a given index
	int indexOfNewElement = this->allocate();
    //if we couldn't allocate a new element (array is full), then resize and allocate again
    if(indexOfNewElement == -1){
        this->resizeArray();
        indexOfNewElement = this->allocate();
    }
    // if we managed to allocate a new element
    if(indexOfNewElement != -1) {
        // create a TElem and store it in the newly allocated element
        TElem newElement;
        newElement.first = c;
        newElement.second = v;
        this->nodes[indexOfNewElement].element = newElement;
        // add the element at the end
        // set the links accordingly
        // if the list is empty, add the element at the end and that's it
        if (this->tail == -1) {
            this->tail = indexOfNewElement;
            this->nodes[indexOfNewElement].previous = -1;
            this->nodes[indexOfNewElement].next = -1;
        }
        // otherwise (element is not tail) set the links accordingly. the element gets added at the end
        else{
            this->nodes[this->tail].next = indexOfNewElement;
            this->nodes[indexOfNewElement].previous = this->tail;
            this->nodes[indexOfNewElement].next = -1;
            this->tail = indexOfNewElement;
        }
        // increase the size
        this->nodes.actualSize++;
    }
    // if the head is also -1, set the head to the new element
    if(this->head == -1)
        this->head = indexOfNewElement;
    return NULL_TVALUE;
}

// complexity: best case tetha(1), worst case tetha(n), overall O(n)
TValue Map::search(TKey c) const{
	int current = this->head;
	while(current != -1 && this->nodes[current].element.first != c)
	    current = this->nodes[current].next;
	if(current != -1)
	    return this->nodes[current].element.second;
	return NULL_TVALUE;
}

// complexity: O(n)
TValue Map::remove(TKey c){
	int indexOfKey = this->searchReturnIndex(c);
	// if we found the element
	if(indexOfKey != -1){
	    // if the element is both tail and head, we just make the list empty (head = tail = -1)
	    if(indexOfKey == this->head && indexOfKey == this->tail)
        {
	        this->head = -1;
	        this->tail = -1;
        }
	    // otherwise if it is only head, we set the head to be next element and remove the link.
	    else if(indexOfKey == this->head) {
            this->head = this->nodes[head].next;
            this->nodes[head].previous = -1;
        }
	    // if it is tail, we set the previous element to be tail and remove the link
	    else if(indexOfKey == this->tail){
	        this->tail = this->nodes[tail].previous;
	        this->nodes[tail].next = -1;
	    }
	    // othewise (the element is neither tail nor head), set the links accordingly.
	    else{
	        int previousNode = this->nodes[indexOfKey].previous;
	        int nextNode = this->nodes[indexOfKey].next;
	        this->nodes[previousNode].next = nextNode;
	        this->nodes[nextNode].previous = previousNode;
	    }
	    // save the old value to return it
	    auto oldValue = this->nodes[indexOfKey].element.second;
	    // free the node
	    this->free(indexOfKey);
	    // decrease the size
	    this->nodes.actualSize --;
	    // return the old value
        return  oldValue;
    }
	// if the list is empty after removing the element, we set the index of first empty and make the links between
	// empty nodes
	if(this->size() == 0)
    {
	    this->head = -1;
	    this->tail = -1;
	    this->indexFirstEmpty = 1;
        for(int i = 1; i< this->capacity; i++)
            this->nodes[i].next = i + 1;
        this->nodes[this->capacity].next = -1;
    }
	return NULL_TVALUE;
}


// compelxity: tetha(1)
int Map::size() const {
	return this->nodes.actualSize;
}

// complexity: tetha(1)
bool Map::isEmpty() const{
    return this->nodes.actualSize == 0;
}

// complexity: tetha(1)
MapIterator Map::iterator() {
	return MapIterator(*this);
}

// complexity: tetha(1)
int Map::allocate() {
    // we allocate the new node at the index of the first empty node
    int newElement = this->indexFirstEmpty;
    // if there is an empty node
    if(newElement != -1) {
        // we set the first empty node to the next one
        this->indexFirstEmpty = this->nodes[this->indexFirstEmpty].next;
        // if there is another empty node, we remove its previous link to our newly allocated node
        if(this->indexFirstEmpty != -1)
            this->nodes[this->indexFirstEmpty].previous = -1;
        // we remove the links of our newly allocated node
        this->nodes[newElement].next = -1;
        this->nodes[newElement].previous = -1;
    }
    // returns its index
    return  newElement;
}

// complexity: tetha(1)
void Map::free(int position) {
    this->nodes[position].next = this->indexFirstEmpty;
    this->nodes[position].previous = -1;
    if(this->indexFirstEmpty != -1)
        this->nodes[this->indexFirstEmpty].previous = position;
    this->indexFirstEmpty = position;
}

// complexity: O(n) - best: tetha(1), worst - tetha(n)
int Map::searchReturnIndex(TKey c) {
    int current = this->head;
    while(current != -1 && this->nodes[current].element.first != c)
        current = this->nodes[current].next;
    return current;
}

// complexity: O(n)
void Map::resizeArray() {
    // resize the array
    this->nodes.resize();
    // save the old capacity
    int oldCapacity = this->capacity;
    // update the capacity
    this->capacity *= 2;
    // initialize the links of the empty nodes
    for(int i = oldCapacity + 1; i < this->capacity; i++) {
        this->nodes[i].next = i + 1;
        this->nodes[i].previous = i - 1;
    }
    this->nodes[oldCapacity + 1].previous = -1;
    this->nodes[this->capacity - 1].next = -1;
    // first empty element will be the first newly allocated node
    this->indexFirstEmpty = oldCapacity + 1;
}





