/**
 * Sort.h
 *
 * Template based Sort functions
 *
 * @author  Aiden McCaughey
 * @email   a.mccaughey@ulster.ac.uk
 * @version 2.0
 */

#ifndef SORT_H_
#define SORT_H_

// when defined - debug info printed for each algorithm
//#define SORT_DEBUG_

#include "Array.h"

//  swap algorithm to swap two elements
template <class T>
void swap(T& a, T& b) {
    T tmp = a;
    a = b;
    b = tmp;
}

// PostCondition: collection elements are sorted
template <class T>
void selectionSort(Array<T> & elements) {
    int min, moves = 0, comps = 0;

    for (int marker = 0; marker < elements.length() - 1; marker++) {
        min = marker;
        for (int i = marker + 1; i < elements.length(); i++) {
            comps++;
			if (elements[i] < elements[min]) {
				min = i;
			}
        }
        // swap elements at position min and out
        moves += 3;
        swap<T>(elements[marker], elements[min]);

        #ifdef SORT_DEBUG_
        std::cout << "End of Pass " << (marker+1) << " " << elements << std::endl;
        #endif

    }
    #ifdef SORT_DEBUG_
    std::cout << "Selection sort : Comps: " << comps << " Moves: " << moves << std::endl;
    #endif
}

// PostCondition: collection elements are sorted
template <class T>
void bubbleSort(Array<T> & elements) {
    int moves =0, comps = 0;
    
    for (int i = 0 ; i < elements.length(); i++) {
        for (int e = 0 ; e < elements.length() - i - 1; e++) {
            comps++;
            // swap elements at positions e and e+1. For decreasing order use < */ 
            if (elements[e] > elements[e+1]) { 
                moves += 3;
                swap<T>(elements[e], elements[e+1]);
            }
        }
        #ifdef SORT_DEBUG_
        std::cout << "End of Pass " << (i+1) << " " << elements << std::endl;
        #endif
    }

    #ifdef SORT_DEBUG_
    std::cout << "Bubble sort : Comps: " << comps << " Moves: " << moves << std::endl;
    #endif
}

// PostCondition: collection elements are sorted
template <class T>
void insertionSort(Array<T> & elements) {
    int comps = 0, moves = 0;
    int in, out, temp;
    for (out = 1; out < elements.length(); out++) {
        temp = elements[out];
        moves++;
        // find position for temp
        for (in = out; in > 0 && elements[in - 1] >= temp; in--) {
            elements[in] = elements[in - 1];
            comps++;
            moves++; // one comp and one move on each iteration
        }
        comps++; // final comp which terminates loop above
        elements[in] = temp;
        moves++; // additional move
     
        #ifdef SORT_DEBUG_
        std::cout << "End of Pass " << out << " " << elements << std::endl;
        #endif
    }

    #ifdef SORT_DEBUG_
    std::cout << "Insertion sort : Comps: " << comps << " Moves: " << moves << std::endl;
    #endif
}


// PostCondition: elements sorted using merge sort algorithm

template <class T>
void mergeSort(Array<T> & elements) {
    Array<T> work(elements.length());

    divide(work, elements, 0, elements.length() - 1);
}

// Private merge sort divide algorithm

template <class T>
void divide(Array<T> & work, Array<T> & data, int left, int right) {
    if (left < right) {
        int center = (left + right) / 2;
        divide(work, data, left, center);
        divide(work, data, center + 1, right);
        merge(work, data, left, center + 1, right);
    }
}

// Private merge sort merge algorithm

template <class T>
void merge(Array<T> & work, Array<T> & data,
        int leftS, int rightS, int rightE) {
    int leftE = rightS - 1;
    int tmpPos = leftS;
    int numElements = rightE - leftS + 1;

    // Main loop
    while (leftS <= leftE && rightS <= rightE) {
        if (data[ leftS ] < data[ rightS ])
            work[ tmpPos++ ] = data[ leftS++ ];
        else
            work[ tmpPos++ ] = data[ rightS++ ];
    }
    while (leftS <= leftE) // Copy rest of left half
        work[ tmpPos++ ] = data[ leftS++ ];

    while (rightS <= rightE) // Copy rest of right half
        work[ tmpPos++ ] = data[ rightS++ ];

    // Copy work back into data
    for (int i = 0; i < numElements; i++, rightE--)
        data[ rightE ] = work[ rightE ];
}


// PostCondition: elements sorted using quicksort

template <class T>
void quickSort(Array<T> & elements) {
    qsort(elements, 0, elements.length() - 1);
}

// Private quicksort sorter method

template <class T>
void qsort(Array<T> & data, int low, int high) {
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
int qpartition(Array<T> & data, int low, int high) {
    int s; // start of sub-list (elements > pivot)
    int m; // index into array
    T pivot; // pivot value

    // pivot selected as first element in array positions low..high
    pivot = data[low];
    s = low;

    for (m = s + 1; m <= high; m++) {
        if (data[m] < pivot) {
            swap<T>(data[++s], data[m]);
        }
    }
    // put pivot in correct position
    swap<T>(data[low], data[s]);
    return s;
}

#endif	/* SORT_H */

