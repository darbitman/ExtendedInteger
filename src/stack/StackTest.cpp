#include "Stack.h"
#include <iostream>


int main() {
    Stack<unsigned int>* s = new Stack<unsigned int>();
    std::cout << s->isEmpty() << std::endl;
    s->push(1);
    s->push(2);
    s->push(3);
    s->push(4);
    s->push(5);
    s->push(6);
    s->push(7);
    s->push(8);
    s->push(9);
    s->pop();
    s->pop();
    s->pop();
    s->pop();
    s->pop();
    s->pop();
    s->pop();
    s->pop();
    s->pop();
    return 0;
}