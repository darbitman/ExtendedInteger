// ExtendedMath.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "UnsignedExtendedInt.h"

using namespace std;

int main() {
    UnsignedExtendedInt* x = new UnsignedExtendedInt("9");
    UnsignedExtendedInt* y = new UnsignedExtendedInt("5");
    UnsignedExtendedInt* z = new UnsignedExtendedInt(*x % *y);
    return 0;
}
