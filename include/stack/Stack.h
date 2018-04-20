#pragma once
#include "Exception.h"
#include "Logger.h"
#include <string>

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
  if (LOGGER_VERBOSITY == Logger::LogLevel::Verbose) {
    std::string s = "Creating a new stack";
    Logger::getInstance().addEntry(s.c_str());
  }
  size = 2;
  numEntries = 0;
  stackPtr = new T[size];
}


template<typename T>
Stack<T>::Stack(const Stack<T>& rhs) {
  if (LOGGER_VERBOSITY == Logger::LogLevel::Verbose) {
    std::string s = "Calling stack copy constructor";
    s = s + std::to_string(stackPtr[numEntries - 1]);
    Logger::getInstance().addEntry(s.c_str());
  }
  size = rhs.size;
  numEntries = rhs.numEntries;
  stackPtr = new T[size];
  for (unsigned int i = 0; i < numEntries; i++) {
    stackPtr[i] = rhs.stackPtr[i];
  }
}


template<typename T>
Stack<T>::~Stack() {
  if (LOGGER_VERBOSITY == Logger::LogLevel::Verbose) {
    std::string s = "Deleting stack";
    Logger::getInstance().addEntry(s.c_str());
  }
  delete[] stackPtr;
}


template<typename T>
bool Stack<T>::isEmpty() const {
  if (LOGGER_VERBOSITY == Logger::LogLevel::Verbose) {
    std::string s = "Checking if stack is empty";
    Logger::getInstance().addEntry(s.c_str());
  }
  return !numEntries;
}


template<typename T>
void Stack<T>::push(T data) {
  if (LOGGER_VERBOSITY == Logger::LogLevel::Verbose) {
    std::string s = "Adding stack entry: ";
    s = s + std::to_string(data);
    Logger::getInstance().addEntry(s.c_str());
  }
  if (numEntries == size) {                     // current stack is full, need to double size and copy over
    unsigned int newSize = size * 2;
    T* newStackPtr = new T[newSize];            // create new stack of double the size
    for (unsigned int i = 0; i < size; i++) {
      newStackPtr[i] = stackPtr[i];             // copy old stack data to new stack
    }
    delete[] stackPtr;                          // delete old stack data
    stackPtr = newStackPtr;                     // set old data pointer to point to new stack
    size = newSize;                             // assign size to new size
  }
  stackPtr[numEntries++] = data;
}


/**
Removes and returns item at the top of the stack
Throws StackEmptyException
**/
template<typename T>
T Stack<T>::pop() {
  if (numEntries == 0) {
    throw StackEmptyException();
  }
  if (LOGGER_VERBOSITY == Logger::LogLevel::Verbose) {
    std::string s = "Popping stack entry: ";
    s = s + std::to_string(stackPtr[numEntries - 1]);
    Logger::getInstance().addEntry(s.c_str());
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
Returns item at the top of the stack without removing it
Throws StackEmptyException
**/
template<typename T>
T Stack<T>::peek() const {
  if (numEntries == 0) {
    throw StackEmptyException();
  }
  if (LOGGER_VERBOSITY == Logger::LogLevel::Verbose) {
    std::string s = "Peeking stack entry: ";
    s = s + std::to_string(stackPtr[numEntries - 1]);
    Logger::getInstance().addEntry(s.c_str());
  }
  return stackPtr[numEntries - 1];
}