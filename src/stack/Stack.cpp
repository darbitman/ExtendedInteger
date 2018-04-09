#include "Stack.h"


//Stack::Stack() {
//    topOfStackPtr = 0;
//};
//
//
//Stack::~Stack() {
//    StackEntry* nextEntryToDelete;
//    while (topOfStackPtr) {
//        nextEntryToDelete = topOfStackPtr->stackEntryBelowPtr;
//        delete topOfStackPtr;
//        topOfStackPtr = nextEntryToDelete;
//    }
//}
//
//
//void Stack::push(unsigned int data) {
//    if (topOfStackPtr == 0) {                                       // if stack is empty, need to create new node and update topOfStackPtr
//        topOfStackPtr = new StackEntry();
//        topOfStackPtr->data = data;
//        topOfStackPtr->stackEntryBelowPtr = 0;
//    }
//    else {                                                          // if stack is not empty
//        StackEntry* newTopStackEntryPtr = new StackEntry();         // create new stack entry
//        newTopStackEntryPtr->data = data;
//        newTopStackEntryPtr->stackEntryBelowPtr = topOfStackPtr;    // set the new stack entry's stackEntryBelowPtr to point to old topOfStackPtr
//        topOfStackPtr = newTopStackEntryPtr;                        // update topOfStackPtr to point to new stack entry
//    }
//}
//
//
//unsigned int Stack::pop() {
//    if (topOfStackPtr) {                                            // can pop only when stack has at least 1 entry
//        unsigned int dataToReturn = topOfStackPtr->data;
//        StackEntry* stackEntryToDelete = topOfStackPtr;             // store ptr to top entry in temp variable
//        if (topOfStackPtr->stackEntryBelowPtr) {                    // if entry exists below the top, then update topOfStackPtr to point below
//            topOfStackPtr = topOfStackPtr->stackEntryBelowPtr;
//        }
//        else {                                                      // if nothing exists below top, set topOfStackPtr = 0
//            topOfStackPtr = 0;
//        }
//        return dataToReturn;
//    }
//    else {
//        return 0;
//    }
//}
