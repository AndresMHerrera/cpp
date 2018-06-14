#include "binary.search.tree.h"

BinarySearchTree::BinarySearchTree()
{
	Root = EMPTY;
}

/*********************************************************
Description : The destructor will call the Destroy_Tree()
			method and send a pointer to the root. 

precondition : the binary search tree must not be empty.

postcondition : All memory allocated during execution time 
				will be freed. 
*********************************************************/
BinarySearchTree::~BinarySearchTree()
{
	if (Root != EMPTY)
	{
		this->destroyTree(Root);
	}
}

/**********************************************************
Description : The purpose of this function is to delete 
			each binary search tree node, starting from 
			the bottom.(leaves).

precondition : none

postcondition : All memory allocated during execution time
				will be freed.
**********************************************************/
void BinarySearchTree::destroyTree(Tree_Node *&temp_Tree_ptr)
{
	//destroy the tree until the root is set to NULL
	if (temp_Tree_ptr != EMPTY)
	{
		this->destroyTree(temp_Tree_ptr->Left_Child);
		this->destroyTree(temp_Tree_ptr->Right_Child);
		delete temp_Tree_ptr;
		temp_Tree_ptr = EMPTY;
	}
}

bool BinarySearchTree::createBinarySearchTree(vector<int> treeItems)
{
	int level = 0;
	bool successFlag = true;

	for (std::vector<int>::iterator it = treeItems.begin(); it != treeItems.end(); ++it)
	{
		if (this->Root == EMPTY)
		{
			this->insertNode(*it, level, this->Root);
		}
		else
		{
			Tree_Node *insertLocation = this->findNodeInsertLocation(*it, level, this->Root);

			if (insertLocation != EMPTY)
			{
				this->insertNode(*it, level, insertLocation);
			}
			else
			{
				cout << "Error, could not insert: " << *it << endl;
				successFlag = false;
			}
		}
	}

	return successFlag;
}

// Does not account for root special case.
Tree_Node *BinarySearchTree::findNodeInsertLocation(int value, int level, Tree_Node *march)
{
	Tree_Node *target = NULL;

	if (value < march->Search_Key && march->Left_Child != EMPTY)
		target = this->findNodeInsertLocation(value, ++level, march->Left_Child);

	else if (value > march->Search_Key && march->Right_Child != EMPTY)
		target = this->findNodeInsertLocation(value, ++level, march->Right_Child);

	else
		target = march;

	return target;
}

void BinarySearchTree::insertNode(int value, int level, Tree_Node *insertLocation)
{

	Tree_Node *newNode = new Tree_Node(value, 0);

	if (this->Root == EMPTY)
		this->Root = newNode;

	else if (value < insertLocation->Search_Key)
	{
		insertLocation->Left_Child = newNode;
		insertLocation->Left_Child->node_level = insertLocation->node_level + 1;
	}

	else if (value > insertLocation->Search_Key)
	{
		insertLocation->Right_Child = newNode;
		insertLocation->Right_Child->node_level = insertLocation->node_level + 1;
	}

	// Insert duplicate
	else
	{
		newNode->node_level = insertLocation->node_level;

		//insert 1st duplicate
		if (insertLocation->Duplicate == NULL)
			insertLocation->Duplicate = newNode;

		//insert in front of list
		else
		{
			newNode->Duplicate = insertLocation->Duplicate;
			insertLocation->Duplicate = newNode;
		}
	}
}

/*************************************************************************
Description : The purpose of this function is to initialize the value 
			of a new tree node.

precondition : memory should already be allocated for a new tree node.

postcondition : All values of the new tree node will be initialized. 
				Except the level at which it will be inserted. 
**************************************************************************/
Tree_Node::Tree_Node(int insertValue, int level)
{
	Search_Key = insertValue;
	node_level = level;
	visited = NOT_VISITED;
	Left_Child = EMPTY;
	Right_Child = EMPTY;
	Duplicate = EMPTY;
}


/*********************************************************
Description : The purpose of this function is to determine
			the maximum height of the binary search tree, 
			using the depth first search algorithm.

precondition : The binary search tree must not be empty.

postcondition : The function will return the maximum tree
				height.
*********************************************************/
int BinarySearchTree::calculateTreeHeight()
{
	int maxHeight = INITIALIZE; //keeps track of max tree height

	if (Root != EMPTY)
	{
		stack<Tree_Node *> S; //used for backtracking
		Tree_Node *march = Root; //used to traverse the tree

		S.push(march);

		maxHeight = S.size();

		while (!S.empty())
		{
			if (march->Left_Child != EMPTY && march->Left_Child->visited == false)
			{
				march = march->Left_Child;
				S.push(march);
			}

			else if (march->Right_Child != EMPTY && march->Right_Child->visited == false)
			{
				march = march->Right_Child;
				S.push(march);
			}

			//no more children to visit
			else
			{
				if (S.size() > maxHeight)
					maxHeight = S.size();

				S.pop();

				if (!S.empty())
				{
					march->visited = true;
					march = S.top();
				}
			}
		}
	}
	return (maxHeight - 1);
}


/************************************************************
Description : The purpose of this function is to determine 
			the maximum tree width and the maximum tree width
			level, using the breadth first search algorithm.

precondition : The binary search tree must not be emtpy.

postcondition : Will print to the terminal the tree width
			and the level at which the maximum tree width
			is.
*************************************************************/
void BinarySearchTree::calculateTreeWidth()
{
	if (Root != EMPTY)
	{
		queue<Tree_Node *> Q;
		Tree_Node *march_p = Root;
		int maxWidth_level = 0;
		int currentLevel = 0;
		int maxWidth = 0;

		Q.push(march_p);
		maxWidth = Q.size();

		while (!Q.empty())
		{
			march_p = Q.front();
			Q.pop();

			//insert children into queue
			if (march_p->Left_Child != EMPTY)
				Q.push(march_p->Left_Child);

			if (march_p->Right_Child != EMPTY)
				Q.push(march_p->Right_Child);

			//check if maxWidth and maxWidth level need to be updated
			if (!Q.empty())
			{
				if (Q.front()->node_level != currentLevel)
				{
					if (maxWidth <= Q.size())
					{
						maxWidth = Q.size();
						maxWidth_level = currentLevel + 1;
					}
					currentLevel++;
				}
			}
		}
		cout << "Max Width : " << maxWidth << endl;
		cout << "Max Width level : " << maxWidth_level << endl;
	}
}


void BinarySearchTree::breadthFirstPrint()
{
	if (this->Root != EMPTY)
	{
		queue<Tree_Node *> Q;
		Tree_Node *march_p = Root;

		Q.push(march_p);

		while (!Q.empty())
		{
			march_p = Q.front();
			Q.pop();

			cout << "value: " << march_p->Search_Key << '\t' << "level :" << march_p->node_level << endl;

			if (march_p->Left_Child != EMPTY)
				Q.push(march_p->Left_Child);

			if (march_p->Right_Child != EMPTY)
				Q.push(march_p->Right_Child);
		}
	}
}