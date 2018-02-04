#ifndef _TYPEDEFS_H_
#define _TYPEDEFS_H_

#include "ExtendedIntLengths.h"

template<typename T>
class UnsignedExtendedInt;

template<typename T>
class SignedExtendedInt;

typedef UnsignedExtendedInt<_extint128_t> uextint128_t;
typedef UnsignedExtendedInt<_extint256_t> uextint256_t;
typedef UnsignedExtendedInt<_extint512_t> uextint512_t;

typedef SignedExtendedInt<_extint128_t> extint128_t;
typedef SignedExtendedInt<_extint256_t> extint256_t;
typedef SignedExtendedInt<_extint512_t> extint512_t;

#endif
