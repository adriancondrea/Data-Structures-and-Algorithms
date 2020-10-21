#pragma once
#include<vector>
#include<utility>
//DO NOT INCLUDE MultiMapIterator

using namespace std;

//DO NOT CHANGE THIS PART
typedef int TKey;
typedef int TValue;
typedef std::pair<TKey, TValue> TElem;
#define NULL_TVALUE -111111
#define LOAD_FACTOR 0.7
#define INITIAL_SIZE 2
#define NULL_TELEM pair<int,int>(NULL_TVALUE, NULL_TVALUE)
//define a DELELTED_TELEM to mark deleted elements with
#define DELETED_TELEM pair<int,int>(NULL_TVALUE -1, NULL_TVALUE -1)
class MultiMapIterator;

class MultiMap
{
	friend class MultiMapIterator;

private:
	// we store a pointer to the elements, the capactiy, and the actual size
    TElem* elements;
    int capacity;
	int actualSize;

	// checks if a number is prime
	static bool isPrime(int number);

	// returns the next prime number >= than the number passed as parameter
    int nextPrime(int number);

	// computes the loadFactor of the hashTable
	double loadFactor();

	// first hash function
    int firstHash(TKey key) const;

    // second hash function
    int secondHash(TKey key) const;

    // the final hashing function
    int hashingFunction(TKey key, int i) const;

public:
	//constructor
	MultiMap();

	//adds a key value pair to the multimap
	void add(TKey c, TValue v);

	//removes a key value pair from the multimap
	//returns true if the pair was removed (if it was in the multimap) and false otherwise
	bool remove(TKey c, TValue v);

	//returns the vector of values associated to a key. If the key is not in the MultiMap, the vector is empty
	vector<TValue> search(TKey c) const;

	//returns the number of pairs from the multimap
	int size() const;

	//checks whether the multimap is empty
	bool isEmpty() const;

	//returns an iterator for the multimap
	MultiMapIterator iterator();

	//destructor
	~MultiMap();

	//resizes the hash table, rehashing all its elements
	void resize();
};

