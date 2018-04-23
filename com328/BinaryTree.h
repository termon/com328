/**********************************************************************
* Name        : BinaryTree.h
* Author      : a.mccaughey@ulster.ac.uk
* Version     : 1.0
* Description : Dynamic BinarySearch Tree class with public BinNode
*********************************************************************/
#ifndef BinaryTree_H_
#define BinaryTree_H_
#include "Array.h"
#include <cstdlib>
#include <fstream>

template <class T>
struct BinNode {
	BinNode(T d = T(), BinNode<T>* l = nullptr, BinNode<T>* r = nullptr) :
		data(d), left(l), right(r) {}

	T		    data;
	BinNode<T> *left;
	BinNode<T> *right;
};

template <class T>
class BinaryTree {
public:
	BinaryTree();
	~BinaryTree();
	BinaryTree(const BinaryTree<T>& t);
	const BinaryTree& operator=(const BinaryTree<T>& rhs);

	void insert(const T & e);
	void clear();
	void remove(const T & e);
	bool find(const T & e) const;
	void displayInOrder(std::ostream & os = std::cout) const;
	void displayPreOrder(std::ostream & os = std::cout) const;
	void displayPostOrder(std::ostream & os = std::cout) const;

	bool isEmpty() const;

	void load(const std::string & fname);
	void loadFrom(const Array<T> & a);
	void extractTo(Array<T> & a);

	int size() const;
	int height() const;

private:
	BinNode<T>* root;
	int tsize;

	BinNode<T>*	insert(const T & e, BinNode<T>* n);
	BinNode<T>*	remove(const T & e, BinNode<T>* n);
	bool		find(const T & e, BinNode<T>* n) const;
	void        displayInOrder(BinNode<T>* n, std::ostream & os) const;
	void        displayPreOrder(BinNode<T>* n, std::ostream & os) const;
	void        displayPostOrder(BinNode<T>* n, std::ostream & os) const;

	BinNode<T>* findMin(BinNode<T>* n) const;
	void        clear(BinNode<T>* n);
	BinNode<T>* copy(BinNode<T>* n);
	int         subTreeHeight(BinNode<T>* n) const;

	void extractTo(Array<T> & a, int & pos, BinNode<T>* n);
};


// ========================= IMPLEMENTATION BinaryTree.cpp ===================================

// Constructor: initialises empty binary tree
template <class T>
BinaryTree<T>::BinaryTree() : root(nullptr), tsize(0) { }

// Copy Constructor: initialises BinaryTree from Tree passed as const parameter
template <class T>
BinaryTree<T>::BinaryTree(const BinaryTree<T> & t) {
	root = copy(t.root);
	tsize = t.tsize;
}

// Destructor: deletes binary tree
template <class T>
BinaryTree<T>::~BinaryTree() {
	clear();
}

// Pre Condition: none
// PostCondition: element e is inserted into the tree
template <class T>
void BinaryTree<T>::insert(const T & e) {
	root = insert(e, root);
	tsize++;
}

// Pre Condition: none
// PostCondition: the contents of the tree are deleted
template <class T>
void BinaryTree<T>::clear() {
	clear(root);
	root = nullptr;
	tsize = 0;
}

// Pre Condition: none
// PostCondition: the element e is deleted from the tree if contained in the tree
//                otherwise the tree is unchanged
template <class T>
void BinaryTree<T>::remove(const T & e) {
	root = remove(e, root);
	tsize--;
}

// Pre Condition: none
// PostCondition: returns boolean result of searching for the element e in the tree
template <class T>
bool BinaryTree<T>::find(const T & e) const {
	return find(e, root);
}


// Pre Condition: none
// PostCondition: returns true if the tree is empty and false otherwise
template <class T>
bool BinaryTree<T>::isEmpty() const {
	return (root == nullptr);
}

// Pre Condition: none
// PostCondition: print elements of tree in sorted order
template <class T>
void BinaryTree<T>::displayInOrder(std::ostream & os) const {
	os << "[ ";
	displayInOrder(root, os);
	os << "]";
}
template <class T>
void BinaryTree<T>::displayPreOrder(std::ostream & os) const {
	os << "[ ";
	displayPreOrder(root, os);
	os << "]";
}
template <class T>
void BinaryTree<T>::displayPostOrder(std::ostream & os) const {
	os << "[ ";
	displayPostOrder(root, os);
	os << "]";
}

// Pre Condition: none
// PostCondition: return the number of elements contained in the tree
template <class T>
int BinaryTree<T>::size() const {
	return tsize;
}

// Pre Condition: none
// PostCondition: return the number of levels in the tree	
template <class T>
int BinaryTree<T>::height() const {
	return subTreeHeight(root);
}

// Pre Condition: none
// PostCondition: creates and returns a copy of the tree rhs
template <class T>
const BinaryTree<T>& BinaryTree<T>::operator=(const BinaryTree<T>& rhs) {
	if (this != &rhs) {
		clear();
		root = copy(rhs.root);
		tsize = rhs.tsize;
	}
	return *this;
}



// ================== PRIVATE METHODS ============================= //

