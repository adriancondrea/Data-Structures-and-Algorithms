#include "Map.h"
#include "MapIterator.h"
#include <exception>
using namespace std;


// complexity: tetha(1)
MapIterator::MapIterator(Map& d) : map(d)
{
    // call first function
	this->first();
}

// complexity: tetha(1)
void MapIterator::first() {
	// set the currentElementIndex to the head of the map
	this->currentElementIndex = this->map.head;
}

// complexity: tetha(1)
void MapIterator::next() {
    // if the index is not valid, throw an exception
	if(!this->valid())
	    throw std::exception();
	// otherwise move to the next element
	this->currentElementIndex = this->map.nodes[this->currentElementIndex].next;
}

// complexity: tetha(1)
TElem MapIterator::getCurrent(){
	// return the current element
	// if the index is not valid, throw an exception
	if(!this->valid())
	    throw std::exception();
	// return the current element
    return this->map.nodes[this->currentElementIndex].element;
}

// complexity: tetha(1)
bool MapIterator::valid() const {
	// checks if the currentElementIndex points to a valid element
    return this->currentElementIndex !=  -1;
}

//removes and returns the current pair from the iterator
//after the operation the current pair from the Iterator is the next element from the Map, or, if the removed element
//was the last one, the iterator is invalid
//throws exception if the iterator is invalid
// complexity: tetha(1)
TElem MapIterator::remove() {
    if(!this->valid())
        throw std::exception();
    // save the element to be removed
    auto elementToBeRemoved = this->getCurrent();
    // save the key of the element to be removed
    auto indexOfKey = elementToBeRemoved.first;
    // move to the next element
    this->next();
    // remove the element
    // if the element is both tail and head, we just make the list empty (head = tail = -1)
    if(indexOfKey == this->map.head && indexOfKey == this->map.tail)
    {
        this->map.head = -1;
        this->map.tail = -1;
    }
        // otherwise if it is only head, we set the head to be next element and remove the link.
    else if(indexOfKey == this->map.head) {
        this->map.head = this->map.nodes[this->map.head].next;
        this->map.nodes[this->map.head].previous = -1;
    }
        // if it is tail, we set the previous element to be tail and remove the link
    else if(indexOfKey == this->map.tail){
        this->map.tail = this->map.nodes[this->map.tail].previous;
        this->map.nodes[this->map.tail].next = -1;
    }
        // othewise (the element is neither tail nor head), set the links accordingly.
    else{
        int previousNode = this->map.nodes[indexOfKey].previous;
        int nextNode = this->map.nodes[indexOfKey].next;
        this->map.nodes[previousNode].next = nextNode;
        this->map.nodes[nextNode].previous = previousNode;
    }
    // free the element removed
    this->map.free(indexOfKey);
    // decrease the size
    this->map.nodes.actualSize --;
    // this->map.remove(elementToBeRemoved.first); - we can use this but is O(n) complexity because of the search
    return elementToBeRemoved;
}



