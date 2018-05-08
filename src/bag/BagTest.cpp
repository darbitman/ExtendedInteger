#include "Bag.h"
#include <iostream>


int main() {
    Bag<unsigned int> b;
    b.add(12);
    b.add(15);
    b.add(111);
    b.add(111);
    b.size();
    std::cout << b.isEmpty() << std::endl;
    Bag<unsigned int>::iterator iter = b.begin();
    std::cout << *iter++ << std::endl;
    std::cout << *(++iter) << std::endl;
    std::cout << (iter == b.end());
    Bag<unsigned int> c(b);
    return 0;
}