// Pre Condition: none
// PostCondition: return height of tree whose root is 'n' 	
template <class T>
int BinaryTree<T>::subTreeHeight(BinNode<T>* n) const {
	if (n == nullptr) {
		return 0;
	}
	else {
		int hl = subTreeHeight(n->left);
		int hr = subTreeHeight(n->right);
		if (hl > hr) {
			return 1 + hl;
		}
		else {
			return 1 + hr;
		}
	}
}

// Pre Condition: none
// PostCondition: return reference to root of copy of tree whose root is 'n'
template <class T>
BinNode<T>* BinaryTree<T>::copy(BinNode<T>* n) {
	BinNode<T>* t;
	if (n == nullptr) {
		t = nullptr;
	}
	else {
		// t = new BinNode<T>(n->data, copy(n->left), copy(n->right);
		t = new BinNode<T>();
		t->data = n->data;
		t->left = copy(n->left);
		t->right = copy(n->right);
	}
	return t;
}


// Pre Condition: none
// PostCondition: delete elements from tree whose root is 'n'
template <class T>
void BinaryTree<T>::clear(BinNode<T>* n) {
	if (n != nullptr) {
		clear(n->left);
		clear(n->right);
		delete n;
		n = nullptr; // just to be sure!!
	}
}


// Pre Condition: none
// PostCondition: return reference to node containing smallest element in tree whose root is 'n'
template <class T>
BinNode<T>* BinaryTree<T>::findMin(BinNode<T>* n) const {
	if (n == nullptr) {
		return nullptr;
	}
	else if (n->left == nullptr) {
		return n;
	}
	else {
		return findMin(n->left);
	}
}


// Pre Condition: none
// PostCondition: print contents of tree on stdout in sorted order
template <class T>
void BinaryTree<T>::displayInOrder(BinNode<T>* n, std::ostream & os) const {
	if (n != nullptr) {
		displayInOrder(n->left, os);
		os << n->data << " ";
		displayInOrder(n->right, os);
	}
}
template <class T>
void BinaryTree<T>::displayPreOrder(BinNode<T>* n, std::ostream & os) const {
	if (n != nullptr) {
		os << n->data << " ";
		displayPreOrder(n->left, os);
		displayPreOrder(n->right, os);
	}
}
template <class T>
void BinaryTree<T>::displayPostOrder(BinNode<T>* n, std::ostream & os) const {
	if (n != nullptr) {
		displayPostOrder(n->left, os);
		displayPostOrder(n->right, os);
		os << n->data << " ";
	}
}

// Pre Condition: none
// PostCondition: return reference to tree updated by inserting element 'e' into tree whose root is 'n'
template <class T>
BinNode<T>* BinaryTree<T>::insert(const T & e, BinNode<T>* n) {
	if (n == nullptr) {
		n = new BinNode<T>(e, nullptr, nullptr);
	}
	else if (e < n->data) {
		n->left = insert(e, n->left);
	}
	else if (e >= n->data) {
		n->right = insert(e, n->right);
	}
	return n;
}


// Pre Condition: none
// PostCondition: return reference to tree updated by removing element 'e' from tree whose root is 'n'
template <class T>
BinNode<T>* BinaryTree<T>::remove(const T & e, BinNode<T>* n) {
	BinNode<T> *tmp = n;
	if (n == nullptr) {
		return n;
	}
	else if (e < n->data) {
		n->left = remove(e, n->left);
	}
	else if (e > n->data) {
		n->right = remove(e, n->right);
	}
	else if (n->left != nullptr && n->right != nullptr) {
		BinNode<T>* succ = findMin(n->right);
		n->data = succ->data;
		n->right = remove(succ->data, n->right);
	}
	else if (n->left == nullptr) {
		n = n->right;
		delete tmp;
	}
	else {
		n = n->left;
		delete tmp;
	}
	return n;
}


// Pre Condition: none
// PostCondition: return true if element 'e' is found in tree whose root is 'n', false otherwise
template <class T>
bool BinaryTree<T>::find(const T & e, BinNode<T>* n) const {
	/* if (n == nullptr) {
	return false;
	} else if (e == n->data) {
	return true;
	} else if (e < n->data) {
	return find(e, n->left);
	} else {
	return find(e, n->right);
	}
	*/
	while (n != nullptr) {
		if (e == n->data)
			return true;
		else if (e < n->data)
			n = n->left;
		else
			n = n->right;
	}
	return false;
}

template <class T>
void BinaryTree<T>::load(const std::string & fname) {
	std::ifstream in_stream;
	in_stream.open(fname.c_str());

	clear(); // remove any existing entries

	if (!in_stream.fail()) {
		T x;
		while (in_stream >> x) {
			insert(x); // add entry to dictionary
		}
		in_stream.close();
	}
}

template <class T>
void BinaryTree<T>::loadFrom(const Array<T> & a) {
	clear();
	for (int i = 0; i<a.length(); i++)
		insert(a[i]);
}

template <class T>
void BinaryTree<T>::extractTo(Array<T> & a) {
	int start = 0;
	extractTo(a, start, root);
}

template <class T>
void BinaryTree<T>::extractTo(Array<T> & a, int & pos, BinNode<T>* n) {
	if (n != nullptr) {
		extractTo(a, pos, n->left);
		a[pos++] = n->data;
		extractTo(a, pos, n->right);
	}
}


#endif /*BinaryTree_H_*/
