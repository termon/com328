/**
* Sorter.h
*
* Completed Template based Sorter class
*
* @author  Aiden McCaughey
* @email   a.mccaughey@ulster.ac.uk
* @version 2.1
*/

#ifndef SORTER_H_
#define SORTER_H_

#include "Array.h"
#include <fstream>
#include <cstdlib>

// ------------------------ Sorter Definition ------------------------
template <class T>
class Sorter
{
public:
	Sorter(int size = DEF_SIZE);

	// constructor initialises Sorter using specified Array
	Sorter(const Array<T> & other);

	// Note we can accept default C++ copy constructor and overloaded operator=
	// as our Sorter class does not contain any pointers nor perform memory allocation

	// return capacity of Sorter
	int capacity() const;

	// initialise sorter elements to default values
	void clear();

	// fill Sorter with random numbers
	void fillRandom(int range = 100);

	// return copy of Sorter elements
	Array<T> getElements() const;

	// search and sort algorithms
	int binarySearch(const T & element);
	void selectionSort();
	void insertionSort();
	void mergeSort();
	void quickSort();
	void shellSort();

	// Load and store elements in a text file
	void loadFile(const std::string & fname);
	void writeFile(const std::string & fname);

	// print elements to specified output stream
	void print(std::ostream & os) const;

private:

	void lswap(T &a, T &b);

	int qpartition(Array<T> & data, int low, int high);
	void qsort(Array<T> & data, int low, int high);

	void merge(Array<T> &, Array<T> &, int leftS, int rightS, int rightE);
	void divide(Array<T> &, Array<T> &, int left, int right);

	static const int DEF_SIZE = 10;
	Array<T> elements;
};

// --------------------------- Sorter Implementation -------------------

// PostCondition: creates a dynamic array of specified size
template <class T>
Sorter<T>::Sorter(int newSize) : elements(newSize) {}

// PostCondition: Sorter member variable 'elements' is initialised
//                with a copy of the specified Array
template <class T>
Sorter<T>::Sorter(const Array<T> & other) : elements(other) {}

// PostCondition: return capacity of Sorter
template <class T>
inline int Sorter<T>::capacity() const
{
	return elements.length();
}

// PostCondition: set all Array elements to default value of type T
template <class T>
void Sorter<T>::clear()
{
	elements.initialise();
}

// PostCondition: return a copy of the elements Array instance variable
//                note this invokes the Array copy constructor automatically
//                as we are returning a copy of the elements Array by value
template <class T>
Array<T> Sorter<T>::getElements() const
{
	return elements;
}

// PreCondition : elements must have been sorted
// PostCondition: return position if element found, otherwise -1
template <class T>
int Sorter<T>::binarySearch(const T & element)
{
	int left = 0, right = elements.length() - 1;

	while (left <= right) {
		int pivot = (left + right) / 2;
		std::cout << "Left=" << left << " Pivot=" << pivot << " Right=" << right << std::endl;
		if (elements[pivot] == element) {
			return pivot;     		// found
		}
		else {
			if (elements[pivot] < element)
				left = pivot + 1; 	// search right
			else
				right = pivot - 1; 	// search left
		}
	}
	return -1;

}

// PostCondition: collection elements are sorted
template <class T>
void Sorter<T>::selectionSort() {
	int min, moves = 0, comps = 0;

	for (int marker = 0; marker < elements.length() - 1; marker++) {
		min = marker;
		for (int i = marker + 1; i < elements.length(); i++) {
			comps++;
			if (elements[i] < elements[min])
				min = i;
		}
		// swap elements at position min and out
		moves += 3;
		lswap(elements[marker], elements[min]);
	}
	std::cout << "Selection sort : Comps: " << comps << " Moves: " << moves << std::endl;
}

template <class T>
void Sorter<T>::shellSort() {
	T temp;
	int in, out, h;
	int comps = 0, moves = 0;

	// calculate initial h value
	for (h = 1; h <= elements.length() / 3; h = h * 3 + 1);

	while (h >= 1) {  // n-sort until h=1
		for (out = h; out < elements.length(); out++) {
			temp = elements[out]; moves++;
			for (in = out; in > h - 1 && elements[in - h] >= temp; in -= h) {
				elements[in] = elements[in - h];
				comps++; moves++;			// one comp and one move on each iteration
			}
			comps++;						// final comp which terminates loop above
			elements[in] = temp; moves++;	// additional move
		}
		//std::cout << "H=" << h << " " << elements << std::endl;
		h = (h - 1) / 3; // decrease h
	}
	std::cout << "Shell sort : Comps: " << comps << " Moves: " << moves << std::endl;
}


