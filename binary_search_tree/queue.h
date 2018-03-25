/********************************************************************
* Author        :       Herrera, Andres
* File          :       queue.h
*
* Purpose :
*       This file contains all of the function prototypes
*       for the queue class. 
*
*********************************************************************/
#ifndef QUEUE_INCLUDED
#define QUEUE_INCLUDED

#include <iostream>
#define EMPTY NULL
#define NOT_VISITED false
#define VISITED true
using namespace std;

template <class T>
struct queueNode
{
	T queueValue;
	queueNode * next_ptr;

	queueNode(T insert_value) {
		queueValue = insert_value;
		next_ptr = EMPTY;
	}
};

template <class T>
class queue
{
	private: 
		queueNode<T> * queueFront;
		queueNode<T> * queue_back;

	public: 

		queue();

		~queue();

		void enque(T insert_value);

		//check if the queue is empty or not
		bool is_empty();

		//will delete front and returns the object deleted
		T deque_andReturn();

		void deque();	//removes item with no return value

		//will determine the size of the queue
		int size();

		void printQueue();

		T getFront();

};

#endif