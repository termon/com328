/**
 * Sequence.h
 *
 * Template based dynamic Sequence class, representing an unordered sequence
 *
 * @author  Aiden McCaughey
 * @email   a.mccaughey@ulster.ac.uk
 * @version 1.0
 */

#ifndef SEQUENCE_H_
#define SEQUENCE_H_

#include "Array.h"
#include  <cstdlib>

template <class T>
class Sequence
{
public:
	Sequence(int size=DEF_SIZE);

	int capacity() const;
	int count() const;
	bool isEmpty() const;
	void empty();

	void push_back(const T & element);
	T    pop_back();
	void erase(int pos);

	void insert(const T & element);
	bool remove(const T & element);
	void removeAll(const T & element);

	int search(const T & element);
	int binarySearch(const T & element);
	void sort();

	void print(std::ostream & os) const;

	void fillRandom(int max=100);

private:
	static const int DEF_SIZE=10;
	Array<T> elements;
	int used;

};

// PreCondition: None
// PostCondition: creates a dynamic array of specified size
template <class T>
Sequence<T>::Sequence(int newSize) : elements(newSize), used(0) {}

// PostCondition: return capacity of sequence
template <class T>
inline int Sequence<T>::capacity() const
{
	return elements.length();
}

// PostCondition: return number of elements in sequence
template <class T>
inline int Sequence<T>::count() const
{
	return used;
}

// PostCondition: sequence emptied of elements
template <class T>
void Sequence<T>::empty()
{
	used=0;
}

// PostCondition: return true if used==0, otherwise false
template <class T>
bool Sequence<T>::isEmpty() const
{
	return used==0;
}
// PostCondition: add element to end of sequence, resizing sequence if necessary
template <class T>
void Sequence<T>::push_back(const T & element)
{
	if (used >= elements.length())
		elements.resize(elements.length()+DEF_SIZE);

	elements[used] = element;
	++used;
}

// PreCondition : sequence is not empty
// PostCondition: add element to end of sequence, resizing sequence if necessary
template <class T>
T Sequence<T>::pop_back()
{
	assert(used > 0);

	T tmp = elements[count()-1];
	erase(count()-1);
	return tmp;
}

// PreCondition:  sequence is already in order (elements[i] < elements[i+1])
// PostCondition: add element to ordered position, resizing sequence if necessary
template <class T>
void Sequence<T>::insert(const T & element)
{
	// check if Sequence needs resized
	if (used >= elements.length()) {
		elements.resize(used+DEF_SIZE);
	}

	int pos;  // ordered position of element

	// find position
	for (pos=0; pos<used && element > elements[pos]; pos++);

	for(int i=used; i>pos; --i)		// move subsequent elements up
		elements[i] = elements[i-1];

	elements[pos]=element; 	// place element in hole

	++used; // increment used counter
}

// PostCondition: return position if element found, otherwise -1
template <class T>
int Sequence<T>::search(const T & element)
{
	for(int i=0; i<used; i++) {
		if (elements[i] == element) {
			return i;
		}
	}
	return -1;
}

template <class T>
void Sequence<T>::sort()
{
	Array<int> tmp = elements;
	int tmpused = used;

	// empty existing Sequence
	used = 0;

	for(int i=0; i<tmpused; i++)
		insert(tmp[i]);
}



// PreCondition : elements must have been added using insert
// PostCondition: return position if element found, otherwise -1
template <class T>
int Sequence<T>::binarySearch(const T & element)
{
	int left = 0, right = used-1;

	while (left <= right) {
      int pivot = (left + right) / 2;
	  std::cout << "Left=" << left << " Pivot=" << pivot << " Right=" << right << std::endl;
      if (elements[pivot] == element) {
          return pivot;     		// found
      } else {
          if (elements[pivot] < element)
             left = pivot + 1; 	// search right
          else
	       right = pivot - 1; 	// search left
      }
   }
   return -1;

}
// PreCondition: pos is valid
// PostCondition: element at pos is removed by moving subsequent elements down one position
template <class T>
void Sequence<T>::erase(int pos)
{
	assert(pos >=0 && pos < used);

	for(int i=pos; i<used; ++i)
		elements[i] = elements[i+1];

	--used;
}

// PostCondition: remove first occurance of specfied element from Sequence and return true
//                if element is not found do not modify sequence and return false
template <class T>
bool Sequence<T>::remove(const T & element)
{
	int pos = search(element); // find position of element to be removed
	if (pos == -1)
		return false;

	// fill hold left by deleted item
	for(int i = pos; i < used-1; ++i) {
		elements[i] = elements[i+1];
	}
	--used;  // decrement number of elements in sequence
	return true;
}

// PostCondition: element at pos is removed by moving subsequent elements down one position
template <class T>
void Sequence<T>::removeAll(const T & element)
{
	while (remove(element));
}


// PostCondition: sequence filled with max random numbers
template <class T>
void Sequence<T>::fillRandom(int max) {
	// empty sequence
	used = 0;

	// fill sequence with random numbers in range 0-max
	for(int i=0; i<elements.length(); i++)
		push_back(rand() % max);
}

// Post Condition: Print elements in sequence to parameter ostream
template <class T>
void Sequence<T>::print(std::ostream & os) const {
	os << "{ ";
	for(int i=0; i<used; i++) {
		os << elements[i] << " ";
	}
	os << "}";
}

template <class T>
std::ostream& operator <<(std::ostream& output, const Sequence<T>& p) {
    p.print(output);
    return output;  // for multiple << operators.
}

#endif
