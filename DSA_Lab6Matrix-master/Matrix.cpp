#include "Matrix.h"
#include <exception>
using namespace std;

// complexity: tetha(1)
Matrix::Matrix(int nrLines, int nrCols) {
	   
	//TODO - Implementation
	this->lines = nrLines;
	this->columns = nrCols;
	// initially the root is at an invalid index
	this->BST.root = INVALID_INDEX;
	// the size is 0
	this->BST.size = 0;
	// index first empty is also zero
	this->BST.indexFirstEmpty = 0;
	// capacity is equal the predefined value
	this->BST.capacity = INITIAL_SIZE;
	// create a vector of Nodes of size capacity
	this->BST.elements = new Node[this->BST.capacity];
}

// complexity: tetha(1)
int Matrix::nrLines() const {
	//TODO - Implementation
	return this->lines;
}

// complexity: tetha(1)
int Matrix::nrColumns() const {
	//TODO - Implementation
	return this->columns;
}

// complexity: O(size)
// return the value of the element at position [i,j] in the matrix if it exists, NULL_TELEM otherwise.
TElem Matrix::element(int i, int j) const {
	//TODO - Implementation
	if(i < 0 || i > this->nrLines() || j < 0 || j > this->nrColumns())
	    throw std::exception();
	auto node = this->search(i, j);
	if(node != INVALID_INDEX)
	    return this->BST.elements[node].info.value;
	return NULL_TELEM;
}

// complexity: O(size)
TElem Matrix::modify(int i, int j, TElem e) {
	//TODO - Implementation
    if(i < 0 || i > this->nrLines() || j < 0 || j > this->nrColumns())
        throw std::exception();
    auto node = this->search(i, j);
    //we have 4 cases:
    // case 1: node exists, e.value != null_telem -> update its value
    // case 2: node exists, e.value  = null_telem -> delete the node
    // case 3: node does not exist, e.value != null_telem -> add the node
    // case 4: node does not exist, e.value = null_telem -> do nothing
    if(node != INVALID_INDEX)
    {
        //save its old value
        TElem savedValue = this->BST.elements[node].info.value;
        //set its new value
        this->BST.elements[node].info.value = e;
        return savedValue;
    } else if(e != NULL_TELEM)
    {
        this->addNode(i, j, e);
    }
	return NULL_TELEM;
}

// returns -1 if firstElement < secondElement, 0 if firstElement = secondElement, 1 if firstElement > secondElement
//complexity: tetha(1)
int Matrix::comparisonFunction(const Matrix::matrixElement& firstElement,const Matrix::matrixElement& secondElement) const{
    int aux;
    aux = firstElement.line - secondElement.line;
    if(aux < 0)
        return -1;
    else if(aux > 0)
        return 1;
    else {
        aux = firstElement.column - secondElement.column;
        if(aux < 0)
            return -1;
        else if(aux > 0)
            return 1;
        else return 0;
    }
}

//complexity: O(size)
int Matrix::search(int line, int column) const{
    if(line < 0 || column < 0 || line > this->lines || column > this->columns)
        return INVALID_INDEX;
    // create a searchedElement to search for
    matrixElement searchedElement{};
    searchedElement.line = line;
    searchedElement.column = column;
    // start the search from the root
    auto currentNode = this->BST.root;
    while(currentNode != INVALID_INDEX) {
        // we found the element
        if (this->comparisonFunction(this->BST.elements[currentNode].info, searchedElement) == 0)
            return currentNode;
        // if the element we are looking for is greater than the current element. search in the right subtree
        else if(this->comparisonFunction(this->BST.elements[currentNode].info, searchedElement) < 0)
            currentNode = this->BST.elements[currentNode].right;
        // otherwise search in the left subtree
        else
            currentNode = this-> BST.elements[currentNode].left;
    }
    //element not found
    return INVALID_INDEX;
}

//complexity: O(size)
int Matrix::insertNodeRecursive(int headIndex, matrixElement value) {
    if(headIndex == INVALID_INDEX)
    {
        // set index to be inserted to first empty
        int indexToBeInserted = this->BST.indexFirstEmpty;
        // move first empty to next empty
        this->BST.elements[indexToBeInserted].right = INVALID_INDEX;
        this->BST.elements[indexToBeInserted].left = INVALID_INDEX;
        this->BST.elements[indexToBeInserted].info = value;
        this->BST.size++;
        this->BST.indexFirstEmpty++;
        return indexToBeInserted;
    }
    else if(this->comparisonFunction(this->BST.elements[headIndex].info, value) < 0)
        this->BST.elements[headIndex].right = this->insertNodeRecursive(this->BST.elements[headIndex].right, value);
    else
        this->BST.elements[headIndex].left = this->insertNodeRecursive(this->BST.elements[headIndex].left, value);
    return headIndex;
}

