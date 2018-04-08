#include "Bag.h"
#include <iostream>

int main() {
    Bag<unsigned int> b;
    b.add(12);
    b.add(15);
    b.add(111);
    std::cout << b.isEmpty() << std::endl;
    Bag<unsigned int>::iterator iter = b.begin();
    std::cout << *iter++ << std::endl;
    std::cout << *(++iter) << std::endl;
    std::cout << (iter == b.end());
    return 0;
}
