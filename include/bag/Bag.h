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
    BagObject* nextObjectToReturnPtr;
    unsigned int numOfObjects;
public:
    Bag();
    ~Bag();
    void add(T obj);
    T nextObject();
};


template<typename T>
Bag<T>::Bag() {
    firstObjectPtr = 0;
    lastObjectPtr = 0;
    nextObjectToReturnPtr = 0;
    numOfObjects = 0;
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
void Bag<T>::add(T obj) {
    if (numOfObjects == 0) {
        firstObjectPtr = new BagObject();
        firstObjectPtr->data = obj;
        lastObjectPtr = firstObjectPtr;
    }
    else {
        lastObjectPtr->nextObjectPtr = new BagObject();
        lastObjectPtr = lastObjectPtr->nextObjectPtr;
        lastObjectPtr->data = obj;
        lastObjectPtr->nextObjectPtr = 0;
    }
    numOfObjects++;
}

template<typename T>
T Bag<T>::nextObject() {
    T objectToReturn;
}