/********************************************************************
* Author        :       Herrera, Andres
* File          :       stack.cpp
*
* Purpose :
*       This file contains all of the function implementations
*		specified in the header file (stack.h).
*
*********************************************************************/
#include "stack.h"

/******************************************************
Description : The constructor initializes the private
			stack_top to NULL;
*******************************************************/
template <class T>
stack<T>::stack()
{
	stack_top = EMPTY;
}

/******************************************************
Description : The destructor will traverse each stack
			node at a time and delete it.

precondition : The stack must not be empty

postcondition : All dynamically allocated memory will
			be freed. 
*******************************************************/

template <class T>
stack<T>::~stack()
{
	if (stack_top != EMPTY) {

		//will be used to delete each node
		stack_node<T> * trav_ptr = stack_top;

		//traverse the stack deleting each node
		while (stack_top != EMPTY) {

			stack_top = stack_top->back_ptr;
			trav_ptr->back_ptr = EMPTY;
			delete trav_ptr;

			trav_ptr = stack_top;
		}
	}
}

/******************************************************
Description : The purpose of this function is to insert
			a new stack node into the stack.

precondition : none

postcondition : The new node will be inserted into the 
			stack at the top. 
*******************************************************/
template <class T>
void stack<T>::push(T insert_value)
{
	//insert if the stack is empty
	if(stack_top == EMPTY)
		stack_top = new stack_node<T>(insert_value, EMPTY);

	//insert if nodes already exist
	else {
		stack_node<T> * new_stack_node = new stack_node<T>(insert_value,stack_top);

		//set the values into the new node and insert it
		//into the stack
		stack_top = new_stack_node;
		new_stack_node = EMPTY;
	}
}

/******************************************************
Description : The purpose of this function is to delete
			  the top node of the stack.

precondition : The stack must not be empty

postcondition : The integer value of the node that was 
				deleted	will be returned. 
*******************************************************/
template <class T>
void stack<T>::pop()
{
	stack_node<T> * node_to_delete = stack_top;

	//set the new top pointer location
	stack_top = stack_top->back_ptr;

	delete node_to_delete;
	node_to_delete = EMPTY;

}


/******************************************************
Description : The purpose of this function is to delete
			  the top node of the stack.

precondition : The stack must not be empty

postcondition : The integer value of the node that was 
				deleted	will be returned. 
*******************************************************/
template <class T>
T stack<T>::pop_return()
{
	if(stack_top != EMPTY) {
		stack_node<T> * node_to_delete = stack_top;
		T valueReturned = node_to_delete->stack_value;

		//set the new top pointer location
		stack_top = stack_top->back_ptr;

		delete node_to_delete;
		node_to_delete = EMPTY;

		return valueReturned;
	}

}


/******************************************************
Description : The purpose of this function is to 
			determine if the stack is empty or not.

precondition : none

postcondition : Will return true if the stack is empty,
				false otherwise. 
*******************************************************/
template <class T>
bool stack<T>::is_empty()
{
	if (stack_top == EMPTY)
		return true;
	else
		return false;
}

/******************************************************
 : This function will traverse the stack 
			counting each node in the stack. The function
			will return an integer(the height of the
			binary search tree). counting will start
			zero.

preconditions : none

postcondition : will return an integer used to represent
			the hight of the binary search tree. (N - 1)
*******************************************************/
template <class T>
int stack<T>::size()
{
	int height_count = COUNT_INITIALIZER; // initialize to 0

	if (stack_top != EMPTY) {

		stack_node<T> * trav_ptr = stack_top;

		//traverse the stack and count the nodes
		while(trav_ptr != EMPTY) {
			height_count++;
			trav_ptr = trav_ptr->back_ptr;
		}
	}
	return height_count;
}


/*******************************************************
Description : The purpose of this function is to return
			the value of the stack_top pointer.

precondition : the stack must not be empty.

postcondition : Will return an integer value.
********************************************************/
template <class T>
T stack<T>::return_top()
{
	return stack_top->stack_value;

}

template <class T>
void stack<T>::print()
{
	stack_node<T> * march = stack_top;

	while(march != EMPTY) {
		cout << march->stack_value << endl;
		march = march->back_ptr;
	}
}
