#include "stdafx.h"
#include <iostream>
#include "ExtendedInteger.h"

using namespace std;

int main() {
    uextint128_t a(109);
    extint128_t b(a);
    cout << b << endl;
    int x = -10;
    unsigned int c = x;
    cout << x << endl << c;
    while (1);
    return 0;
}
