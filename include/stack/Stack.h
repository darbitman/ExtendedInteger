#pragma once

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
