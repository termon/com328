/**
 * HashTable.h
 *
 * Linear probing Hash Table 
 *
 * @author  Aiden McCaughey
 * @email   a.mccaughey@ulster.ac.uk
 * @version 1.0
 */

#ifndef HASH_H_
#define HASH_H_

#include "Array.h"
#include <string>


template <class T>
class HashTable
{
public:
	explicit HashTable(int size = 101) : table(size), currentsize{ 0 } {}
	void clear();
	bool add(std::string key, const T & value);
	bool remove(std::string key);
	bool find(std::string key, T & value) const;
	void print(std::ostream & out) const ;
	void rehash(int size);

private:
	enum EntryType { ACTIVE, EMPTY, DELETED };

	struct HashEntry {
	   std::string key;
       T element;
       EntryType info;

	   HashEntry(const std::string & k = "", const T & e = T(), EntryType i = EMPTY) : key(k), element(e), info(i) {}
	   bool operator==(const HashEntry & e) { return e.key == key; }
	};

	Array<HashEntry> table;
	int currentsize;

	bool isActive(int pos) const;
	bool isDeleted(int pos) const;

	int findPos(const std::string & key) const;
	int findPosLinear(const std::string & key) const;	
	int findPosQuadratic(const std::string & key) const;
	int findPosSecondary(const std::string & key) const;
	int hash(const std::string & key) const;
};

// PreCondition: 0 >= pos < table.length() 
// PostCondition: return true if entry is active, otherwise false
template <class T>
bool HashTable<T>::isActive(int pos) const {
	return table[pos].info == ACTIVE;
}

// PreCondition: 0 >= pos < table.length() 
// PostCondition: return true if entry is deleted, otherwise false
template <class T>
bool HashTable<T>::isDeleted(int pos) const {
	return table[pos].info == DELETED;
}

template <class T>
int HashTable<T>::findPos(const std::string & key) const {
	int pos = findPosLinear(key);
	return pos;
}

// PostCondtion: table hash entries are marked as empty
template <class T>
void HashTable<T>::clear() {
	for(int i=0; i<table.length(); i++)
		table[i].info = EMPTY;
}


// PostCondtion: resize the table and rehash active hash entries
template <class T>
void HashTable<T>::rehash(int size) {
	if (size > table.length()) {
		// copy table to a temporary array
		Array<HashEntry> tmp = table;

		// empty the table
		clear();

		// create a new table
		table = Array<HashEntry>(size);

		for(int i=0; i<tmp.length(); i++) {
			if (tmp[i].info == ACTIVE)
				add(tmp[i].key, tmp[i].element);
		}
	}
}

// PostCondition: private hash function
template <class T>
int HashTable<T>::hash(const std::string & key) const {
	int pos = 0;
	for (size_t i = 0; i < key.length(); i++) {
		pos += key[i];
	}
	pos =  pos % table.length();
	return pos;
}

// PreCondition: table is not full
// PostCondition: new HashEntry containing key and val is inserted into the table
template <class T>
bool HashTable<T>::add(std::string key, const T & value) {
	
	int pos = findPos(key);							// determine position
	if (!isActive(pos))	{			  				// if position empty
		table[pos] = HashEntry(key, value, ACTIVE); // insert item
		currentsize++;								// increment table size
	    return true;
	}
	return false;
}

// PreCondition: table is not full
// PostCondition: if located element is marked as deleted
template <class T>
bool HashTable<T>::remove(std::string key) {
	int pos = findPos(key);							// locate position in table
	if (isActive(pos) && table[pos].key == key) {	// check if found it
		table[pos].info = DELETED;					// mark as deleted
		currentsize--;								// reduce table count
		return true;
	}
	return false;
}


// PostCondition: if element identified by key is found element is 
//                returned in reference parameter val and function
//                returns true, otherwise function returns false
template <class T>
bool HashTable<T>::find(std::string key, T & value) const {
	bool found = false;
	int pos = findPos(key);
	
	if (isActive(pos) && table[pos].key == key ) {  // check if we found it
	    value = table[pos].element;		// copy value to reference parameter
		found = true;
	}
	return found;
}


// PreCondtion:   table is not full
// PostCondition: private method used to locate position for specified key
//                using linear probing 
template <class T>
int HashTable<T>::findPosLinear(const std::string & key) const {
	// calculate hash position in table
	int pos = hash(key);

	// Checks if all positions in table have been examined
	int visited = 0;
	while( isActive(pos) && table[pos].key != key && visited <= table.length()) {
		visited++;
		pos++;							// go to next cell
        pos = pos % table.length();		// wrap if necessary
	}
	return pos;
}

// PreCondtion:   table is not full
// PostCondition: private method used to locate postion for specified key
//                using quadratic probing    
template <class T>
int HashTable<T>::findPosQuadratic(const std::string & key) const {
	bool found = false;
	int offset = 1, visited = 0;
	int pos = hash(key);

	while( isActive(pos) && table[pos].key != key && visited <= table.length()) {
		visited++;
		pos += offset;					// compute ith probe
		offset +=2;
        pos = pos % table.length();		// wrap if necessary
	}
	return pos;
}

template <class T>
int HashTable<T>::findPosSecondary(const std::string & key) const {
	int visited = 0;
	int pos = hash(key);

	while( isActive(pos) && table[pos].key != key && visited <= table.length()) {
		visited++;
		pos = (7 - ( pos % 7 )) % table.length();	// secondary hash
	}
	return pos;
}

// PostCondition: table HashEntries are printed to output stream
template <class T>
void HashTable<T>::print(std::ostream & out) const {
	out << "[";
	for(int i=0; i<table.length(); i++) {
		if (isActive(i))
 			out << " (" << table[i].key << "," << table[i].element << ")";
		else if (isDeleted(i))
			out << " (x)";
		else
			out << " ()";	
	}
	out << " ]";
}

// PostCondition: overload << operator to output table on ostream
template <class T>
std::ostream & operator<<(std::ostream& output, const HashTable<T> & t) {
    t.print(output);
    return output;  // for multiple << operators.
}

#endif
