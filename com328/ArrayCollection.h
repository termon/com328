/*
* ArrayCollection.h
*
* Generic Collection based on an Array implementation
*
* @author  Aiden McCaughey
* @email   a.mccaughey@ulster.ac.uk
* @version 1.0
*
*/

#ifndef ARRAYCOLLECTION_H
#define ARRAYCOLLECTION_H

#include "Array.h"

template <class T>
class Collection
{
public:
	explicit Collection(int size=100);
	Collection(const Collection<T> & o);

	void add(const T & e);  
	bool remove(const T & e);
	bool find(const T & e) const;
	int size() const;
	int count(const T & e) const;
	void clear();
	bool isEmpty() const;

	Collection<T>& operator=(const Collection<T>& right);
	
	bool operator==(const Collection<T> & other) const;
	void print(std::ostream & out=std::cout ) const;

protected:
	Array<T> items;
	int      used;
};


/**
* Construct the Collection
*/
template <class T>
Collection<T>::Collection(int size) : items(size), used{ 0 } { }

template <class T>
Collection<T>::Collection(const Collection<T> & o) : items(o.items), used(o.used) { }


/**
* add element to Collection
* PreCondition:: none
* PostCondition: element added to Collection
*/
template <class T>
void Collection<T>::add(const T & e)
{        
	if (used == items.length()) {
		items.resize(used + (used/2));
	}
	items[used] = e;    // add item to end of array
	used++;             // increment count     
}

/**
* remove element from Collection if found.
* PreCondition: none
* PostCondition: returns true if element removed, false otherwise
*/
template <class T>
bool Collection<T>::remove(const T & e)
{
	for(int i=0; i<used; i++) {
		if (items[i] == e) {
			// move all elements from i to end of array down one space
			for(int p=i; p<used-1; p++) {
				items[p] = items[p+1];
			}
			used--;
			return true;
		}
	}
	return false;
}

/**
* Determine if  element is contained in Collection.
* PreCondition: none
* PostCondition: returns true if element found, false otherwise
*/
template <class T>
bool Collection<T>::find(const T & e) const
{
	for(int i=0; i<used; i++) {
		if (items[i] == e) {
			return true;
		}
	}
	return false;
}

/**
* return number of elements in Collection.
* PreCondition: none
*/
template <class T>
int Collection<T>::size() const
{
	return used;
}

/**
* return number of elements in Collection.
* PreCondition: none
*/
template <class T>
bool Collection<T>::isEmpty() const
{
	return used == 0;
}

/**
* return number of occurrences of element in Collection.
* PreCondition: none
*/
template <class T>
int Collection<T>::count(const T & e) const
{
	int count = 0;
	for(int i=0; i<used; i++) {
		if (items[i] == e) { count++; }
	}
	return count;
}

/**
* Empty the Collection
* PreCondition: None
* PostCondition: count() == 0
*/
template <class T>
void Collection<T>::clear() {
	used = 0;
}


/**
* print elements in Collection to specified output stream.
*/
template <class T>
void Collection<T>::print(std::ostream & out ) const
{
	out << "( ";
	for (int i = 0; i < used; i++) {
		out << items[i] << " ";
	}
	out << ")";
}

// PostCondition: returns true if other Collection contains exact same elements, otherwise false
template <class T>
bool Collection<T>::operator==(const Collection<T> & other) const 
{
	bool same=true;
	if (size() != other.size()) {
		same = false;
	}
	for(int i=0; same && i<size(); i++) {
		if (count(items[i]) != other.count(items[i])) {
			same = false;
		}
	} 
	return same;
}

// PostCondition: current Set overwritten by other
template <class T>
Collection<T> & Collection<T>::operator=(const Collection<T> & right) 
{
	if (this != &right) {
		// underling Array class assignment operator will be called
		items = right.items;
		used = right.used;
	}
	return *this;	
}

// PreCondition: None
// PostCondition: overload << operator to output Collection on ostream
template <class T>
std::ostream& operator <<(std::ostream& output, const Collection<T>& b) {
	b.print(output);
	return output;  // for multiple << operators.
}


#endif /* ARRAYCOLLECTION_H */
