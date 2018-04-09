#include "Stack.h"
#include <iostream>


int main() {
    Stack<unsigned int>* s = new Stack<unsigned int>();
    s->push(3);
    s->push(10);
    s->push(15);
    Stack<unsigned int>* s2 = new Stack<unsigned int>(*s);
    while (!s->isEmpty()) {
        std::cout << s->pop() << std::endl;
        std::cout << s2->pop() << std::endl;
    }
    std::cout << s->isEmpty() << std::endl << s2->isEmpty() << std::endl;
    delete s;
    return 0;
}