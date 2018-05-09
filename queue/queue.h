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
// #define EMPTY NULL
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
		next_ptr = NULL;
	}
};

template <class T>
class queue
{
	private: 
		queueNode<T> * front;
		queueNode<T> * back;
		int count;

	public: 

		queue();
		~queue();
		void enque(T item);
		void deque();
		T peek();
		bool isEmpty();
		int size();
};

#endif