#ifndef _TYPEDEFS_H_
#define _TYPEDEFS_H_

#include "ExtendedIntLengths.h"

template<unsigned int t>
class UnsignedExtendedInt;


typedef UnsignedExtendedInt<4> uextint128_t;
typedef UnsignedExtendedInt<8> uextint256_t;
typedef UnsignedExtendedInt<12> uextint512_t;

//typedef SignedExtendedInt<_extint128_t> extint128_t;
//typedef SignedExtendedInt<_extint256_t> extint256_t;
//typedef SignedExtendedInt<_extint512_t> extint512_t;

#endif
