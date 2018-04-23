/*
 * Collection.h
 *
 * Generic Collection based on a List implementation
 *
 * @author  Aiden McCaughey
 * @email   a.mccaughey@ulster.ac.uk
 * @version 1.0
 *
 */

#ifndef Collection_H
#define Collection_H

#include "ArrayList.h"

template <class T>
class Collection
{
  public:
    Collection();

    void add(const T & e);  
    bool remove(const T & e);
    bool find(const T & e) const;
    int count() const;
    int count(const T & e) const;
    void clear();

    bool operator==(const Collection<T> & other) const;
    void print(std::ostream & out ) const;

  private:
    ArrayList<T> items;
    int      used;
};


/**
 * Construct the Collection
 */
template <class T>
Collection<T>::Collection() : items(), used(0) { }

/**
 * add element to Collection
 * PreCondition:: none
 * PostCondition: element added to Collection
 */
template <class T>
void Collection<T>::add(const T & e)
{        
    items.add(used,e);    // add item to end of list
	used++;               // increment count     
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
        if (items.get(i) == e) {
            items.remove(i);
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
        if (items.get(i) == e) {
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
int Collection<T>::count() const
{
	return used;
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
        if (items.get(i) == e) count++;
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
    items.clear();
}


/**
 * print elements in Collection to specified output stream.
 */
template <class T>
void Collection<T>::print(std::ostream & out ) const
{
	out << "( ";
	for(int i=0; i<used; i++)
		out << items.get(i) << " ";
	out << ")";
}

// PostCondition: returns true if other Collection contains exact same elements, otherwise false
template <class T>
bool Collection<T>::operator==(const Collection<T> & other) const 
{
    bool same=true;
    if (count() != other.count()) {
        same = false;
    }
    for(int i=0; same && i<count(); i++) {
        if (count(items.get(i)) != other.count(items.get(i))) {
            same = false;
        }
    } 
    return same;
}


// PreCondition: None
// PostCondition: overload << operator to output Collection on ostream
template <class T>
std::ostream& operator <<(std::ostream& output, const Collection<T>& b) {
    b.print(output);
    return output;  // for multiple << operators.
}


#endif /* Collection_H */

