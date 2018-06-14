/********************************************************************
* Author        :       Herrera, Andres
* File          :       binary_search_tree.h
*
* Purpose :
*       This file contains all of the function prototypes
*       for the Binary_Search_Tree class. 
*
*********************************************************************/
#ifndef BINARY_SEARCH_TREE_INCLUDED
#define BINARY_SEARCH_TREE_INCLUDED

#include <iostream>
#include <iomanip>
#include <cstring>
#include <sstream>
#include <cstdlib>
#include <vector>
#include <stack>
#include <queue>

#define NOT_VISITED false
#define VISITED true
#define INITIALIZE 0
#define EMPTY NULL

using namespace std;

struct Tree_Node
{
	int Search_Key;
	bool visited;
	int node_level;
	Tree_Node *Left_Child;
	Tree_Node *Right_Child;
	Tree_Node *Duplicate;
	Tree_Node(int insertValue, int level);
};

class BinarySearchTree
{
  public:

	BinarySearchTree();
	~BinarySearchTree();
	bool createBinarySearchTree(vector<int> treeItems);
	int calculateTreeHeight();
	void calculateTreeWidth();
	void breadthFirstPrint();

  private:
	Tree_Node *Root;

	void destroyTree(Tree_Node *&temp_Tree_ptr);
	Tree_Node *findNodeInsertLocation(int value, int level, Tree_Node *march);
	void insertNode(int value, int level, Tree_Node *insertLocation);
};

#endif