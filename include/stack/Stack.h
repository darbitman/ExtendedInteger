#pragma once
#include "Exception.h"

template<typename T>
class Stack {
private:
  T * stackPtr;
  unsigned int size;
  unsigned int numEntries;
public:
  Stack();
  Stack(const Stack<T>& rhs);
  ~Stack();
  bool isEmpty() const;
  void push(T data);
  T pop();
  T peek() const;
};


template<typename T>
Stack<T>::Stack() {
  size = 2;
  numEntries = 0;
  stackPtr = new T[size];
}


template<typename T>
Stack<T>::Stack(const Stack<T>& rhs) {
  size = rhs.size;
  numEntries = rhs.numEntries;
  stackPtr = new T[size];
  for (unsigned int i = 0; i < numEntries; i++) {
    stackPtr[i] = rhs.stackPtr[i];
  }
}


template<typename T>
Stack<T>::~Stack() {
  delete[] stackPtr;
}


template<typename T>
bool Stack<T>::isEmpty() const {
  return !numEntries;
}


template<typename T>
void Stack<T>::push(T data) {
  if (numEntries == size) {                       // current stack is full, need to double size and copy over
    unsigned int newSize = size * 2;
    T* newStackPtr = new T[newSize];            // create new stack of double the size
    for (unsigned int i = 0; i < size; i++) {
      newStackPtr[i] = stackPtr[i];           // copy old stack data to new stack
    }
    delete[] stackPtr;                          // delete old stack data
    stackPtr = newStackPtr;                     // set old data pointer to point to new stack
    size = newSize;                             // assign size to new size
  }
  stackPtr[numEntries++] = data;
}


/**
Throws StackEmptyException
**/
template<typename T>
T Stack<T>::pop() {
  if (numEntries == 0) {
    throw StackEmptyException();
  }
  T returnValue = stackPtr[--numEntries];             // get value at the top of the stack
  if ((numEntries) <= (size / 4) && (size > 2)) {     // if stack will have 1/4 of the entries that fit, shrink the size of the array by 2
    unsigned int newSize = size / 2;                // new size is half the original size
    T* newStackPtr = new T[newSize];                // create stack of half size
    for (unsigned int i = 0; i < numEntries; i++) {
      newStackPtr[i] = stackPtr[i];               // copy old stack data to new stack
    }
    delete[] stackPtr;                              // delete old stack data
    stackPtr = newStackPtr;                         // set the old data pointer to point to new stack
    size = newSize;                                 // assign size to new size
  }
  return returnValue;
}


/**
Throws StackEmptyException
**/
template<typename T>
T Stack<T>::peek() const {
  if (numEntries == 0) {
    throw StackEmptyException();
  }
  return stackPtr[numEntries];
}