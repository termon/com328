
/**
 * PriorityQueue.h
 * 
 * Generic PriorityQueue based on a MaxHeap implementation
 *
 * @author  Aiden McCaughey
 * @email   a.mccaughey@ulster.ac.uk
 * @version 1.0
 *
 */

#ifndef PRIORITYQUEUE_H_
#define PRIORITYQUEUE_H_

#include "BinaryHeap.h"

template <class T>
class PriorityQueue 
{
  public:
    PriorityQueue(int size=100);

    bool isEmpty( ) const;
    const T & peek( ) const;
    T dequeue( );
    void enqueue( const T & x );

  private:
    BinaryHeap<T> data;
};


/**
 * Construct the queue.
 */
template <class T>
PriorityQueue<T>::PriorityQueue(int size) : data(size) { }

/**
 * Test if the queue is logically empty.
 * Return true if empty, false, otherwise.
 */
template <class T>
bool PriorityQueue<T>::isEmpty( ) const
{
    return data.isEmpty();
}


/**
 * Get the least recently inserted item in the queue.
 * Return the least recently inserted item in the queue
 * or throw Underflow if empty.
 */
template <class T>
const T & PriorityQueue<T>::peek( ) const
{	
	return data.find();
}

/**
 * Return and remove the least recently inserted item from the queue.
 * Throw Underflow if empty.
 */
template <class T>
T PriorityQueue<T>::dequeue( )
{
    T tmp;
    data.deleteMin();
    return tmp;
}

/**
 * Insert x into the queue.
 */
template <class T>
void PriorityQueue<T>::enqueue( const T & x )
{
    data.insert(x);
}


#endif /* PRIORITYQUEUE_H_ */

