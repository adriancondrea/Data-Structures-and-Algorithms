#include "Set.h"
#include "SetITerator.h"

// Complexity: tetha(1)
Set::Set() {
	array = nullptr;
	arraySize = 0;
	arrayActualSize = 0;
	minimumElement = 0;
}

// Complexity: tetha(1) if the element fits the array
// tetha(newArraySize) otherwise
// amortized complexity is tetha(1)
bool Set::add(TElem elem) {
	// if the array does not exist, we create it, add the element then return true
	if (arraySize < 1)
	{
		arraySize = 1;
		arrayActualSize = 1;
		minimumElement = elem;		// if there is only one element, it is surely the minimum one
		array = new bool[arraySize];
		array[0] = true;
		return true;
	}
	/*case 1: the element we want to add fits the current array*/
	if (elem >= minimumElement && elem < minimumElement + arraySize)
	{
		// if the element is already in the array, we return false, meaning it was not added
		if (array[elem - minimumElement] == true)
			return false;
		// otherwise we add it to the array
		else
			array[elem - minimumElement] = true;
	}
	/* case 2: the element we want to add is smaller than the minimum element*/
	else if (elem < minimumElement)
	{
		int newArraySize, shiftingSize, i;
		//shiftingSize - how many spaces to the right will the old array be translated
		shiftingSize = minimumElement - elem;
		//the new size for the array
		newArraySize = arraySize + shiftingSize;
		//allocate space for a new array
		bool* auxiliaryArray = new bool[newArraySize];
		//add the element
		auxiliaryArray[0] = true;
		// clear the elements before the previous minimum and the current minimum
		for (i = 1; i < shiftingSize; i++)
			auxiliaryArray[i] = false;
		// copy the old array's elements onto the new one, shifted shiftingSize positions to the right
		for (i = 0; i < arraySize; i++)
			auxiliaryArray[i + shiftingSize] = array[i];
		// delete the old array
		delete[] array;

		//update the parameters of the array
		array = auxiliaryArray;
		arraySize = newArraySize;
		minimumElement = elem;
	}
	/* case 3: the element we want to add does not fit the current array but is not smaller than the minimum element (no need to do shifting)*/
	else
	{
		int maximumElement, newArraySize, i;
		maximumElement = minimumElement + arraySize - 1;
		newArraySize = arraySize + (elem - maximumElement);		//compute the size needed to store the new maximum value
		bool* auxiliaryArray = new bool[newArraySize];
		// copy the old array
		for (i = 0; i < arraySize; i++)
			auxiliaryArray[i] = array[i];
		for (i = arraySize; i < newArraySize - 1; i++)
			auxiliaryArray[i] = false;
		// add elem
		auxiliaryArray[newArraySize - 1] = true;

		//delete the old array
		delete[] array;

		// update the pointer to the array and the size
		array = auxiliaryArray;
		arraySize = newArraySize;
	}
	// increase the actual size of the array
	arrayActualSize += 1;
	return true;
}

// complexity: tetha(1) if the array can not be represented on an array half the size after removing the element or the element does not exist
// tetha(arraySize / 2) otherwise, and the dimension of the array halves
bool Set::remove(TElem elem) {
	if(search(elem) == false)
		return false;
	//delete the element from the array and update the actual size
	array[elem - minimumElement] = false;
	arrayActualSize -= 1;

	// if the element removed was the minimum element
	if (elem == minimumElement)
	{
		int indexFirstElement;
		//the new index of the first element (first true value from the array)
		indexFirstElement = 0;
		while (indexFirstElement < arraySize && array[indexFirstElement] == false)
			indexFirstElement++;

		//if the first half of the array is empty, we resize it, reducing its size to half
		if (indexFirstElement >= arraySize / 2)
		{
			int newArraySize, index, newMinimumElement;
			bool* auxiliaryArray;
			newMinimumElement = minimumElement + indexFirstElement;
			newArraySize = arraySize - indexFirstElement;
			auxiliaryArray = new bool[newArraySize];
			//copy the old array into the new one
			for (index = indexFirstElement; index < arraySize; index++)
				auxiliaryArray[index - indexFirstElement] = array[index];
			//delete the new array
			delete[] array;
			
			//update the parameters of the array
			array = auxiliaryArray;
			arraySize = newArraySize;
			minimumElement = newMinimumElement;
		}
	}
	// else, if the element we removed was the biggest element from the array
	else if (elem == minimumElement + arraySize - 1)
	{
		int indexLastElement;
		// find the index of the last value of 1 from the array
		indexLastElement = arraySize - 1;
		while (indexLastElement > 0 && array[indexLastElement] == false)
			indexLastElement--;
		// if we can represent the array on an array half the size, we resize it.
		if(indexLastElement <= arraySize/2)
		{
			int newArraySize, index;
			bool* auxiliaryArray;
			newArraySize = indexLastElement + 1;
			auxiliaryArray = new bool[newArraySize];
			// copy the old array into the new one
			for (index = 0; index < newArraySize; index++)
				auxiliaryArray[index] = array[index];
			//delete the old array
			delete[] array;

			//update the parameters of the array
			array = auxiliaryArray;
			arraySize = newArraySize;
		}
	}
	return true;
}

// complexity: tetha(1) 
bool Set::search(TElem elem) const {
	// if elem is out of bounds ( < minimum or > maximum) return false
	if (elem < minimumElement || elem >= minimumElement + arraySize)
		return false;
	// return the value from the array, which represents whether the element is in the set or not
	return array[elem - minimumElement];
}

// complexity: tetha(1)
int Set::size() const {
	return arrayActualSize;
}

// complexity: tetha(1)
bool Set::isEmpty() const {
	return (arrayActualSize == 0);
}

// complexity: tetha(1)
Set::~Set() {
	delete[] array;
}


SetIterator Set::iterator() const {
	return SetIterator(*this);
}


