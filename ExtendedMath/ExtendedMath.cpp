#include "stdafx.h"
#include <iostream>
#include "ExtendedInteger.h"

using namespace std;

int main() {
    uextint128_t a(12);
    uextint256_t b(12);
    extint128_t c;
    a ^ b;
    return 0;
}
