/**
 * FluentTree.h
 *
 * Generic Fluent Dynamic Binary Tree
 *
 * @author  Aiden McCaughey
 * @email   a.mccaughey@ulster.ac.uk
 * @version 1.0
 */

#ifndef FLUENTTREE_H
#define FLUENTTREE_H

template <class T, class S>
class FluentTree : public S {
public:
	FluentTree() : S() {};
    
    FluentTree & clear();
	FluentTree & insert(const T & value);
    FluentTree & remove(int pos);

};

// --------------- Fluent List Implementation -----------------------


// PreCondition: pos is a valid list position and list is not full
// PostCondition: inserts element value at specified position in list
template<class T, class S>
FluentTree<T, S> & FluentTree<T, S>::insert(const T & value) {
	S::insert(value);
	return *this;
}

// PreCondition: pos is a valid list position
// PostCondition: remove element at specified position in  list
template<class T, class S>
FluentTree<T, S> & FluentTree<T, S>::remove(int pos) {
	S::remove(pos);
	return *this;
}

// PostCondition: list is emptied len == 0;
template<class T, class S>
FluentTree<T, S> & FluentTree<T, S>::clear() {
	S::clear();
	return *this;
}

#endif /* FluentTree_H*/