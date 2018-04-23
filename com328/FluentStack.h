/**
 * FluentStack.h
 *
 * Generic Fluent Stack based on StackArray class
 *
 * @author  Aiden McCaughey
 * @email   a.mccaughey@ulster.ac.uk
 * @version 1.0
 */

#ifndef FLUENTSTACK_H
#define FLUENTSTACK_H

#include <exception>
#include "ArrayStack.h"

template <class T>
class FluentStack : public Stack<T>
{
public:
	FluentStack(int n=100) : Stack<T>(n) {}
	FluentStack & pop();
	FluentStack & push(const T & element);
	FluentStack & clear();
};


// ========================= IMPLEMENTATION FluentStack.cpp ===================================


// PreCondition: Stack is not empty
// PostCondition: removes top element from Stack
template <class T>
FluentStack<T> & FluentStack<T>::pop()
{
	Stack<T>::pop();
	return *this;
}


// PreCondition: Stack is not full
// PostCondition: Add specified element to top of stack
template <class T>
FluentStack<T> & FluentStack<T>::push(const T & element) 
{
	Stack<T>::push(element);
	return *this;
}

// PreCondition: None
// PostCondition: empty the stack
template <class T>
FluentStack<T> & FluentStack<T>::clear()
{
	Stack<T>::clear();
	return *this;
}

#endif /* FLUENTSTACK_H */
