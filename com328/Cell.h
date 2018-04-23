/**
 * Cell.h
 *
 * Generic Cell ADT
 *
 * @author  Aiden McCaughey
 * @email   a.mccaughey@ulster.ac.uk
 * @version 1.0
 */

#ifndef CELL_H
#define CELL_H

#include <iostream>
#include <string>

template <class T>
class Cell  {
public:
	explicit Cell(const T & e) : value(e) {};
    bool operator==(const Cell<T> & right) const;
	Cell<T>& operator=(const Cell<T>& right);

    void  write(const T & e);
    T read() const;
    void print(std::ostream & os = std::cout) const;
  
private:
	T value;
};

// --------------- Cell Implementation -----------------------

template<class T>
T Cell<T>::read() const {
	return value;
}

template<class T>
void Cell<T>::write(const T & e) {
	value = e;
}

// PostCondition: prints contents of Cell to standard output
template<class T>
void Cell<T>::print(std::ostream & os) const {
	os << "{ " << value << " }";
}

// PostCondition: return true if Cells are equal, otherwise false
template<class T>
bool Cell<T>::operator==(const Cell<T> & right) const {
	return (value == right.value);
}

template<class T>
Cell<T>& Cell<T>::operator=(const Cell<T> & right) {
	value = right.value;
	return *this;
}

// PreCondition: None
// PostCondition: overload << operator to output Cell on ostream
template <class T>
std::ostream& operator <<(std::ostream& output, const Cell<T>& cell) {
    cell.print(output);
    return output;  // for multiple << operators.
}

#endif /* CELL_H*/