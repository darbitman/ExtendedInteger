#include "stdafx.h"
#include <iostream>

#include "ExtendedInteger.h"


using namespace std;

int main() {
    extint128_t x;
    x.setValueAtIndex(0x80000000, 3);
    extint128_t y = "23";
    extint128_t z = x * -23;
    return 0;
}
