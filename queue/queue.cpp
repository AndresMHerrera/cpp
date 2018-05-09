/********************************************************************
* Author        :       Herrera, Andres
*
* File          :       queue.cpp
*
* Purpose :
*       This file contains all of the function implementations
*       specified in the header file (queue.h)
*
*********************************************************************/
#include "queue.h"

/**************************************************
Description : This constructor will initialize the 
			private members of the queue class
			to NULL. 
***************************************************/
template <class T>
queue<T>::queue()
{
	this->front = NULL;
	this->back = NULL;
	this->count = 0;
}

/**************************************************
Description : This destructor will traverse a queue
			node at a time deleting each node
			allocated during program execution. 

preconditions : The destructor will delete each node
			if the queue is not NULL.

postcondition : All memmory allocated will be freed.
***************************************************/
template <class T>
queue<T>::~queue()
{
	if(this->front != NULL) {

		queueNode<T> * trav_ptr = this->front;

		while(this->front != NULL) {

			this->front = this->front->next_ptr;
			delete trav_ptr;
			trav_ptr = this->front;
		}
	}
}

/****************************************************
Description : The purpose of this function is to 
			insert a new queue node into the queue. 

precondition : A integer argument must be passesd 
			into the function to insert. 

postcondition : There will be no return value, but 
			at the end of function execution the 
			new node will be inserted into the queue.
*****************************************************/
template <class T>			
void queue<T>::enque(T item)
{
	//insertion when queue is NULL
	if(this->front == NULL) {

		this->front = new queueNode<T>(item);
		this->back = this->front;
	}

	//insertion when queue is not NULL
	else {
		queueNode<T> * new_node = new queueNode<T>(item);
		this->back->next_ptr = new_node;
		this->back = new_node;
		new_node = NULL;
	}

	++this->count;
}


/********************************************************
Description : The purpose of this function is to delete
			remove the next item in the queue.

precondition : The queue must not be NULL.

postcondition : The front node will be removed
*******************************************************/
template <class T>
void queue<T>::deque()
{
	if(this->front != NULL) {

		//delete if its the last node
		if(this->front->next_ptr == NULL) {
			delete this->front;
			this->front = NULL;
			this->back = NULL;
		}

		else {
			queueNode<T> * target = this->front;
			this->front = this->front->next_ptr;
			target->next_ptr = NULL;

			delete target;
			target = NULL;
		}

		--this->count;
	}	
}

/********************************************************
Description : The purpose of this function is to return
				the next value is the queue.

precondition : The queue must not be NULL.
*******************************************************/
template <class T>
T queue<T>::peek() {
	if( !this->isEmpty() ) {
		return this->front->queueValue;
	}
}


/***************************************************
Description : The purpose of this function is to 
			determine if the queue is NULL or not.

precondition : none

postcondition : will return true if the queue is 
			NULL, false otherwise.
***************************************************/
template <class T>			
bool queue<T>::isEmpty()
{
	return (this->front == NULL) ? true : false;
}


/***************************************************
Description : The purpose of this function is to
				return the length of the queue.

precondition : none

postcondition : will return the size of the queue.
***************************************************/
template <class T>
int queue<T>::size()
{
	return this->count;
}