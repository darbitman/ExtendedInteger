#include "stdafx.h"
#include <iostream>

#include "ExtendedInteger.h"


using namespace std;

int main() {
    //extint256_t x = "9";
    uextint128_t* x = new uextint128_t("1324");
    UnsignedExtendedInt<_extint256_t>* y = new UnsignedExtendedInt<_extint256_t>();
    UnsignedExtendedInt<_extint256_t>* z = new UnsignedExtendedInt<_extint256_t>(*y);
    return 0;
}
