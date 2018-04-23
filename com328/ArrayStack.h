/**
 * ArrayStack.h
 *
 * Generic Stack based on Generic Array class
 *
 * @author  Aiden McCaughey
 * @email   a.mccaughey@ulster.ac.uk
 * @version 1.1
 */

#ifndef STACK_H
#define STACK_H

#include <exception>
#include "Array.h"

template <class T>
class Stack
{
public:
	explicit Stack(int n=100);
	void pop();
	T top() const;
	void push(const T & element);
	bool isEmpty() const;
	void clear();
	int size() const;

private:
	Array<T> data;
	int count;
};


// ========================= IMPLEMENTATION Stack.cpp ===================================

// PreCondition: None
// PostCondition: creates a Stack
template <class T>
Stack<T>::Stack(int n) : data(n), count{ -1 } { }


// PreCondition: Stack is not empty
// PostCondition: removes top element from Stack
template <class T>
void Stack<T>::pop()
{
	if (isEmpty()) {
		throw std::underflow_error("stack underflow");
	}
	else {
		count--;
	}
}

// PreCondition: Stack is not empty
// PostCondition: return a copy of top element from stack
template <class T>
T Stack<T>::top() const
{
	if (isEmpty()) {
		throw std::underflow_error("stack underflow");
	} 

	return data[count];		
}

// PreCondition: Stack is not full
// PostCondition: Add specified element to top of stack
template <class T>
void Stack<T>::push(const T & element) 
{
	if (count < data.length() - 1) {
		data[++count] = element;
	}
	else {
		throw std::overflow_error("stack overflow");
	}
}

// PreCondition: None
// PostCondition: return true if stack is empty and false otherwise
template <class T>
bool Stack<T>::isEmpty() const
{
	return count == -1;
}

// PreCondition: None
// PostCondition: empty the stack
template <class T>
void Stack<T>::clear()
{
	count = -1;
}

// PreCondition: None
// PostCondition: return number of entries on stack
template <class T>
int Stack<T>::size() const
{
	return count + 1;
}

#endif /* STACK_H */
