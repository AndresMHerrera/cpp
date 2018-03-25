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
	queueFront = EMPTY;
	queue_back = EMPTY;
}

/**************************************************
Description : This destructor will traverse a queue
			node at a time deleting each node
			allocated during program execution. 

preconditions : The destructor will delete each node
			if the queue is not empty.

postcondition : All memmory allocated will be freed.
***************************************************/
template <class T>
queue<T>::~queue()
{
	if(queueFront != EMPTY) {

		queueNode<T> * trav_ptr = queueFront;

		while(queueFront != EMPTY) {

			queueFront = queueFront->next_ptr;
			delete trav_ptr;
			trav_ptr = queueFront;
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
void queue<T>::enque(T insert_value)
{
	//insertion when queue is empty
	if(queueFront == EMPTY) {

		queueFront = new queueNode<T>(insert_value);
		queue_back = queueFront;
	}

	//insertion when queue is not empty
	else {

		queueNode<T> * new_node = new queueNode<T>(insert_value);
		queue_back->next_ptr = new_node;
		queue_back = new_node;
		new_node = EMPTY;
	}
}

/********************************************************
Description : The purpose of this function is to delete
			a node from the queue (the front node).

precondition : The queue must not be empty.

postcondition : The front node will be deleted, including
			the there is any dublicate nodes that have 
			the same value. 
*******************************************************/
template <class T>			
T queue<T>::deque_andReturn()
{
	if(queueFront != EMPTY) {

		//delete if its the last node
		if(queueFront->next_ptr == NULL) {

			T temp = queueFront->queueValue;
			delete queueFront;
			queueFront = NULL;
			queue_back = NULL;

			return temp;
		}

		else {

			queueNode<T> * target = queueFront;
			queueFront = queueFront->next_ptr;
			target->next_ptr = NULL;
			T temp = target->queueValue;
			delete target;
			target = NULL;

			return temp;

		}
	}
}

/***************************************************
Description : The purpose of this function is count
			the number of nodes in the queue to 
			determine the size.

precondition : none

postcondition : will return the size of the queue.
***************************************************/
template <class T>
int queue<T>::size()
{
	int size = 0;

	//calculate size if the queue is not empty
	if(queueFront != EMPTY) {

		size++;

		//used to traverse the queue
		queueNode<T> * trav_ptr = queueFront;

		while(trav_ptr->next_ptr != EMPTY) {

			trav_ptr = trav_ptr->next_ptr;
			size++;
		}
	}

	return size;
}

/***************************************************
Description : The purpose of this function is to 
			determine if the queue is empty or not.

precondition : none

postcondition : will return true if the queue is 
			empty, false otherwise.
***************************************************/
template <class T>			
bool queue<T>::is_empty()
{
	if(queueFront == EMPTY)
		return true;
	else
		return false;

}


//removes item with no return value
template <class T>
void queue<T>::deque()
{
	if(queueFront != EMPTY) {

		//delete if its the last node
		if(queueFront->next_ptr == EMPTY) {
			delete queueFront;
			queueFront = EMPTY;
			queue_back = EMPTY;
		}

		else {
			queueNode<T> * target = queueFront;
			queueFront = queueFront->next_ptr;
			target->next_ptr = EMPTY;

			delete target;
			target = EMPTY;
		}
	}	
}


/******************************************************
Description : prints queue if its not empty
******************************************************/
template <class T>
void queue<T>::printQueue()
{
	if (!this->is_empty())
	{
		queueNode<T> * march = queueFront;

		while(march != EMPTY) {
			cout << march->queueValue << endl;
			march = march->next_ptr;
		}
	}
}
/******************************************************
Description : this function returns the value of the 
			1st object of the queue
******************************************************/
template <class T>
T queue<T>::getFront()
{
	if (queueFront != EMPTY) {
		return queueFront->queueValue;	
	}
}