/**********************************************************************
 * Name        : DoubleLinkedList.h
 * Author      : a.mccaughey@ulster.ac.uk
 * Version     : 1.4
 * Description : Dynamic Doubly Linked List class with public DNode
 *               and error checking using exceptions
 *********************************************************************/

#ifndef DOUBLELINKEDLIST_H
#define DOUBLELINKEDLIST_H

#include <cstdlib> // Defines NULL
#include <iostream>
#include <exception>

// =============================== LIST DNode ==============================================
// DNode Class Used as Building Blocks of a Doubly Linked List
template <class T>
struct DNode {
	DNode(const T & d=T(), DNode<T> *p=nullptr, DNode<T> *n=nullptr) : data(d), prev(p), next(n) {};

	T data;
	DNode* prev;
	DNode* next;
};
	
// ============================= LIST ITERATOR ============================================
// List Iterator Class , used to efficiently traverse through a List
template <class T>
class DListIterator {
	public:
		DListIterator(DNode<T> *start=nullptr) : current(start)	{}
		DListIterator & operator=(const DListIterator & o)	{ current = o.current; return (*this); }
		T & operator*()										{ return current->data; }
		DListIterator & operator++()						{ current = current->next; return *(this);}
		DListIterator operator++(int)						{ DListIterator tmp(*this); ++(*this); return tmp; }
		DListIterator & operator--()						{ current = current->prev; return *(this);}
		DListIterator operator--(int)						{ DListIterator tmp(*this); --(*this); return tmp; }
		bool operator!=(const DListIterator & o)			{ return current != o.current; }
		bool operator==(const DListIterator & o)			{ return current == o.current; }
	private:
		DNode<T> *current;
};

// ============================== LINKED LIST ===========================================
template <class T>
class DLinkedList {
public:
	DLinkedList(int n=10);
    virtual ~DLinkedList();
    DLinkedList(const DLinkedList<T> & c);
	void operator=(const DLinkedList<T> & c);
	bool operator==(const DLinkedList<T> & o) const;
	
    void clear();
	void add(const T & value);
    void add(int pos, const T & value);
    void remove(int pos);
    void set(int pos, const T & value);
    T    get(int pos) const;
    int  size() const;
    bool isEmpty() const;

    void print(std::ostream & os) const;
    int  find(const T & value) const;
	
	DListIterator<T> begin()		{ return DListIterator<T>(header->next); }
	DListIterator<T> end()			{ return DListIterator<T>(header); }
	DListIterator<T> begin() const	{ return DListIterator<T>(header->next); }
	DListIterator<T> end()   const	{ return DListIterator<T>(header); }

private:
    DNode<T> *DNodeAt(int pos) const;
	void addBefore(const T & e, DNode<T> *p);
	void deepCopy(const DLinkedList<T> & c);

	DNode<T> *header;
	int		count;
};


// ----------------- Double LinkedList Implementation ----------------

// Default Constructor
template <class T>
DLinkedList<T>::DLinkedList(int n) { // dummy size for compatability with ArrayList
	header = new DNode<T>();
  	header->prev = header;	
  	header->next = header;
	count = 0;
}


// Destructor
template <class T>
DLinkedList<T>::~DLinkedList() {
	clear();		// delete DNodes
	delete header;	// delete header
}


// PreCondition: c is not null
// PostCondition: copy constructor
template <class T>
DLinkedList<T>::DLinkedList(const DLinkedList& c) {
    // initialise the header DNode
    header = new DNode<T>;
	header->prev = header;	
  	header->next = header;
	count = 0;
	deepCopy(c);
}


// PreCondition: c is not null
// PostCondition: overloaded assignment operator
template <class T>
void DLinkedList<T>::operator=(const DLinkedList<T> & c) {
	clear();		// clear existing DLinkedList
	deepCopy(c);	// perform a deep copy
}

// PostCondition: test DLinkedLists for equality
template<class T>
bool DLinkedList<T>::operator==(const DLinkedList<T> & o) const {
	bool same=true;
	if (size() != o.size()) {
		same = false;
	}

	for(int i=0; i<size() && same; i++) {
		if (get(i) != o.get(i)) {
			same = false;
		}
	}
	return same;
}

// PreCondition: c is not null  
// PostCondition: perform a deep copy of c
template <class T>
void DLinkedList<T>::deepCopy(const DLinkedList<T> & c) {
    DNode<T>* p = header;	// previous DNode pointer
    DNode<T>* n;				// new DNode pointer
    for(DListIterator<T> itr = c.begin(); itr != c.end(); ++itr) {
        n = new DNode<T>(*itr, p, p->next); // create new DNode
        n->prev->next = n;		// set last next to refer to n
        n->next->prev = n;		// set last prev to n
		p = n;					// move p to new DNode
    }
	count = c.count;		// copy count
}

