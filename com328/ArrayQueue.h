/**
 * ArrayQueue.h
 * 
 * Generic Queue based on circular Array implementation
 * with exception handling for underflow and overflow
 *
 * @author  Aiden McCaughey
 * @email   a.mccaughey@ulster.ac.uk
 * @version 1.1
 *
 */

#ifndef _ARRAYQUEUE_H
#define _ARRAYQUEUE_H

#include <exception>
#include "Array.h"

template <class T>
class Queue {
public:
    explicit Queue(int n=100);

	T peek() const;
    void dequeue();
    void enqueue(const T & x);
    void clear();

	bool isEmpty() const;
    int size() const;

private:
    Array<T> data;
    int count;
    int front;
    int back;
};

// ========================= IMPLEMENTATION Stack.cpp ===================================

// PostCondition: empty queue initialised
template <class T>
Queue<T>::Queue(int n) : data(n), count{ 0 }, front{ 0 }, back{ data.length() - 1 } {}

// PostCondition: Return true if empty, false, otherwise.
template <class T>
bool Queue<T>::isEmpty() const {
    return (count == 0);
}

// PostCondition: return number of elements in the queue
template <class T>
int Queue<T>::size() const {
    return count;
}

// PostCondition: make the queue logically empty.
template <class T>
void Queue<T>::clear() {
    count = 0;
    front = 0;
    back = data.length() - 1;
}

// PreCondition: the queue is not empty
// PostCondition: return the least recently inserted item in the queue.
template <class T>
T Queue<T>::peek() const {
	// check for underflow
	if (size() < 1) {
		throw std::underflow_error("queue underflow");
	}
	return data[ front ];
}


// PreCondition: the queue is not empty
// PostCondition: remove the least recently inserted item in the queue.
template <class T>
void Queue<T>::dequeue() {
	// check for underflow
	if (size() < 1) {
		throw std::underflow_error("queue underflow");
	}
	front = (front + 1) % data.length();
	count--;
}

// PreCondition: the queue is not full
// PostCondition: element is added to end of the queue
template <class T>
void Queue<T>::enqueue(const T & x) {
	// check for overflow
	if (size() >= data.length()) {
		throw std::overflow_error("queue overflow");
	}
    back = (back + 1) % data.length();
    data[ back ] = x;
    count++;
}

#endif /* _ARRAYQUEUE_H */

