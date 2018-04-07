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
    ~Bag();
    void add(T obj);
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
        BagObject* iterDataPtr;
    };

    iterator begin() {
        return iterator(firstObjectPtr);
    }

    iterator end() {
        if (lastObjectPtr == 0) {
            return iterator(0);
        }
        else {
            return iterator(lastObjectPtr->nextObjectPtr);
        }
    }
};


template<typename T>
Bag<T>::Bag() {
    firstObjectPtr = 0;
    lastObjectPtr = 0;
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
Bag<T>::iterator::iterator(BagObject* dataPtr) : iterDataPtr(dataPtr) {}

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
