#pragma once
#define ARRAY_INITIAL_CAPACITY 10
#define RESIZE_FACTOR 2
#include <exception>
template <typename T>
class DynamicVector
{
    friend class Map;
    friend class MapIterator;
private:
	int capacity{}, actualSize{};
	T* vectorElements;

public:
	DynamicVector(int capacity = ARRAY_INITIAL_CAPACITY);
	DynamicVector(const DynamicVector& newVector);
	~DynamicVector();
	T& operator[](int position);
	const T& operator[](int position) const;
	DynamicVector& operator=(const DynamicVector& newVector);
	void resize(int resizeFactor = RESIZE_FACTOR);
};

/**default constructor for a DynamicVector**/
// complexity: tetha(1)
template<typename T>
inline DynamicVector<T>::DynamicVector(int capacity)
{
    this->actualSize = 0;
	this->capacity = capacity;
	this->vectorElements = new T[capacity];
}

/*copy constructor for a DynamicVector*/
// complexity: tetha(n) where n - number of elements in the vector passed as parameter
template<typename T>
inline DynamicVector<T>::DynamicVector(const DynamicVector& newVector)
{
    this->actualSize = newVector.actualSize;
	this->capacity = newVector.capacity;
	this->vectorElements = new T[this->capacity];
	for (int i = 0; i < this->capacity; i++)
		this->vectorElements[i] = newVector.vectorElements[i];
}

// destructor for a DynamicVector
// complexity: tetha(1)
template<typename T>
inline DynamicVector<T>::~DynamicVector()
{
	delete[] this->vectorElements;
}

// member access operator, throws erxception if position is invalid
// complexity: tetha(1)
template<typename T>
inline T& DynamicVector<T>::operator[](int position)
{
    if(position >= this->capacity || position < 0)
        throw std::exception();
	return this->vectorElements[position];
}

// assignment operator
// best case: self assignment - tetha(1)
// worst case: assignment to another vector - tetha(n), n - number of elements
// overall complexity:  O(n) where n - number of elements of newVector
template<typename T>
inline DynamicVector<T>& DynamicVector<T>::operator=(const DynamicVector& newVector)
{
	if (this == &newVector)
		return *this;

	this->capacity = newVector.capacity;
	this->actualSize = newVector.actualSize;
	delete[] this->vectorElements;
	this->vectorElements = new T[this->capacity];
	for (int i = 0; i < this->capacity; i++)
		this->vectorElements[i] = newVector.vectorElements[i];

	return *this;
}

/*Resizes the current DynamicVector, multiplying its capacity by a given factor*/
// time complexity: O(n), where n - capacity before resizing
// space complexity: capacity of the vector doubles
template<typename T>
inline void DynamicVector<T>::resize(int resizeFactor)
{
    int oldCapacity = this->capacity;
	this->capacity *= resizeFactor;
	T* newVector = new T[this->capacity];
	for (int i = 0; i < oldCapacity; i++)
		newVector[i] = this->vectorElements[i];
	delete[] this->vectorElements;
	this->vectorElements = newVector;
}

// constant member access operator
// complexity: tetha(1)
template<typename T>
const T &DynamicVector<T>::operator[](int position) const {
    if(position >= this->capacity || position < 0)
        throw std::exception();
    return this->vectorElements[position];
}
