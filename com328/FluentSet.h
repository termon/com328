/*
* FluentSet.h
*
* Generic FluentSet Collection based on a Set implementation
*
* @author  Aiden McCaughey
* @email   a.mccaughey@ulster.ac.uk
* @version 1.0
*
*/

#ifndef FluentSet_
#define FluentSet_

#include "Set.h"

template <class T>
class FluentSet : public Set<T>
{
public:
	FluentSet(int size=100) : Set<T>(size) {};
	FluentSet & add(const T & e);  
	FluentSet & remove(const T & e);
	FluentSet & clear();
};

// ---------------- FluentSet Implementation ---------------------

/**
* add element to Set
* PreCondition:: none
* PostCondition: element added to Set
*/
template <class T>
FluentSet<T> & FluentSet<T>::add(const T & e)
{    
	Set<T>::add(e);
	return *this;
}

/**
* remove element from Set if found.
* PreCondition: none
* PostCondition: returns true if element removed, false otherwise
*/
template <class T>
FluentSet<T> & FluentSet<T>::remove(const T & e)
{
	Set<T>::remove(e);
	return *this;
}


/**
* Empty the Set
* PreCondition: None
* PostCondition: count() == 0
*/
template <class T>
FluentSet<T> & FluentSet<T>::clear() {
	Set<T>::clear();
	return *this;
}

#endif /* FluentSet_ */
