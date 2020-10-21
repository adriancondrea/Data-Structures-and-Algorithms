#include <exception>
#include "BagIterator.h"
#include "Bag.h"

using namespace std;

//complexity: tetha(1)
BagIterator::BagIterator(const Bag& c): bag(c)
{
    this->first();
}

//complexity: tetha(1)
void BagIterator::first() {
    // sets currentElement to the head of the list, and if the list is not empty, sets the currentFrequency to the
    // frequency of the first element
    this->currentElement = this->bag.head;
    if(this->currentElement != nullptr)
        this->currentFrequency = this->bag.head->frequency;
}

//complexity: tetha(1)
void BagIterator::next() {
	//if the iterator is not valid, throw an exception
	if(!this->valid())
	    throw exception();
	// if the current element appears only once, next needs to move to the next element
	if(this->currentFrequency == 1)
    {
	    this->currentElement = this->currentElement->next;
	    // update currentFrequency if the list hasn't ended
	    if(this->currentElement != nullptr)
	        this->currentFrequency = this->currentElement->frequency;
    } else{
	    this->currentFrequency--;       // if the element appears more than once, next just decreases its frequency.
	}
}

//complexity: tetha(1)
bool BagIterator::valid() const {
    // checks if currentElement is a valid pointer in the bag
	return this->currentElement != nullptr;
}


//complexity: tetha(1)
TElem BagIterator::getCurrent() const
{
	// throw an exception if the iterator is not valid
	if(!this->valid())
	    throw exception();
	// otherwise return the value of the current element
	return this->currentElement->value;
}
