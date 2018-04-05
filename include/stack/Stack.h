#ifndef _STACK_H_
#define _STACK_H_

class Stack {
private:
    struct StackEntry {
        unsigned int data;
        StackEntry* stackEntryBelowPtr;
    };
    StackEntry* topOfStackPtr;
public:
    Stack();
    ~Stack();
    void push(unsigned int data);
    unsigned int pop();
};



#endif