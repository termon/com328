/**
* FluentDatabase.h
*
* Template based FluentDatabase class based on an Database
*
* @author  Aiden McCaughey
* @email   a.mccaughey@ulster.ac.uk
* @version 1.1 (07-03-2017)
*/

#ifndef FLUENTDATABASE_H_
#define FLUENTDATABASE_H_

#include "Database.h"

#include <cstdlib>
#include <fstream>

template <class T>
class FluentDatabase: public Database<T>
{
public:
	FluentDatabase(int size=100) : Database<T>(size) {};
	FluentDatabase(const Database<T> e) : Database<T>(e) {};

	FluentDatabase & add(const T & element);
	FluentDatabase & remove();
	FluentDatabase & clear();

};

// PostCondition: initialise the database to empty
template <class T>
FluentDatabase<T> & FluentDatabase<T>::clear()
{
	Database<T>::clear();
	return *this;
}


// PostCondition: add element to current position in database
template <class T>
FluentDatabase<T> & FluentDatabase<T>::add(const T & element)
{
	Database<T>::add(element);
	return *this;
}

// PreCondition: database is not empty
// PostCondition: element at current position is deleted and current is decremented
template <class T>
FluentDatabase<T> & FluentDatabase<T>::remove()
{
	Database<T>::remove();
	return *this;
}

template <class T>
std::ostream& operator <<(std::ostream& output, const FluentDatabase<T>& p) {
	Database<T>::p.print(output);
	return output;  // for multiple << operators.
}

#endif
