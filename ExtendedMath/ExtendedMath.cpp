// ExtendedMath.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "UnsignedExtendedInt.h"

using namespace std;

int main() {
    UnsignedExtendedInt* x = new UnsignedExtendedInt();
    UnsignedExtendedInt* y = new UnsignedExtendedInt("12345");
    x->setValueAtIndex(5, 0);
    //y->setValueAtIndex(0x05, 0);
    UnsignedExtendedInt* z = new UnsignedExtendedInt(*y / *x);
    return 0;
}
