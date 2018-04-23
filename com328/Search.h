/**
 * Search.h
 *
 * Template based Search Functions
 *
 * @author  Aiden McCaughey
 * @email   a.mccaughey@ulster.ac.uk
 * @version 2.0
 */

#ifndef SEARCH_H_
#define SEARCH_H_

// when defined - debug info printed for each algorithm
//#define SEARCH_DEBUG_

#include "Array.h"


// PreCondition: data array is full
// PostCondition: return true if array elements are in sorted order, otherwise false
template <class T>
bool isOrdered(const Array<T> & data) {
    int i;
	for(i=0; i<data.length()-1; i++) {
		if (data[i] > data[i+1]) {

            #ifdef SEARCH_DEBUG_
        	std::cout << "\nisOrdered " <<  data << " took " << (i+1) << " passes" << std::endl;
            #endif

			return false;
		}
	}

    #ifdef SEARCH_DEBUG_
    std::cout << "\nisOrdered " <<  data << " took " << (i+1) << " passes" << std::endl;
    #endif

	return true;
}

// PreCondition: Data array is full
// PostCondition: return position if val found in data array, otherwise -1
template <class T>
int sequentialSearch(const Array<T> & data, const T & val) {
    #ifdef SEARCH_DEBUG_
    std::cout << "\nSeqSearch: " << data << " for " << val;
    #endif
	for(int i=0; i<data.length(); i++) {
		if (data[i] == val) {

            #ifdef SEARCH_DEBUG_
            std::cout << " Found in " << (i+1) << " passes" << std::endl;
            #endif 

        	return i; // found
        }
	}

    #ifdef SEARCH_DEBUG_
    std::cout << " Not Found in " << data.length() << " passes" << std::endl; 
    #endif

	return -1; //not found
}

// PreCondition : Data array is full and is sorted
// PostCondition: return position if val found, otherwise -1
template <class T>
int binarySearch(const Array<T> & data, const T & val) {
    int left = 0, right = data.length() - 1;

    #ifdef SEARCH_DEBUG_
    std::cout << "\nBinarySearch: " << data << " for " << val << std::endl;
    #endif

    while (left <= right) {
        int pivot = (left + right) / 2;

        #ifdef SEARCH_DEBUG_
        std::cout << "Left=" << left << " Pivot=" << pivot << " Right=" << right << std::endl;
        #endif

        if (data[pivot] == val) {
            return pivot; // found
        } else if (data[pivot] < val) {
            left = pivot + 1; // search right
        } else {
            right = pivot - 1; // search left
        }
    }
    return -1;
}


// PreCondition: Data array is full
// PostCondition: return number of occurences of e in Array
template <class T>
int countOccurrence(const Array<T> & data, const T & e)
{
	int count = 0, i;
	for(i=0; i<data.length(); i++) {
		if (data[i] == e) {
            count++;
        }
	}
    #ifdef SEARCH_DEBUG_
	std::cout << "\nCount Occurrence for " << e << " in " << data << " took " << (i+1) << " passes" << std::endl;
    #endif

	return count;
}

// PreCondition: Data array is full and sorted
// PostCondition: return number of occurences of e in Array
template <class T>
int countOccurrenceOrdered(const Array<T> & data, const T & e)
{
	int i, count = 0;
	// find first occurance
	for (i = 0; i < data.length() && data[i] != e; i++) {};
	
    // count contiguous occurances
	for (; i < data.length() && data[i] == e; i++, count++) {};

    #ifdef SEARCH_DEBUG_
	std::cout << "\nCount ordered Occurrence for " << e << " in " <<  data << " took " << (i+1) << " passes" << std::endl;
    #endif

	return count;
}

// PreCondition: data and keys are full arrays and are unordered
// PostConditon: return true if elements in keys array is found 
//               in data array, otherwise false  
template <class T>
bool containsAll(const Array<T> & data, const Array<T> & keys) {
    int i;
    for(i=0; i<keys.length(); i++) {
        if (sequentialSearch(data, keys[i]) == -1) {
            #ifdef SEARCH_DEBUG_
        	std::cout << "\ncontainsAll " << keys << " in " <<  data << " failed in " << (i+1) << " passes" << std::endl;
            #endif
            return false;
        }
    }
    #ifdef SEARCH_DEBUG_
    std::cout << "\ncontainsAll " << keys << " in " <<  data << " succeeded in " << (i+1) << " passes" << std::endl;
    #endif
    return true;
}


// PreCondition: named file exists and contains integers
// PostCondition: array is loaded with integers read from
//                file and array is resized if necessary
template <class T>
void loadFromFile(Array<T> & data, std::string fname) {
	std::ifstream ifile;
	ifile.open(fname.c_str());

	if (!ifile.fail()) {
		T val;
		int i = 0;
		while (ifile >> val) {
			if (i == data.length())
				data.resize(data.length() * 2); // double size of array
			data[i++] = val;
		}
		// resize array to i, to remove unused blanks
		data.resize(i);

		ifile.close();
	}
}
#endif	/* SEARCH_H */
