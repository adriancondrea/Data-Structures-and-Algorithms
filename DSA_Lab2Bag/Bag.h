#pragma once
#define NULL_TELEM -11111;
typedef int TElem;
class BagIterator;
// for complexities, n - number of nodes of the list (number of distinct elements)
class Bag {
    // we declare a struct Node used for storing the information saved in our SLL (value, frequency pairs) and a pointer
    // to the next element of the list
    struct Node
    {
        TElem value;
        int frequency;
        Node* next;
    };
private:
    // we represent the bag by keeping a pointer to the head of the list and the number of elements
    Node* head;
    int numberOfElements;
	friend class BagIterator;

public:
	//default constructor for the bag
	Bag();

	//adds an element to the bag complexity: O(n)
	void add(TElem e);

	//removes one occurence of an element from a bag, returns true if an element was removed, false otherwise
	// (if e was not part of the bag) complexity: O(n)
	bool remove(TElem e);

    //removes nr occurrences of elem. If the element appears less than nr times, all occurrences will be removed.
    //returns the number of times the element was removed.
    //throws an exception if nr is negative
    int removeOccurrences(int nr, TElem elem);

	//checks if an element appears in the bag. returns true if it finds the element, false otherwise complexity: O(n)
	bool search(TElem e) const;

	// checks if an element appears in the bag, and if it does, returns a pointer to the node containing the element,
	// returns nullptr if the element is not in the bag. complexity:O(n)
	Node* searchElementReturnAddress(TElem elem) const;

	//searches for an element in the bag and if it finds it, updates the values of current and previous accordingly.
	//complexity: O(n)
	void searchElementAndPrevious(TElem elem, Node* &previous, Node* &current);

	//returns the number of occurrences for an element in the bag complexity: O(n)
	int nrOccurrences(TElem e) const;

	//returns the number of elements from the bag complexity: tetha(1)
	int size() const;

	//returns an iterator for this bag complexity: tetha(1)
	BagIterator iterator() const;

	//checks if the bag is empty complexity:tetha(1)
	bool isEmpty() const;

	//destructor complexity: O(n)
	~Bag();
};