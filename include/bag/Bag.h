#pragma once


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
  Bag();
  Bag(const Bag& rhs);
  ~Bag();
  void add(T data);
  bool isEmpty() const;
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
    BagObject * iterDataPtr;
  };

  iterator begin() const;
  iterator end() const;
};


template<typename T>
Bag<T>::Bag() {
  firstObjectPtr = 0;
  lastObjectPtr = 0;
  numOfObjects = 0;
}


template<typename T>
Bag<T>::Bag(const Bag& rhs) {
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
  return numOfObjects > 0 ? false : true;
}


template<typename T>
unsigned int Bag<T>::size() const {
  return numOfObjects;
}


template<typename T>
Bag<T>::iterator::iterator() {}


template<typename T>
Bag<T>::iterator::iterator(BagObject* dataPtr): iterDataPtr(dataPtr) {}

template<typename T>
typename Bag<T>::iterator Bag<T>::iterator::operator++(int) {
  iterator iteratorToReturn = *this;
  iterDataPtr = iterDataPtr->nextObjectPtr;
  return iteratorToReturn;
}


template<typename T>
typename Bag<T>::iterator Bag<T>::iterator::operator++() {
  iterDataPtr = iterDataPtr->nextObjectPtr;
  return *this;
}


template<typename T>
T Bag<T>::iterator::operator*() const {
  return iterDataPtr->data;
}


template<typename T>
bool Bag<T>::iterator::operator==(const iterator& rhs) {
  return iterDataPtr == rhs.iterDataPtr;
}


template<typename T>
bool Bag<T>::iterator::operator!=(const iterator& rhs) {
  return iterDataPtr != rhs.iterDataPtr;
}


template<typename T>
typename Bag<T>::iterator Bag<T>::begin() const {
  return iterator(firstObjectPtr);
}


template<typename T>
typename Bag<T>::iterator Bag<T>::end() const {
  if (lastObjectPtr == 0) {
    return iterator(0);
  }
  else {
    return iterator(lastObjectPtr->nextObjectPtr);
  }
}
