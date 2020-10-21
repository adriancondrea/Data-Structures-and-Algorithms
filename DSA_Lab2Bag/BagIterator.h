#include "Bag.h"

class BagIterator
{
	//DO NOT CHANGE THIS PART
	friend class Bag;
	
private:
	const Bag& bag;
	// we keep a pointer to the node storing the current element and an integer representing the frequency of elem
	Bag::Node *currentElement;
	int currentFrequency;
	// constructor, initializes the bag and sets the iterator to the first element.
	BagIterator(const Bag& c);
public:
    // sets the iterator to the first element
	void first();
    // moves the iterator to the next element. Throws an exception if the iterator is not valid
	void next();
	// returns the current element. Throws an exception if the iterator is not valid
	TElem getCurrent() const;
	bool valid() const;
};
