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
			this->top to NULL;
*******************************************************/
template <class T>
Stack<T>::Stack()
{
	this->top = NULL;
	this->count = 0;
}

/******************************************************
Description : The destructor will traverse each stack
			node at a time and delete it.

precondition : The stack must not be NULL

postcondition : All dynamically allocated memory will
			be freed. 
*******************************************************/

template <class T>
Stack<T>::~Stack()
{
	if (this->top != NULL) {

		//will be used to delete each node
		stack_node<T> * trav_ptr = this->top;

		//traverse the stack deleting each node
		while (this->top != NULL) {

			this->top = this->top->back_ptr;
			trav_ptr->back_ptr = NULL;
			delete trav_ptr;

			trav_ptr = this->top;
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
void Stack<T>::push(T item)
{
	//insert if the stack is NULL
	if(this->top == NULL)
		this->top = new stack_node<T>(item, NULL);

	//insert if nodes already exist
	else {
		stack_node<T> * new_stack_node = new stack_node<T>(item, this->top);

		//set the values into the new node and insert it
		//into the stack
		this->top = new_stack_node;
		new_stack_node = NULL;
	}

	++this->count;
}

/******************************************************
Description : The purpose of this function is to delete
			  the top node of the stack.

precondition : The stack must not be NULL

postcondition : The integer value of the node that was 
				deleted	will be returned. 
*******************************************************/
template <class T>
void Stack<T>::pop()
{	
	if (this->top->back_ptr == NULL) {
		delete this->top;
		this->top = NULL;
	}
	else {
		stack_node<T> * node_to_delete = this->top;

		//set the new top pointer location
		this->top = this->top->back_ptr;

		delete node_to_delete;
		node_to_delete = NULL;
	}
	
	this->count = (this->count <= 0) ? 0 : this->count - 1;
}


/*******************************************************
Description : The purpose of this function is to return
			the value of the this->top pointer.

precondition : the stack must not be NULL.

postcondition : Will return an integer value.
********************************************************/
template <class T>
T Stack<T>::peek()
{
	return this->top->stack_value;
}


/******************************************************
Description : The purpose of this function is to 
			determine if the stack is NULL or not.

precondition : none

postcondition : Will return true if the stack is NULL,
				false otherwise. 
*******************************************************/
template <class T>
bool Stack<T>::isEmpty()
{
	return (this->top == NULL) ? true : false;
}

/******************************************************
Description: This function will returnt the size of the
				stack.
*******************************************************/
template <class T>
int Stack<T>::size()
{
	return this->count;
}