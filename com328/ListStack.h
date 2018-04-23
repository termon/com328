/**
 * ListStack.h
 *
 * Generic Stack based on Generic ArrayList class
 *
 * @author  Aiden McCaughey
 * @email   a.mccaughey@ulster.ac.uk
 * @version 1.0
 */

#ifndef LISTSTACK_H
#define LISTSTACK_H

#include <exception>
#include "ArrayList.h"

template <class T>
class Stack
{
public:
	Stack(int size);
	void pop();
	T top() const;
	void push(const T & element);
	bool isEmpty() const;
	void clear();

private:
	ArrayList<T> data;
};


// ========================= IMPLEMENTATION ListStack.cpp ===================================

// PreCondition: None
// PostCondition: creates a Stack
template <class T>
Stack<T>::Stack(int size) : data(size) { }


// PreCondition: Stack is not empty
// PostCondition: removes top element from Stack
template <class T>
void Stack<T>::pop()
{
	if (!data.isEmpty())
		data.remove(data.size()-1);
	else
		throw std::underflow_error("stack underflow");
}

// PreCondition: Stack is not empty
// PostCondition: return a copy of top element from stack
template <class T>
T Stack<T>::top() const
{
	if (!data.isEmpty())
		return data.get(data.size()-1);
	else
		throw std::underflow_error("stack underflow");
}


// PreCondition: Stack is not full
// PostCondition: Add specified element to top of stack
template <class T>
void Stack<T>::push(const T & element) 
{
		data.add(data.size(),element);
}

// PreCondition: None
// PostCondition: return true if stack is empty and false otherwise
template <class T>
bool Stack<T>::isEmpty() const
{
	return data.isEmpty();
}

// PreCondition: None
// PostCondition: empty the stack
template <class T>
void Stack<T>::clear()
{
	data.clear();
}

#endif /* LISTSTACK_H */
