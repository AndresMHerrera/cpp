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
#define EMPTY NULL
#define COUNT_INITIALIZER 0
using namespace std;

template <class T>
struct stack_node
{
	T stack_value;
	stack_node * back_ptr;
	stack_node(T inputStack_value, stack_node * top) 
	{
		stack_value = inputStack_value;
		back_ptr = top;
	}
};

template <class T>
class stack
{

public:

	stack();

	~stack();

	void push(T insert_value);

	void pop();

	bool is_empty();

	int size();

	T return_top();

	void print();
	
	T pop_return();

	private:
		stack_node<T> * stack_top;
};

#endif