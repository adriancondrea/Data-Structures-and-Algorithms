#include "Bag.h"
#include "BagIterator.h"
#include <exception>
#include <iostream>
using namespace std;

//for complexities, n - number of nodes of the list (number of distinct elements)
// default constructor for the bag, initializes the head to null
// complexity: tetha(1)
Bag::Bag() {
	this->head = nullptr;
	this->numberOfElements = 0;
}

//complexity: O(n) - average
void Bag::add(TElem elem) {
	Node* auxiliaryNode = this->searchElementReturnAddress(elem);
	// if the element does not exist in the bag, we add it by allocating space for a new node, setting its value
	// to elem, its frequency to one and adding it to the beginning of the bag.
    if (auxiliaryNode == nullptr) {
        auxiliaryNode = new Node;
        auxiliaryNode->value = elem;
        auxiliaryNode->frequency = 1;
        auxiliaryNode->next = this->head;
        this->head = auxiliaryNode;
    } else      //otherwise (if we found the element in the bag) we just increase its frequency
        auxiliaryNode->frequency++;
    this->numberOfElements++;
}

//complexity: O(n)
bool Bag::remove(TElem elem) {
	// we search for the element in the bag. If we don't find it (nodeToBeRemoved == nullptr) we return false
	Node *nodeToBeRemoved, *previousNode;
	this->searchElementAndPrevious(elem, previousNode, nodeToBeRemoved);
    if (nodeToBeRemoved != nullptr) {
        // if the frequency of the node to be removed is greater than 1, we just have to decrease it to remove one
        // instance of elem
        if (nodeToBeRemoved->frequency > 1)
            nodeToBeRemoved->frequency--;
        // otherwise we have to remove the node from the list
        else {
            // if the node to be removed is the head, we set the head to be the next element
            if(nodeToBeRemoved == this->head) {
                head = head->next;
            } else{
                // otherwise we set the links between previous and next accordingly.
                previousNode->next = nodeToBeRemoved->next;
            }
            // then we deallocate the memory for the node
            delete nodeToBeRemoved;
        }
        this->numberOfElements--;
        return true;        // meaning we removed one instance of elem from the bag
    } else return false;    // nothing was removed
}

/*
// OLD remove with two parsings
 bool Bag::remove(TElem elem) {
	Node* nodeToBeRemoved = this->searchElementReturnAddress(elem);
    if (nodeToBeRemoved != nullptr) {
        if (nodeToBeRemoved->frequency > 1)
            nodeToBeRemoved->frequency--;
        else {
            if(nodeToBeRemoved == this->head) {
                head = head->next;
                delete nodeToBeRemoved;
            } else{
                auto prevNode = this->head;
                while(prevNode->next != nodeToBeRemoved)
                    prevNode = prevNode->next;
                prevNode->next = nodeToBeRemoved->next;
                delete nodeToBeRemoved;
            }
        }
        this->numberOfElements--;
        return true;
    } else return false;
}
*/

// complexity: O(n)
bool Bag::search(TElem elem) const {
	// we parse the bag using an auxiliary node, returning true if we find elem in the bag, false otherwise
	Node* auxiliaryNode = this->head;
	while(auxiliaryNode != nullptr)
    {
	    if(auxiliaryNode->value == elem)
	        return true;
	    auxiliaryNode = auxiliaryNode->next;
    }
	return false; 
}

//complexity:O(n)
Bag::Node *Bag::searchElementReturnAddress(TElem elem) const{
    // we parse the bag using an auxiliaryNode and return a pointer to the node where elem is stored or nullptr if
    // elem is not in the bag
    Node* auxiliaryNode = this->head;
    while(auxiliaryNode != nullptr) {
        if (auxiliaryNode->value == elem)
            return auxiliaryNode;
        auxiliaryNode = auxiliaryNode->next;
    }
    return nullptr;
}

//complexity: O(n)
int Bag::nrOccurrences(TElem elem) const {
    // returns the number of occurences of elem in the bag.
	Node* auxiliaryNode = this->searchElementReturnAddress(elem);
	// if the element does not exist, we return 0
	if(auxiliaryNode == nullptr)
	    return 0;
	// else we return the frequency stored in the node where elem is
	else return auxiliaryNode->frequency;
}

//complexity: tetha(1)
int Bag::size() const {
	return this->numberOfElements;
}

//complexity:tetha(1)
bool Bag::isEmpty() const {
    return this->numberOfElements == 0;
}

//complexity: tetha(1)
BagIterator Bag::iterator() const {
	return BagIterator(*this);
}

//complexity: O(n)
Bag::~Bag() {
    // we parse the list and delete all nodes
    Node *auxiliaryNode = this->head, *nextNode;
    while(auxiliaryNode != nullptr)
    {
        nextNode = auxiliaryNode->next;
        delete auxiliaryNode;
        auxiliaryNode = nextNode;
    }
}

// complexity: O(n)
// searches for the node containing elem as value and returns its address in current, and in previous returns the
// address of the node before it. If the node does not exist, returns null through current and in previous the address
// of the last node
void Bag::searchElementAndPrevious(TElem elem, Bag::Node *&previous, Bag::Node *&current) {
    previous = nullptr;
    current = this->head;
    while(current != nullptr && current->value != elem)
    {
        previous = current;
        current = current->next;
    }
}

int Bag::removeOccurrences(int nr, TElem elem) {
    //removes nr occurrences of elem. If the element appears less than nr times, all occurrences will be
    // removed. returns the number of times the element was removed.
    //throws an exception if nr is negative
    // n - number of nodes of the list (number of distinct numbers in the bag)
    //Complexities:
    //best case - tetha(1) - nr is negative / is zero / the elem is the head of the list
    //worst case - tetha(n) - the element is the tail, nr > 0
    //total complexity - O(n)

    //throw an exception if nr is negative
    if(nr < 0)
        throw exception();
    // if we want to remove the element 0 times, return 0
    if(nr == 0)
        return 0;
    Node *previous, *current;
    this->searchElementAndPrevious(elem, previous, current);
    // if we didn't find the element return 0
    if(current == nullptr)
        return 0;
    // if elem appears more than numberOfOccurences, we just subtract numberOfOccurences from his frequency and return
    // numberOfOccurences
    else if(current->frequency > nr)
    {
        current->frequency -= nr;
        this->numberOfElements -= nr;     //update the number of elements
        return nr;                        //return the number of elements removed
    } else{     //otherwise we have to remove the node completely and return its frequency.
        nr = current->frequency;      //save the node's frequency in order to return it
        //case 1: the node we want to remove is the head
        if(current == this->head)
        {
            this->head = this->head->next;
        } else{     //case 2: the node we want to remove is not head, we have to set the link of previous to its next
            previous->next = current->next;
        }
        delete current;     //delete the node
        this->numberOfElements -= nr;
        return nr;
    }
}
