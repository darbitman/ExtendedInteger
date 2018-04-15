#pragma once
#include "ExtendedIntLengths.h"


template<unsigned int t>
class UnsignedExtendedInt;


typedef UnsignedExtendedInt<4> uextint128_t;
typedef UnsignedExtendedInt<8> uextint256_t;
typedef UnsignedExtendedInt<12> uextint512_t;


typedef SignedExtendedInt<4> extint128_t;
typedef SignedExtendedInt<8> extint256_t;
typedef SignedExtendedInt<12> extint512_t;
