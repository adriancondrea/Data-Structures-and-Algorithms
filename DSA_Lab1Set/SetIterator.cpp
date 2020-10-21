#include "SetIterator.h"
#include "Set.h"

SetIterator::SetIterator(const Set& m) : set(m)
{
	// we call first to find the first element in the array
	first();
}

// minimum complexity: tetha(1) - the first element of the set is true
// maximum complexity: tetha(arraySize) - there are no true values in the array or the true value is towards the end of the array
void SetIterator::first() {
	// after exectuing first(), index will point to the first true value from array
	index = 0;
	while (valid() && set.array[index] == false)
		index++;
}

// minimum complexity tetha(1), maximum complexity tetha(arraySize)
void SetIterator::next() {
	index++;
	while (valid())
	{
		// if we find an element in the set whose value is true, we stop the loop
		if (set.array[index] == true)
			break;
		index++;
	}
}

// complexity: O(arraySize)
void SetIterator::previous()
{
	index--;		// if index was 0, it will now be invalid and the loop won't start, we throw an exception at the end
	while (valid())
	{
		if (set.array[index] == true)
			break;
		index--;
	}
	if (!valid())
		throw 1;
}

// complexity: tetha(1)
TElem SetIterator::getCurrent()
{
	return index + set.minimumElement;
}

// complexity: tetha(1)
bool SetIterator::valid() const {
	return 0 <= index && index < set.arraySize;
}