// complexity: O(size)
void Matrix::addNode(int i, int j, TElem e) {
    // if the bst is full, resize
    if(this->BST.size == this->BST.capacity)
        this->resize();
    //create the element to be added
    matrixElement elementToBeAdded;
    elementToBeAdded.line = i;
    elementToBeAdded.column = j;
    elementToBeAdded.value = e;
    //case 1: the root is empty
    if(this->BST.root == INVALID_INDEX)
    {
        this->BST.root = 0;
        this->BST.elements[0].left = INVALID_INDEX;
        this->BST.elements[0].right = INVALID_INDEX;
        this->BST.elements[0].info = elementToBeAdded;
        this->BST.size++;
        this->BST.indexFirstEmpty++;
        return ;
    }
    //case 2: non-empty tree
    this->insertNodeRecursive(this->BST.root, elementToBeAdded);
}

//complexity: O(size)
void Matrix::resize() {
    int newCapacity = this->BST.capacity * 2;
    Node* newElements = new Node[newCapacity];
    for(int i=0; i < this->BST.size; i++)
        newElements[i] = this->BST.elements[i];
    delete[] this->BST.elements;
    this->BST.elements = newElements;
    this->BST.capacity = newCapacity;
}

// returns the index of the minimum element in the tree
// complexity: O(size)
int Matrix::minimumElementIndex(int currentNode) {
    //last node will contain the last valid node. with currentNode we will check the left subtree of last node.
    int lastNode = currentNode;
    while(currentNode != INVALID_INDEX)
    {
        lastNode = currentNode;
        currentNode = this->BST.elements[currentNode].left;
    }
    return lastNode;
}

//removes a node from the tree
// complexity: O(size)
void Matrix::removeNode(int i, int j) {
    //search for the node
    int indexOfNode = this->search(i, j);
    //if we found the node
    if(indexOfNode != INVALID_INDEX)
    {
        //create the element to be removed and initialize it
        matrixElement elementToBeRemoved;
        elementToBeRemoved.line = i;
        elementToBeRemoved.column = j;
        //remove the element
        this->BST.root = this->removeRecursively(this->BST.root, elementToBeRemoved);
        this->BST.size--;
    }
}

Matrix::~Matrix() {
    delete[] this->BST.elements;
}

int Matrix::removeRecursively(int headIndex, Matrix::matrixElement toBeRemoved) {
    if(headIndex == INVALID_INDEX)
        return INVALID_INDEX;
    //if we are at the element we want to remove
    if(this->comparisonFunction(toBeRemoved, this->BST.elements[headIndex].info) == 0)
    {
        //case 1: the bst has only one element, the head
        if(this->BST.elements[headIndex].left == INVALID_INDEX && this->BST.elements[headIndex].right == INVALID_INDEX)
        {
            //set the left child of head to be the index of first empty
            this->BST.elements[headIndex].left = this->BST.indexFirstEmpty;
            // set the index of first empty to be the head
            this->BST.indexFirstEmpty = headIndex;
            return INVALID_INDEX;
        }
        // case 2: the head has no left child
        else if(this->BST.elements[headIndex].left == INVALID_INDEX)
        {
            int rightIndex = this->BST.elements[headIndex].right;
            this->BST.elements[headIndex].left = this->BST.indexFirstEmpty;
            this->BST.indexFirstEmpty = headIndex;
            return rightIndex;
        }
        // case 3: the head has no right child
        else if(this->BST.elements[headIndex].right == INVALID_INDEX)
        {
            int leftIndex = this->BST.elements[headIndex].left;
            this->BST.elements[headIndex].left = this->BST.indexFirstEmpty;
            this->BST.indexFirstEmpty = headIndex;
            return leftIndex;
        }
        //case 4: the head has both left and right children. we find the minimum right subtree, move it to the node
        // to be deleted, and delete the minimum
        int minimumIndex = this->minimumElementIndex(this->BST.elements[headIndex].right);
        this->BST.elements[headIndex].info = this->BST.elements[minimumIndex].info;
        this->BST.elements[headIndex].right = this->removeRecursively(BST.elements[headIndex].right, this->BST.elements[headIndex].info);
        return headIndex;
    }
    else if(this->comparisonFunction(toBeRemoved, this->BST.elements[headIndex].info) > 0)
        this->BST.elements[headIndex].left = this->removeRecursively(this->BST.elements[headIndex].left, toBeRemoved);
    else
        this->BST.elements[headIndex].right = this->removeRecursively(this->BST.elements[headIndex].right, toBeRemoved);
    return headIndex;
}