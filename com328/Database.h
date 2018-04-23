/**
* Database.h
*
* Template based Database class based on an ArrayList
*
* @author  Aiden McCaughey
* @email   a.mccaughey@ulster.ac.uk
* @version 1.1 (12-12-2016)
*/

#ifndef DATABASE_H_
#define DATABASE_H_

#include "ArrayList.h"

#include <cstdlib>
#include <fstream>

template <class T>
class Database
{
public:
	explicit Database(int s = 100) : elements(s), current{ -1 } {};
	Database(const ArrayList<T> & e) : elements(e), current{ -1 } {};
	Database(const Database<T> & d) : elements(d.elements), current{ d.current } {};

	bool first();
	bool last();
	bool next();
	bool prev();

	void add(const T & element);
	void remove();
	void set(const T & element);
	T    get() const;
	void clear();
	int  size() const;

	void print(std::ostream & os) const;

	void load(const std::string & fname);
	void save(const std::string & fname);

protected:
	ArrayList<T> elements;
	int current;

};

// PostCondition: return number of elements database
template <class T>
inline int Database<T>::size() const
{
	return elements.size();
}

// PostCondition: initialise the database to empty
template <class T>
void Database<T>::clear()
{
	elements.clear();
	current=-1;
}

// PostCondition: move to previous position in database if possible
//                and return true otherwise false
template <class T>
inline bool Database<T>::prev() 
{
	if (size() > 0 && current > 0) {
		current--;
		return true;
	} else {
		return false;
	}
}

// PostCondition: move to next position in database if possible
//                and return true otherwise false
template <class T>
inline bool Database<T>::next() 
{
	if (size() > 0 && current < size()-1) {
		current++;
		return true;
	} else {
		return false;
	}
}

// PostCondition: move to first position in database if possible
//                and return true otherwise false
template <class T>
inline bool Database<T>::first() 
{
	if (size() > 0) {
		current=0;
		return true;
	} else {
		return false;
	}
}

// PostCondition: move to last position in database if possible
//                and return true otherwise false
template <class T>
inline bool Database<T>::last() 
{
	if (size() > 0) {
		current = size()-1;
		return true;
	} else {
		return false;
	}
}

// PostCondition: add element to current position in database
template <class T>
void Database<T>::add(const T & element)
{
	if (current >= -1 && current < size()) {
		current++;
		elements.add(current, element);
	} else {
		throw std::out_of_range("Database: add out of range");
	}
}


// PostCondition: update element at current position in database
template <class T>
void Database<T>::set(const T & element)
{
	if (current >= -1 && current < size()) {
		elements.set(current, element);
	}
	else {
		throw std::out_of_range("Database: set out of range");
	}
}


// PreCondition: database is not empty
// PostCondition: return element at current position
template <class T>
T Database<T>::get() const
{
	if (current >= 0 && current < size()) {
		return elements.get(current);
	} 
	else {
		throw std::out_of_range("Database: retrieve out of range");
	}
}

// PreCondition: database is not empty
// PostCondition: element at current position is deleted and 
//                current is decremented when current is > 0 
template <class T>
void Database<T>::remove()
{
	if (current >= 0 && current < size()) {
		elements.remove(current);
		if (current > 0) { current--; } // decrement current unless already at first record
	}
	else {
		throw std::out_of_range("Database: remove out of range");
	}
}

// PreCondition:  type T has a copy constructor that can deserialse a string into a type T instance
// PostCondition: load content of file into database
template <class T>
void Database<T>::load(const std::string & fname) {
	std::ifstream in_stream;
	in_stream.open(fname.c_str());

	if (!in_stream.fail()) {        
		std::string str; 
		while (std::getline(in_stream, str))
		{
			T val(str);
			add(val);
		}
		first();
	}
	in_stream.close();

}

// PreCondition: type T has an overloaded << operator that can serialise an instance of T
// PostCondition: save content of database to file
template <class T>
void Database<T>::save(const std::string & fname) {
	std::ofstream out_stream;
	int orig_current = current;

	out_stream.open(fname.c_str());
	first();
	if (!out_stream.fail() && size() > 0) {
		do  {
			out_stream << get();
			out_stream << std::endl;
		} while (next());
	}
	current = orig_current;
	out_stream.close();
	
}

// Post Condition: Print elements in sequence to parameter ostream
template <class T>
void Database<T>::print(std::ostream & os) const {
	os << "{" << current << "} ";
	elements.print(os);
	os << std::endl;
}

template <class T>
std::ostream& operator <<(std::ostream& output, const Database<T>& p) {
	p.print(output);
	return output;  // for multiple << operators.
}

#endif
