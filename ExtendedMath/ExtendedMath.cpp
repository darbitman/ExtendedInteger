#include "stdafx.h"
#include <iostream>

#include "ExtendedInteger.h"


using namespace std;

int main() {
    uextint128_t x;
    x.setValueAtIndex(0x123, 0);
    x >> 3;
    return 0;
}
