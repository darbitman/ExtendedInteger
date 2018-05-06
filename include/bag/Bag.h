#pragma once
#include "Logger.h"
#include <string>


/**
This class implements a bag using a singly linked list
 */
template<typename T>
class Bag {
private:
  struct BagObject {
    T data;
    BagObject* nextObjectPtr;
  };
  BagObject* firstObjectPtr;
  BagObject* lastObjectPtr;
  unsigned int numOfObjects;
public:
  /**
  Create an empty bag
  */
  Bag();

  /**
  Bag copy constructor
  */
  Bag(const Bag& rhs);

  /**
  Clean up bag memory
  */
  ~Bag();

  /**
  Add element to the end of the bag
  */
  void add(T data);


  /**
  Returns true if bag is empty
  */
  bool isEmpty() const;

  /**
  Returns number of items in the bag
  */
  unsigned int size() const;


  class iterator {
  public:
    iterator();
    iterator(BagObject* dataPtr);
    iterator operator++(int);
    iterator operator++();
    T operator*() const;
    bool operator==(const iterator& rhs);
    bool operator!=(const iterator& rhs);
  private:
    BagObject* iterDataPtr;
  };


  iterator begin() const;
  iterator end() const;
};


template<typename T>
Bag<T>::Bag() {
  if (LOGGER_VERBOSITY == Logger::Verbose) {
    std::string s = "Creating empty bag";
    Logger::getInstance().addEntry(s.c_str());
  }
  firstObjectPtr = 0;
  lastObjectPtr = 0;
  numOfObjects = 0;
}


template<typename T>
Bag<T>::Bag(const Bag& rhs) {
  if (LOGGER_VERBOSITY == Logger::LogLevel::Verbose) {
    std::string s = "Bag copy constructor called";
    Logger::getInstance().addEntry(s.c_str());
  }
  firstObjectPtr = 0;
  lastObjectPtr = 0;
  numOfObjects = rhs.numOfObjects;
  BagObject* rhsObjectPtr = rhs.firstObjectPtr;
  for (unsigned int i = 0; i < numOfObjects; i++) {
    if (i == 0) {
      firstObjectPtr = new BagObject();
      lastObjectPtr = firstObjectPtr;
    }
    else {
      lastObjectPtr->nextObjectPtr = new BagObject();
      lastObjectPtr = lastObjectPtr->nextObjectPtr;
    }
    lastObjectPtr->data = rhsObjectPtr->data;
    rhsObjectPtr = rhsObjectPtr->nextObjectPtr;
    lastObjectPtr->nextObjectPtr = 0;
  }
}



template<typename T>
Bag<T>::~Bag() {
  if (LOGGER_VERBOSITY == Logger::Verbose) {
    std::string s = "Bag destructor called";
    Logger::getInstance().addEntry(s.c_str());
  }
  BagObject* nextObjectToDelete;
  while (numOfObjects) {
    numOfObjects--;
    nextObjectToDelete = firstObjectPtr->nextObjectPtr;
    delete firstObjectPtr;
    firstObjectPtr = nextObjectToDelete;
  }
}



template<typename T>
void Bag<T>::add(T data) {
  if (LOGGER_VERBOSITY == Logger::Verbose) {
    std::string s = "Adding bag element: ";
    s = s + std::to_string(data);
    Logger::getInstance().addEntry(s.c_str());
  }
  if (numOfObjects == 0) {
    firstObjectPtr = new BagObject();
    lastObjectPtr = firstObjectPtr;
  }
  else {
    lastObjectPtr->nextObjectPtr = new BagObject();
    lastObjectPtr = lastObjectPtr->nextObjectPtr;
  }
  lastObjectPtr->data = data;
  lastObjectPtr->nextObjectPtr = 0;
  numOfObjects++;
}


template<typename T>
bool Bag<T>::isEmpty() const {
  if (LOGGER_VERBOSITY == Logger::Verbose) {
    std::string s = "Checking if bag is empty";
    Logger::getInstance().addEntry(s.c_str());
  }
  return numOfObjects > 0 ? false : true;
}



template<typename T>
unsigned int Bag<T>::size() const {
  if (LOGGER_VERBOSITY == Logger::LogLevel::Verbose) {
    std::string s = "Getting number of elements in the bag: ";
    s = s + std::to_string(numOfObjects);
    Logger::getInstance().addEntry(s.c_str());
  }
  return numOfObjects;
}


template<typename T>
Bag<T>::iterator::iterator() {}


template<typename T>
Bag<T>::iterator::iterator(BagObject* dataPtr): iterDataPtr(dataPtr) {}


/**
Increments the iterator after returning the current data iterator points to
*/
template<typename T>
typename Bag<T>::iterator Bag<T>::iterator::operator++(int) {
  if (LOGGER_VERBOSITY == Logger::Verbose) {
    std::string s = "Post-increment iterator";
    Logger::getInstance().addEntry(s.c_str());
  }
  iterator iteratorToReturn = *this;
  iterDataPtr = iterDataPtr->nextObjectPtr;
  return iteratorToReturn;
}


/**
Increments the iterator and returns the data iterator now points to
*/
template<typename T>
typename Bag<T>::iterator Bag<T>::iterator::operator++() {
  if (LOGGER_VERBOSITY == Logger::LogLevel::Verbose) {
    std::string s = "Pre-increment bag iterator";
    Logger::getInstance().addEntry(s.c_str());
  }
  iterDataPtr = iterDataPtr->nextObjectPtr;
  return *this;
}


/**
Dereference the iterator
*/
template<typename T>
T Bag<T>::iterator::operator*() const {
  if (LOGGER_VERBOSITY == Logger::Verbose) {
    std::string s = "Dereference bag iterator";
    Logger::getInstance().addEntry(s.c_str());
  }
  return iterDataPtr->data;
}


/**
Compares equality of two iterators
*/
template<typename T>
bool Bag<T>::iterator::operator==(const iterator& rhs) {
  if (LOGGER_VERBOSITY == Logger::Verbose) {
    std::string s = "Comparing if two bag iterators are equal";
    Logger::getInstance().addEntry(s.c_str());
  }
  return iterDataPtr == rhs.iterDataPtr;
}


/**
Compares inequality of two iterators
*/
template<typename T>
bool Bag<T>::iterator::operator!=(const iterator& rhs) {
  if (LOGGER_VERBOSITY == Logger::Verbose) {
    std::string s = "Comparing if two bag iterators are not equal";
    Logger::getInstance().addEntry(s.c_str());
  }
  return iterDataPtr != rhs.iterDataPtr;
}


/**
Get an iterator to the beginning of the bag
*/
template<typename T>
typename Bag<T>::iterator Bag<T>::begin() const {
  if (LOGGER_VERBOSITY == Logger::Verbose) {
    std::string s = "Getting bag iterator to the beginning";
    Logger::getInstance().addEntry(s.c_str());
  }
  return iterator(firstObjectPtr);
}


/**
Get an iterator to the end of the bag
*/
template<typename T>
typename Bag<T>::iterator Bag<T>::end() const {
  if (LOGGER_VERBOSITY == Logger::Verbose) {
    std::string s = "Getting bag iterator to the end";
    Logger::getInstance().addEntry(s.c_str());
  }
  if (lastObjectPtr == 0) {
    return iterator(0);
  }
  else {
    return iterator(lastObjectPtr->nextObjectPtr);
  }
}
