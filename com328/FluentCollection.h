/*
* FluentCollection.h
*
* Generic FluentCollection Collection based on an ArrayCollection implementation
*
* @author  Aiden McCaughey
* @email   a.mccaughey@ulster.ac.uk
* @version 1.0
*
*/

#ifndef FLUENTCOLLECTION_
#define FLUENTCOLLECTION_

#include "ArrayCollection.h"

template <class T>
class FluentCollection : public Collection<T>
{
public:
	FluentCollection() : Collection<T>() {};
	FluentCollection(int size) : Collection<T>(size) {};
	FluentCollection & add(const T & e);  
	FluentCollection & remove(const T & e);
	FluentCollection & clear();
};



/**
* add element to Collection
* PreCondition:: none
* PostCondition: element added to Collection
*/
template <class T>
FluentCollection<T> & FluentCollection<T>::add(const T & e)
{    
	Collection<T>::add(e);
	return *this;
}

/**
* remove element from Collection if found.
* PreCondition: none
* PostCondition: returns true if element removed, false otherwise
*/
template <class T>
FluentCollection<T> & FluentCollection<T>::remove(const T & e)
{
	Collection<T>::remove(e);
	return *this;
}


/**
* Empty the Collection
* PreCondition: None
* PostCondition: count() == 0
*/
template <class T>
FluentCollection<T> & FluentCollection<T>::clear() {
	Collection<T>::clear();
	return *this;
}

#endif /* FLUENTCOLLECTION_ */
