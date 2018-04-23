
/**
 * FluentQueue.h
 * 
 * Generic Fluent Queue based on ArrayQueue
 *
 * @author  Aiden McCaughey
 * @email   a.mccaughey@ulster.ac.uk
 * @version 1.0
 *
 */

#ifndef _FLUENTQUEUE_H
#define _FLUENTQUEUE_H

#include "ArrayQueue.h"

template <class T>
class FluentQueue : public Queue<T> {
public:
	FluentQueue(int n=100) : Queue<T>(n) {};

    FluentQueue & dequeue();
    FluentQueue & enqueue(const T & value);
    FluentQueue & clear();
};

/**
 * Make the queue logically empty.
 */
template <class T>
FluentQueue<T> & FluentQueue<T>::clear() {
	Queue<T>::clear();
	return *this;
}


/**
 * Return and remove the least recently inserted item from the queue.
 * Throw Underflow if empty.
 */
template <class T>
FluentQueue<T> & FluentQueue<T>::dequeue() {
	Queue<T>::dequeue();
	return *this;
}

/**
 * Insert x into the queue
 * Throw overflow if full.
 */
template <class T>
FluentQueue<T> & FluentQueue<T>::enqueue(const T & value) {
	Queue<T>::enqueue(value);
	return *this;
}


#endif /* _FLUENTQUEUE_H */

