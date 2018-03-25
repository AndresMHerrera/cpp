/********************************************************************
* Author        :       Herrera, Andres
* File          :       main.cpp
*
* Purpose :
*       This file contains the main function which creates an
*		instance of a binary search tree, and begins reading
*		user input.
*********************************************************************/
#include "binary.search.tree.h"
#include "stdin.reader.h"

int main(int argc, char *argv[])
{
	BinarySearchTree tree;
	STDinReaderService reader;
	vector<int> integerList = reader.read_stdin();

	cout << "input count: " << integerList.size() << endl;
	cout << "input: ";
	for (std::vector<int>::iterator it = integerList.begin(); it != integerList.end(); ++it)
	{
		std::cout << *it << " ";
	}
	cout << "\n" << endl;

	if (tree.createBinarySearchTree(integerList)) {

		cout << "Printing Binary Search Tree" << endl;
		tree.breadthFirstPrint();
		cout << "\n" << endl;
		cout << "Max Tree Height : " << tree.calculateTreeHeight() << endl;
		tree.calculateTreeWidth();
	}

	else {
		cout << "Error: Unable to create Binary Search Tree" << endl;
	}

	return 0;
}
