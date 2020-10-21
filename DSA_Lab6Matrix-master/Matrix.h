#pragma once

//DO NOT CHANGE THIS PART
typedef int TElem;
#define NULL_TELEM 0
#define INITIAL_SIZE 2
#define INVALID_INDEX -1

class Matrix {
private:
    // define the matrix element structure
    struct matrixElement {
        int line, column;
        TElem value;
    };

    // define a comparison function for matrix elements
    int comparisonFunction(const matrixElement& firstElement, const matrixElement& secondElement) const;

    // define a node structure to be stored in the array
    struct Node{
        matrixElement info;
        int left, right;
    };

    //define the Binary Search tree structure
    struct BinarySearchTree{
        int root;
        Node* elements;
        int size, capacity, indexFirstEmpty;
    };

    int search(int line, int column) const;
    int insertNodeRecursive(int headIndex, matrixElement toBeAdded);
    int removeRecursively(int headIndex, matrixElement toBeRemoved);
    int minimumElementIndex(int currentNode);
    void addNode(int i, int j, TElem e);
    void removeNode(int i, int j);
    void resize();
private:
	//TODO - Representation
	int lines, columns;
	BinarySearchTree BST;
public:
	//constructor
	Matrix(int nrLines, int nrCols);

	~Matrix();
	//returns the number of lines
	int nrLines() const;

	//returns the number of columns
	int nrColumns() const;

	//returns the element from line i and column j (indexing starts from 0)
	//throws exception if (i,j) is not a valid position in the Matrix
	TElem element(int i, int j) const;

	//modifies the value from line i and column j
	//returns the previous value from the position
	//throws exception if (i,j) is not a valid position in the Matrix
	TElem modify(int i, int j, TElem e);
};
