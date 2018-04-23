/*
* ArraySet.h
*
* Generic Set based on a Collection class
*
* @author  Aiden McCaughey
* @email   a.mccaughey@ulster.ac.uk
* @version 1.0
*
*/

#ifndef SET_H
#define SET_H

#include "ArrayCollection.h"

template <class T>
class Set : public Collection<T>
{
public:
	explicit Set(int size=100) : Collection<T>(size) {};

	void add(const T & e);  
};


// PreCondition:: element is not contained in Set
// PostCondition: element added to Set if precondtion holds
template <class T>
void Set<T>::add(const T & e)
{        
	if (!Collection<T>::find(e)) {
		Collection<T>::add(e);
	}
}


#endif /* SET_H */
