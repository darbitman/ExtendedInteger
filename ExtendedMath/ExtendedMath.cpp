#include "stdafx.h"
#include <iostream>

#include "ExtendedInteger.h"


using namespace std;

int main() {
    extint128_t x;
    x.setValueAtIndex(0x1, 0);
    ~x;
    return 0;
}