// PreCondition:  none
// PostCondition: return size of DLinkedList
template <class T>
int DLinkedList<T>::size() const{
	return count;
}

// PreCondition:  none
// PostCondition: inserts element value at specified postion in DLinkedList
template <class T>
void DLinkedList<T>::add(int pos, const T & value) {
	if (pos < 0 || pos > size()) {
		throw std::out_of_range("DLinkedList invalid position: " + std::to_string(pos));
	}
	
	addBefore(value, (pos==count ? header : DNodeAt(pos)));
}

// PostCondition: inserts element value at end of DLinkedList
template<class T>
void DLinkedList<T>::add(const T & value) {
	add(size(),value);
}


// Post-Condition: Insert element before specified DNode  
template <class T>
void DLinkedList<T>::addBefore(const T & e, DNode<T> *p) {
	DNode<T> *n = new DNode<T>(e, p->prev, p);
	n->prev->next = n;
	n->next->prev = n;
	count++;
}

// PreCondition:  none
// PostCondition: deletes DNode at specified postion in DLinkedList
template <class T>
void DLinkedList<T>::remove(int pos) {
	if (pos < 0 || pos >= size()) {
		throw std::out_of_range("DLinkedList invalid position: " + std::to_string(pos));
	}
	DNode<T> *d = DNodeAt(pos);		// locate DNode to delete
	d->prev->next = d->next;		// disconnect DNode
	d->next->prev = d->prev;
	delete d;
  	count--;
}


// PostCondition: returns index of DLinkedList item if found or -1 if not found
template<class T>
int DLinkedList<T>::find(const T & value) const {
	int i=0;
	for (DListIterator<T> itr = begin(); itr != end(); itr++, i++) {
		if ((*itr) == value) {
			return i;
		}
	}
	return -1;
}

// PreCondition:  none
// PostCondition: deletes DNode at specified postion in linked DLinkedList
template <class T>
T DLinkedList<T>::get(int pos) const {
	if (pos < 0 || pos >= size()) {
		throw std::out_of_range("DLinkedList invalid position: " + std::to_string(pos));
	}
	return DNodeAt(pos)->data;
}

// PreCondition:  none
// PostCondition: updates value part of DNode at specified postion in linked DLinkedList
template <class T>
void DLinkedList<T>::set(int pos, const T & value) {
	if (pos < 0 || pos >= size()) {
		throw std::out_of_range("DLinkedList invalid position: " + std::to_string(pos));
	}
	// set data element of note at pos to new value
	DNodeAt(pos)->data = value;
}


// PreCondition:  none
// PostCondition: prints DLinkedList to output stream using an iterator
template <class T>
void DLinkedList<T>::print(std::ostream & os) const {
	os << "[ ";
 	for(DListIterator<T> itr = begin(); itr != end(); ++itr) {
		os << *itr << " ";
	}
	os << "]";
}

// PreCondition:  pos is valid and DLinkedList is not empty
// PostCondition: returns reference to DNode at specified position
template <class T>
DNode<T>* DLinkedList<T>::DNodeAt(int pos) const {	
	DNode<T> *n = header;
	for (int i = 0; i <= pos; i++) {
		n = n->next;
	}
    return n;
}

// Post-Condition: DLinkedList is emptied
template <class T>
void DLinkedList<T>::clear() {
	DNode<T> *tmp, *d;
	
	tmp = header->next;
	// while we have not returned to the header
	while (tmp != header) { 	
		d = tmp; 			// set d to refer to DNode to be deleted
		tmp = tmp->next; 	// move tmp on to next DNode
		delete d;			// delete DNode refered to by d
	}
	header->next = header;  // reset header
	header->prev = header;
	count = 0;				// reset count to zero	

	//  for(int i=size()-1; i>=0; i--)
	//  	remove(i);
	//  return;
}

template <class T>
bool DLinkedList<T>::isEmpty() const {
	return (count == 0);
}

// PreCondition: None
// PostCondition: overload << operator to output DLinkedList on ostream
template <class T>
std::ostream& operator <<(std::ostream& output, const DLinkedList<T>& l) {
    l.print(output);
    return output;  // for multiple << operators.
}

#endif /* DOUBLEDLINKEDLIST_H */
