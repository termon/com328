/**
 * FluentList.h
 *
 * Generic Fluent Dynamic List based on List
 *
 * @author  Aiden McCaughey
 * @email   a.mccaughey@ulster.ac.uk
 * @version 1.0
 */

#ifndef FLUENTLIST_H
#define FLUENTLIST_H

template <class T>
class FluentList : public ArrayList<T> {
public:
	explicit FluentList(int s=100) : ArrayList<T>(s) {};
    
    FluentList & clear();
    FluentList & add(int pos, const T & value);
	FluentList & add(const T & value);
    FluentList & remove(int pos);
    FluentList & set(int pos, const T & value);

};

// --------------- Fluent List Implementation -----------------------

// PreCondition: pos is a valid list position and list is not full
// PostCondition: inserts element value at specified position in list
template<class T>
FluentList<T> & FluentList<T>::add(int pos, const T & value) {
	ArrayList<T>::add(pos, value);
	return *this;
}

// PreCondition: pos is a valid list position and list is not full
// PostCondition: inserts element value at specified position in list
template<class T>
FluentList<T> & FluentList<T>::add(const T & value) {
	ArrayList<T>::add(value);
	return *this;
}

// PreCondition: pos is a valid list position
// PostCondition: updates element at specified position in list with value
template<class T>
FluentList<T> & FluentList<T>::set(int pos, const T & value) {
	ArrayList<T>::set(pos, value);
	return *this;
}


// PreCondition: pos is a valid list position
// PostCondition: remove element at specified position in  list
template<class T>
FluentList<T> & FluentList<T>::remove(int pos) {
	ArrayList<T>::remove(pos);
	return *this;
}


// PostCondition: list is emptied len == 0;
template<class T>
FluentList<T> & FluentList<T>::clear() {
	ArrayList<T>::clear();
	return *this;
}

#endif /* FLUENTLIST_H*/