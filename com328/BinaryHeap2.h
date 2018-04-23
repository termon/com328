/**
 * Heap.h
 *
 * Generic Dynamic Heap based on array
 *
 * @author  Aiden McCaughey
 * @email   a.mccaughey@ulster.ac.uk
 * @version 1.0
 */

#ifndef _HEAP_H_
#define _HEAP_H_

#include "Array.h"

template <class T>
class Heap {
public:
  explicit Heap(int s=10) : data(s), size(0) { data.initialise(0); }
  void insert(T);
  T remove();
  int getSize();

private:
  void bubbleUp();
  void bubbleDown();
  void swap(int child, int parent);
  int  getLeftChild(int parent);
  int  getRightChild(int parent);
  int  getParent(int child);

  Array<T> data;
  int size;
};

template <class T>
int Heap<T> :: getSize(){
  return size;
}

template <class T>
void Heap<T>::swap(int child, int parent) {
  T temp;
  temp = data[child];
  data[child] = data[parent];
  data[parent] = temp;
}

template <class T>
int Heap<T> :: getParent(int child) {
  	return child/2;  
}

template <class T>
int Heap<T> :: getLeftChild(int parent){
    return 2 * parent;
}

template <class T>
int Heap<T> :: getRightChild(int parent){
    return 2 * parent + 1;
}

template <class T>
void Heap<T> :: insert(T value) {
  data[++size] = value;

  bubbleUp();
  std::cout << "insert(" << value << ") " << data << std::endl;
}

template <class T>
T Heap<T> :: remove() {
  int child = getSize() - 1;
  swap(child, 0);
  
  T value = data[size--];
  bubbleDown();
  return value;
	
}

template <class T>
void Heap <T>:: bubbleUp() {
  
  // T x = data[size];
  // int hole = size;

  // for( ; hole > 1 && x < data[ parent(hole) ]; hole = parent(hole) ) {
	// 	data[ hole ] = data[ parent(hole) ];
	// }
  
  int child = getSize();
  int parent = getParent(child);
  
	data[ hole ] = x;
  while (data[child] > data[parent] && child >=1 && parent >= 1) {	
  	swap(child, parent);
	  child = parent;
	  parent = getParent(child);
  }  
}

template <class T>
void Heap<T> :: bubbleDown() {
  int parent = 0;

  while (1) {
	int left = getLeftChild(parent);
	int right = getRightChild(parent);
	int length = getSize();
	int largest = parent;

	if (left < length && data[left] > data[largest])
	  largest = left;

	if (right < length && data[right] > data[largest])
	  largest = right;

	if (largest != parent) {
	  swap(largest, parent);
	  parent = largest;
	} else { 
	  break;
    }	
  }

}
#endif
