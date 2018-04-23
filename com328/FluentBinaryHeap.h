/**
 * FluentStack.h
 *
 * Generic Fluent BinaryHeap based on BinaryHeap class
 *
 * @author  Aiden McCaughey
 * @email   a.mccaughey@ulster.ac.uk
 * @version 1.0
 */

#ifndef FLUENTBINARYHEAP_H_
#define FLUENTBINARYHEAP_H_

#include <exception>
#include "BinaryHeap.h"

template <class T>
class FluentBinaryHeap : public BinaryHeap<T>
{
public:
	FluentBinaryHeap( int capacity = 100 ) : BinaryHeap<T>(capacity) {};
	FluentBinaryHeap(const BinaryHeap<T> & other) : BinaryHeap<T>(other) {};
	FluentBinaryHeap(const Array<T> & other) : BinaryHeap<T>(other) {};

	FluentBinaryHeap & makeEmpty( );
	FluentBinaryHeap & deleteMin();
	FluentBinaryHeap & insert( const T & x );
	FluentBinaryHeap & buildHeap(const Array<T> & data);

};


// ========================= IMPLEMENTATION FluentBinaryHeap.cpp ===================================


/**
* Make the BinaryHeap logically empty.
*/
template <class T>
FluentBinaryHeap<T> & FluentBinaryHeap<T>::makeEmpty( )
{
	BinaryHeap<T>::makeEmpty();
	return *this;
}

template <class T>
FluentBinaryHeap<T> & FluentBinaryHeap<T>::deleteMin( )
{
	BinaryHeap<T>::deleteMin();
	return *this;
}


template <class T>
FluentBinaryHeap<T> & FluentBinaryHeap<T>::insert( const T & x )
{
	BinaryHeap<T>::insert(x);
	return *this;
}

template <class T>
FluentBinaryHeap<T> & FluentBinaryHeap<T>::buildHeap(const Array<T> & data)
{
	BinaryHeap<T>::buildHeap();
	return *this;
}


#endif /* FLUENTBINARYHEAP_H_ */
