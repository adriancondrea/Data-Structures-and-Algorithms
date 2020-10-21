#include "MultiMapIterator.h"
#include "MultiMap.h"

// complexity: O(capacity)
MultiMapIterator::MultiMapIterator(MultiMap& c): col(c) {
	//TODO - Implementation
	this->first();
}

// complexity: tetha(1)
// if the iterator is not valid, throws an exception
TElem MultiMapIterator::getCurrent() const{
    if(!this->valid())
        throw std::exception();
	return this->col.elements[this->index];
}

// complexity: tetha(1)
bool MultiMapIterator::valid() const {
	return this->index < this->col.capacity;
}

//complexity: O(capacity)
//if the iterator is not valid, throws an exception
void MultiMapIterator::next() {
    if(!this->valid())
        throw std::exception();
    this->index++;
    while(this->valid() && this->getCurrent() <= NULL_TELEM)
        this->index++;
}

// sets the iterator to point to the first non-empty element in the hash table
// if the hash table is empty, the iterator becomes invalid
//best case: tetha(1)
//worst case: tetha(capacity)
// avg case: O(capacity)
void MultiMapIterator::first() {
	this->index = 0;
    while(this->valid() && this->getCurrent() <= NULL_TELEM)
        this->index++;
}

// Complexity: tetha(1)
//removes and returns the current pair from the iterator
//after the operation the current pair from the Iterator is the next element from the MultiMap, or, if the removed element was the last one, the iterator is invalid
//throws exception if the iterator is invalid
TElem MultiMapIterator::remove() {
    if(!this->valid())
        throw std::exception();
    // save the pair to be removed
    auto removedPair = this->col.elements[index];
    // set the element at the index to a deleted element
    this->col.elements[index] = DELETED_TELEM;
    // decrease the actual size
    this->col.actualSize--;
    // move the iterator to the next element
    this->next();
    // return the removed pair
    return removedPair;
}

