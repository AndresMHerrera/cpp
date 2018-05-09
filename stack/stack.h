/********************************************************************
* Author        :       Herrera, Andres
* File          :       stack.h
*
* Purpose :
*       This file contains all of the function prototypes
*       for the stack class. 
*
*********************************************************************/
#ifndef STACK_INCLUDED
#define STACK_INCLUDED

#include <iostream>
#define COUNT_INITIALIZER 0
using namespace std;

template <class T>
struct stack_node
{
	T stack_value;
	stack_node *back_ptr;
	stack_node(T inputStack_value, stack_node *top)
	{
		stack_value = inputStack_value;
		back_ptr = top;
	}
};

template <class T>
class Stack
{
  public:
	Stack();
	~Stack();

	void push(T item);
	void pop();
	T peek();
	bool isEmpty();
	int size();

  private:
	// stack_node<T> * stack_top;
	stack_node<T> * top;
	int count;
};

#endif