#pragma once


template<typename T>
class Stack {
private:
    struct StackEntry {
        T data;
        StackEntry* stackEntryBelowPtr;
    };
    StackEntry* topOfStackPtr;
    unsigned int numEntries;
public:
    Stack();
    Stack(const Stack<T>& rhs);
    ~Stack();
    bool isEmpty() const;
    void push(T data);
    T pop();
    T peek() const ;
};


template<typename T>
Stack<T>::Stack() {
    topOfStackPtr = 0;
    numEntries = 0;
}


template<typename T>
Stack<T>::Stack(const Stack<T>& rhs) {
    StackEntry* rhsCurrentStackEntryPtr = rhs.topOfStackPtr;
    StackEntry* thisObjectsCurrentStackEntryPtr = 0;
    numEntries = rhs.numEntries;
    for (unsigned int i = 0; i < numEntries; i++) {
        if (i == 0) {
            thisObjectsCurrentStackEntryPtr = new StackEntry();
            topOfStackPtr = thisObjectsCurrentStackEntryPtr;
        }
        else {
            thisObjectsCurrentStackEntryPtr->stackEntryBelowPtr = new StackEntry();
            thisObjectsCurrentStackEntryPtr = thisObjectsCurrentStackEntryPtr->stackEntryBelowPtr;
        }
        thisObjectsCurrentStackEntryPtr->stackEntryBelowPtr = 0;
        thisObjectsCurrentStackEntryPtr->data = rhsCurrentStackEntryPtr->data;
        thisObjectsCurrentStackEntryPtr->stackEntryBelowPtr = 0;
        rhsCurrentStackEntryPtr = rhsCurrentStackEntryPtr->stackEntryBelowPtr;
    }
}


template<typename T>
Stack<T>::~Stack() {
    StackEntry* nextEntryToDelete;
    while (topOfStackPtr) {
        nextEntryToDelete = topOfStackPtr->stackEntryBelowPtr;
        delete topOfStackPtr;
        topOfStackPtr = nextEntryToDelete;
    }
}


template<typename T>
bool Stack<T>::isEmpty() const {
    return !numEntries;
}


template<typename T>
void Stack<T>::push(T data) {
    if (topOfStackPtr == 0) {                                       // if stack is empty, need to create new node and update topOfStackPtr
        topOfStackPtr = new StackEntry();
        topOfStackPtr->data = data;
        topOfStackPtr->stackEntryBelowPtr = 0;
    }
    else {                                                          // if stack is not empty
        StackEntry* newTopStackEntryPtr = new StackEntry();         // create new stack entry
        newTopStackEntryPtr->data = data;
        newTopStackEntryPtr->stackEntryBelowPtr = topOfStackPtr;    // set the new stack entry's stackEntryBelowPtr to point to old topOfStackPtr
        topOfStackPtr = newTopStackEntryPtr;                        // update topOfStackPtr to point to new stack entry
    }
    numEntries++;
}


template<typename T>
T Stack<T>::pop() {
    if (numEntries) {                                               // can pop only when stack has at least 1 entry
        T dataToReturn = topOfStackPtr->data;
        StackEntry* stackEntryToDelete = topOfStackPtr;             // store ptr to top entry in temp variable
        if (topOfStackPtr->stackEntryBelowPtr) {                    // if entry exists below the top, then update topOfStackPtr to point below
            topOfStackPtr = topOfStackPtr->stackEntryBelowPtr;
        }
        else {                                                      // if nothing exists below top, set topOfStackPtr = 0
            topOfStackPtr = 0;
        }
        numEntries--;
        return dataToReturn;
    }
    else {
        T temp(0);
        return temp;
    }
}


template<typename T>
T Stack<T>::peek() const {
    if (numEntries) {
        return topOfStackPtr->data;
    }
    else {
        T temp(0);
        return temp;
    }
}