// PostCondition: collection elements are sorted
template <class T>
void Sorter<T>::insertionSort() {
	int comps = 0, moves = 0;
	int in, out;
	T temp; // important to declare temp as type T
	for (out = 1; out < elements.length(); out++) {
		temp = elements[out]; 	 moves++;
		// find position for temp
		for (in = out; in > 0 && elements[in - 1] >= temp; in--) {
			elements[in] = elements[in - 1];
			comps++; moves++;			// one comp and one move on each iteration
		}
		comps++;						// final comp which terminates loop above
		elements[in] = temp; moves++;	// additional move
	}
	std::cout << "Insertion sort : Comps: " << comps << " Moves: " << moves << std::endl;
}


// PostCondition: elements sorted using merge sort algorithm
template <class T>
void Sorter<T>::mergeSort() {
	Array<T> work(elements.length());

	divide(work, elements, 0, elements.length() - 1);
}

// Private merge sort divide algorithm
template <class T>
void Sorter<T>::divide(Array<T> & work, Array<T> & data, int left, int right) {
	if (left < right) {
		int center = (left + right) / 2;
		divide(work, data, left, center);
		divide(work, data, center + 1, right);
		merge(work, data, left, center + 1, right);
	}
}

// Private merge sort merge algorithm
template <class T>
void Sorter<T>::merge(Array<T> & work, Array<T> & data,
	int leftS, int rightS, int rightE) {
	int leftE = rightS - 1;
	int tmpPos = leftS;
	int numElements = rightE - leftS + 1;

	// Main loop
	while (leftS <= leftE && rightS <= rightE) {
		if (data[leftS] < data[rightS])
			work[tmpPos++] = data[leftS++];
		else
			work[tmpPos++] = data[rightS++];
	}
	while (leftS <= leftE)    // Copy rest of left half
		work[tmpPos++] = data[leftS++];

	while (rightS <= rightE)  // Copy rest of right half
		work[tmpPos++] = data[rightS++];

	// Copy work back into data
	for (int i = 0; i < numElements; i++, rightE--)
		data[rightE] = work[rightE];
}


// PostCondition: elements sorted using quicksort
template <class T>
void Sorter<T>::quickSort() {
	qsort(elements, 0, elements.length() - 1);
}

// Private quicksort sorter method
template <class T>
void Sorter<T>::qsort(Array<T> & data, int low, int high) {
	int s; // Pivot location

	if (low < high) {
		s = qpartition(data, low, high);
		qsort(data, low, s - 1);
		qsort(data, s + 1, high);
	}
}


// private quicksort partition method arranges elements between
// [low..high] so that: elements smaller than pivot are placed before
// it and elements greater than pivot are placed after it.
template <class T>
int Sorter<T>::qpartition(Array<T> & data, int low, int high) {
	int s;		// start of sub-list (elements > pivot)
	int m;		// index into array
	T pivot;		// pivot value

	// pivot selected as first element in array positions low..high
	pivot = data[low];
	s = low;

	for (m = s + 1; m <= high; m++) {
		if (data[m] < pivot) {
			lswap(data[++s], data[m]);
		}
	}
	// put pivot in correct position
	swap(data[low], data[s]);
	return s;
}


// Private swap algorithm to swap two elements
template <class T>
void Sorter<T>::lswap(T& a, T& b) {
	T tmp = a;
	a = b;
	b = tmp;
}

// PostCondition: Sorter filled with max random numbers
template <class T>
void Sorter<T>::fillRandom(int range) {
	for (int i = 0; i < elements.length(); i++)
		elements[i] = rand() % range + 1; //convert to 1-range inclusive
}

// Post Condition: Print elements in Sorter to parameter ostream
//                 Could also have simply called the elements print
//                 method  e.g. elements.print(os);
template <class T>
void Sorter<T>::print(std::ostream & os) const {
	os << "{ ";
	for (int i = 0; i < elements.length(); i++) {
		os << elements[i] << " ";
	}
	os << "}";

}


// PostCondition: overloaded output operator means a Sorter object p
//                is printed to the specified output stream
template <class T>
std::ostream& operator <<(std::ostream& output, const Sorter<T>& p) {
	p.print(output); // call the sorters print method
	return output;  // for multiple << operators.
}

// PreCondition: named file exists and contains integers
// PostCondition: array is loaded with integers read from
//                file and array is resized if necessary
template <class T>
void Sorter<T>::loadFile(const std::string & fname) {
	std::ifstream in_stream;
	in_stream.open(fname.c_str());

	if (!in_stream.fail()) {
		T x;
		int i = 0;
		while (in_stream >> x) {
			if (i == elements.length())
				elements.resize(elements.length() * 2); // double size of array
			elements[i++] = x;
		}
		// resize array to i, to remove unused blanks
		if (i > 0) elements.resize(i);

		in_stream.close();
	}
}


// PreCondition: the specified file can be created
// PostCondition: each element in the sorter is written to
//                the file one element per line
template <class T>
void Sorter<T>::writeFile(const std::string & fname) {
	std::ofstream out_stream;

	out_stream.open(fname.c_str());
	if (!out_stream.fail()) {
		for (int i = 0; i < elements.length(); i++) {
			out_stream << elements[i];
			out_stream << std::endl;
		}
	}
	out_stream.close();
}

#endif
