#include "UnsignedExtendedInt.h"


UnsignedExtendedInt::UnsignedExtendedInt() : ExtendedInt() {
  ext_int = new unsigned int[arraySize];
  clearValue();
}


UnsignedExtendedInt::UnsignedExtendedInt(const UnsignedExtendedInt& obj) : ExtendedInt() {
  arraySize = obj.arraySize;
  ext_int = new unsigned int[arraySize];
  clearValue();
  for (unsigned int i = 0; i < arraySize; i++) {
    ext_int[i] = obj.ext_int[i];
  }
}


UnsignedExtendedInt::UnsignedExtendedInt(unsigned long long obj) : ExtendedInt() {
  ext_int = new unsigned int[arraySize];
  clearValue();
  ext_int[0] = obj & 0xFFFFFFFF;
  ext_int[1] = (obj >> 32) & 0xFFFFFFFF;
}


UnsignedExtendedInt::UnsignedExtendedInt(long long obj) : ExtendedInt() {
  ext_int = new unsigned int[arraySize];
  clearValue();
  ext_int[0] = obj & 0xFFFFFFFF;
}


UnsignedExtendedInt::UnsignedExtendedInt(int obj) : ExtendedInt() {
  ext_int = new unsigned int[arraySize];
  clearValue();
  ext_int[0] = obj & 0xFFFFFFFF;
}


UnsignedExtendedInt UnsignedExtendedInt::operator=(const UnsignedExtendedInt& obj) {
  // will need to make sure both objects are of the same size
  // to ensure no data loss and to save memory
  if (arraySize != obj.arraySize) {
    if (arraySize > obj.arraySize) {
      decreaseArraySizeTo(obj.arraySize);
    }
    else {
      increaseArraySizeTo(obj.arraySize);
    }
  }
  for (unsigned int i = 0; i < arraySize; i++) {
    ext_int[i] = obj.ext_int[i];
  }
  clearUnusedMemory();
  return *this;
}


UnsignedExtendedInt::~UnsignedExtendedInt() {}


UnsignedExtendedInt UnsignedExtendedInt::operator+(const UnsignedExtendedInt& obj) const {
  UnsignedExtendedInt returnValue;
  returnValue.newArraySize(arraySize > obj.arraySize ? arraySize : obj.arraySize);
  unsigned long long x = 0;
  unsigned long long y = 0;
  unsigned long long result = 0;
  unsigned long long carryBit = 0;
  for (unsigned int i = 0; i < arraySize; i++) {
    x = ext_int[i];
    y = obj.ext_int[i];
    result = x + y + carryBit;                              // perform 32bit addition of left and right operand plus carry bit from previous addition
    returnValue.ext_int[i] = result & 0xFFFFFFFF;           // extract bottom 32bits of the result of the addition
    carryBit = (result & 0x100000000) >> 32;                // extract the carry bit if it exists
  }
  if (carryBit) {                                           // if carryBit overflows, need to increase array size
    returnValue.increaseArraySizeTo(arraySize + 1);         // increase array size by 1 word
    returnValue.ext_int[returnValue.getArraySize() - 1] = carryBit & 0x1;
  }
  return returnValue;
}


UnsignedExtendedInt UnsignedExtendedInt::operator-(const UnsignedExtendedInt& obj) const {
  UnsignedExtendedInt returnValue(this->operator+(~obj + 1));
  returnValue.clearUnusedMemory();
  returnValue.decreaseArraySizeTo(returnValue.arraySize - 1);                   // subtraction can sometimes lead to overflow, so need to delete the carry bit that was generated
  return returnValue;
}


UnsignedExtendedInt UnsignedExtendedInt::operator*(const UnsignedExtendedInt& obj) const {
  unsigned int resultArraySize = arraySize + obj.arraySize;
  UnsignedExtendedInt returnValue;
  returnValue.increaseArraySizeTo(resultArraySize);
  unsigned int leftShiftValue = 0;
  unsigned long long x = 0;
  unsigned long long y = 0;
  unsigned long long z = 0;
  UnsignedExtendedInt intermediateResult;
  intermediateResult.increaseArraySizeTo(resultArraySize);
  for (unsigned int i = 0; i < arraySize; i++) {
    for (unsigned int j = 0; j < obj.arraySize; j++) {
      leftShiftValue = i + j;
      x = ext_int[i];
      y = obj.ext_int[i];
      z = x * y;
      if (leftShiftValue > 0) {                                                 // ensure valid memory can be accessed
        intermediateResult.ext_int[leftShiftValue - 1] = 0;                     // clear previously set lower 32bits because they will introduce a summation error
      }
      intermediateResult.ext_int[leftShiftValue] = z & 0xFFFFFFFF;              // extract lower 32bits of result
      intermediateResult.ext_int[leftShiftValue + 1] = (z >> 32) & 0xFFFFFFFF;  // extract upper 32bits of results
      returnValue = returnValue + intermediateResult;                           // add to previous summation
    }
  }
  returnValue.clearUnusedMemory();
  return returnValue;
}


UnsignedExtendedInt UnsignedExtendedInt::operator/(const UnsignedExtendedInt& obj) const {
  return divideModOperator(obj, ExtendedInt::DIVIDE_OP);
}


UnsignedExtendedInt UnsignedExtendedInt::operator%(const UnsignedExtendedInt& obj) const {
  return divideModOperator(obj, ExtendedInt::MOD_OP);
}


bool UnsignedExtendedInt::operator==(const UnsignedExtendedInt& obj) const {
  if (arraySize > obj.arraySize) {                // if calling object has upper bits not 0, then can't be equal
    for (unsigned int i = obj.arraySize; i < arraySize; i++) {
      if (ext_int[i] != 0) {
        return false;
      }
    }
  }
  if (obj.arraySize > arraySize) {                // if object being compared to has its upper bits not 0, then can't be equal
    for (unsigned int i = arraySize; i < obj.arraySize; i++) {
      if (obj.ext_int[i] != 0) {
        return false;
      }
    }
  }
  unsigned int minArraySize = arraySize > obj.arraySize ? obj.arraySize : arraySize;
  for (unsigned int i = 0; i < minArraySize; i++) {
    if (ext_int[i] != obj.ext_int[i]) {
      return false;
    }
  }
  return true;
}


bool UnsignedExtendedInt::operator!=(const UnsignedExtendedInt& obj) const {
  return !(this->operator==(obj));
}


bool UnsignedExtendedInt::operator>(const UnsignedExtendedInt& obj) const {
  if (arraySize > obj.arraySize) {                // if calling object has upper bits not 0, then can't be equal
    for (unsigned int i = obj.arraySize; i < arraySize; i++) {
      if (ext_int[i] != 0) {
        return false;
      }
    }
  }
  if (obj.arraySize > arraySize) {                // if object being compared to has its upper bits not 0, then can't be equal
    for (unsigned int i = arraySize; i < obj.arraySize; i++) {
      if (obj.ext_int[i] != 0) {
        return false;
      }
    }
  }
  unsigned int minArraySize = arraySize > obj.arraySize ? obj.arraySize : arraySize;
  for (int i = minArraySize - 1; i >= 0; i--) {
    if (ext_int[i] > obj.ext_int[i]) {
      return true;
    }
    else if (ext_int[i] == obj.ext_int[i]) {
      continue;
    }
    else {
      return false;
    }
  }
  return false;
}


bool UnsignedExtendedInt::operator>=(const UnsignedExtendedInt& obj) const {
  if (arraySize > obj.arraySize) {                // if calling object has upper bits not 0, then can't be equal
    for (unsigned int i = obj.arraySize; i < arraySize; i++) {
      if (ext_int[i] != 0) {
        return false;
      }
    }
  }
  if (obj.arraySize > arraySize) {                // if object being compared to has its upper bits not 0, then can't be equal
    for (unsigned int i = arraySize; i < obj.arraySize; i++) {
      if (obj.ext_int[i] != 0) {
        return false;
      }
    }
  }
  unsigned int minArraySize = arraySize > obj.arraySize ? obj.arraySize : arraySize;
  for (int i = minArraySize - 1; i >= 0; i--) {
    if (ext_int[i] > obj.ext_int[i]) {
      return true;
    }
    else if (ext_int[i] == obj.ext_int[i]) {
      continue;
    }
    else {
      return false;
    }
  }
  return true;
}


bool UnsignedExtendedInt::operator<(const UnsignedExtendedInt& obj) const {
  if (arraySize > obj.arraySize) {                // if calling object has upper bits not 0, then can't be equal
    for (unsigned int i = obj.arraySize; i < arraySize; i++) {
      if (ext_int[i] != 0) {
        return false;
      }
    }
  }
  if (obj.arraySize > arraySize) {                // if object being compared to has its upper bits not 0, then can't be equal
    for (unsigned int i = arraySize; i < obj.arraySize; i++) {
      if (obj.ext_int[i] != 0) {
        return false;
      }
    }
  }
  unsigned int minArraySize = arraySize > obj.arraySize ? obj.arraySize : arraySize;
  for (int i = minArraySize - 1; i >= 0; i--) {
    if (ext_int[i] < obj.ext_int[i]) {
      return true;
    }
    else if (ext_int[i] == obj.ext_int[i]) {
      continue;
    }
    else {
      return false;
    }
  }
  return false;
}


bool UnsignedExtendedInt::operator<=(const UnsignedExtendedInt& obj) const {
  if (arraySize > obj.arraySize) {                // if calling object has upper bits not 0, then can't be equal
    for (unsigned int i = obj.arraySize; i < arraySize; i++) {
      if (ext_int[i] != 0) {
        return false;
      }
    }
  }
  if (obj.arraySize > arraySize) {                // if object being compared to has its upper bits not 0, then can't be equal
    for (unsigned int i = arraySize; i < obj.arraySize; i++) {
      if (obj.ext_int[i] != 0) {
        return false;
      }
    }
  }
  unsigned int minArraySize = arraySize > obj.arraySize ? obj.arraySize : arraySize;
  for (int i = minArraySize - 1; i >= 0; i--) {
    if (ext_int[i] < obj.ext_int[i]) {
      return true;
    }
    else if (ext_int[i] == obj.ext_int[i]) {
      continue;
    }
    else {
      return false;
    }
  }
  return true;
}


UnsignedExtendedInt UnsignedExtendedInt::operator>>(const UnsignedExtendedInt& obj) const {
  unsigned long long x = 0;
  unsigned long long y = 0;
  UnsignedExtendedInt returnValue(*this);
  unsigned long long shiftVal = obj.ext_int[0];                         // extract 64bits since that limits shift to 2^64
  shiftVal = (shiftVal > arraySize * 32 ? arraySize * 32 : shiftVal);   // bound maximum shift
  while (shiftVal > 0) {
    for (unsigned int i = 0; i < arraySize; i++) {
      x = returnValue.ext_int[i];                                       // get lower 32 bits
      x = x << 32;                                                      // left shift to upper 32bits
      x = x >> (shiftVal > 32 ? 32 : shiftVal);                         // perform shift
      returnValue.ext_int[i] = (x & 0xFFFFFFFF00000000) >> 32;          // upper 32bits are the result
      if (i > 0) {
        y = returnValue.ext_int[i - 1];                                 // get result of previous shift
        
        // lower 32bits of previous shift ORd with previous entry since these bits
        // were shifted into the adjacent 32bits
        returnValue.ext_int[i - 1] = (unsigned int) ((x & 0xFFFFFFFF) | y);
      }
    }
    shiftVal = (shiftVal >= 32 ? shiftVal - 32 : 0);
  }
  returnValue.clearUnusedMemory();
  return returnValue;
}


UnsignedExtendedInt UnsignedExtendedInt::operator<<(const UnsignedExtendedInt& obj) const {
  unsigned long long x = 0;
  unsigned long long y = 0;
  UnsignedExtendedInt returnValue(*this);
  unsigned long long shiftVal = obj.ext_int[0];                         // extract 64bits since that limits shift to 2^64
  shiftVal = (shiftVal > arraySize * 32 ? arraySize * 32 : shiftVal);   // bound maximum shift
  while (shiftVal > 0) {
    for (int i = arraySize - 1; i >= 0; i--) {
      x = returnValue.ext_int[i];                                       // get bottom 32 bits
      x = x << (shiftVal > 32 ? 32 : shiftVal);                         // perform shift
      returnValue.ext_int[i] = x & 0xFFFFFFFF;                          // lower 32bits are the result
      if (i < (int) arraySize - 1) {
        y = returnValue.ext_int[i + 1];                                 // get result of previous shift

        // upper 32bits of previous shift ORd with previous entry since these bits
        // were shifted into the adjacent 32bits
        returnValue.ext_int[i + 1] =
          (unsigned int) ((x & 0xFFFFFFFF00000000) >> 32 | y);
      }
    }
    shiftVal = (shiftVal >= 32 ? shiftVal - 32 : 0);
  }
  returnValue.clearUnusedMemory();
  return returnValue;
}


UnsignedExtendedInt UnsignedExtendedInt::operator&(const UnsignedExtendedInt& obj) const {
  unsigned int minArraySize = arraySize;
  UnsignedExtendedInt returnValue;
  if (arraySize != obj.arraySize) {
    minArraySize = (arraySize > obj.arraySize ? obj.arraySize : arraySize);
    returnValue.newArraySize(minArraySize);
  }
  for (unsigned int i = 0; i < minArraySize; i++) {
    returnValue.ext_int[i] = ext_int[i] & obj.ext_int[i];
  }
  return returnValue;
}


UnsignedExtendedInt UnsignedExtendedInt::operator|(const UnsignedExtendedInt& obj) const {
  unsigned int minArraySize = arraySize;
  UnsignedExtendedInt returnValue;
  if (arraySize != obj.arraySize) {
    minArraySize = (arraySize > obj.arraySize ? obj.arraySize : arraySize);
    returnValue.newArraySize(minArraySize);
  }
  for (unsigned int i = 0; i < minArraySize; i++) {
    returnValue.ext_int[i] = ext_int[i] | obj.ext_int[i];
  }
  return returnValue;
}


UnsignedExtendedInt UnsignedExtendedInt::operator^(const UnsignedExtendedInt& obj) const {
  unsigned int minArraySize = arraySize;
  UnsignedExtendedInt returnValue;
  if (arraySize != obj.arraySize) {
    minArraySize = (arraySize > obj.arraySize ? obj.arraySize : arraySize);
    returnValue.newArraySize(minArraySize);
  }
  for (unsigned int i = 0; i < minArraySize; i++) {
    returnValue.ext_int[i] = ext_int[i] ^ obj.ext_int[i];
  }
  return returnValue;
}


UnsignedExtendedInt& UnsignedExtendedInt::operator++() {
  *this = *this + 1ULL;
  return *this;
}


UnsignedExtendedInt UnsignedExtendedInt::operator++(int) {
  UnsignedExtendedInt returnValue(*this);
  *this = *this + 1ULL;
  return returnValue;
}


UnsignedExtendedInt& UnsignedExtendedInt::operator--() {
  *this = *this - 1ULL;
  return *this;
}


UnsignedExtendedInt UnsignedExtendedInt::operator--(int) {
  UnsignedExtendedInt returnValue(*this);
  *this = *this - 1ULL;
  return returnValue;
}


UnsignedExtendedInt UnsignedExtendedInt::operator~() const {
  UnsignedExtendedInt returnValue;
  returnValue.newArraySize(arraySize);
  for (unsigned int i = 0; i < arraySize; i++) {
    returnValue.ext_int[i] = ~ext_int[i];
  }
  return returnValue;
}



UnsignedExtendedInt UnsignedExtendedInt::divideModOperator(const UnsignedExtendedInt& divisor, const ExtendedInt::DIVIDE_OPERATION op) const {
  UnsignedExtendedInt returnValue;
  returnValue.newArraySize(arraySize);
  if (divisor == 0) {
    throw DivideByZeroException();
  }
  if (*this < divisor) {                                // if dividend is smaller than divisor (e.g. 10 / 20 = 0)
    if (op == ExtendedInt::DIVIDE_OP) {
      return returnValue;
    }
    else {                                              // op == ExtendedInt::MOD_OP
      return *this;
    }
  }
  unsigned int maxArraySize = (arraySize > divisor.arraySize ? arraySize : divisor.arraySize);
  UnsignedExtendedInt dividend;
  UnsignedExtendedInt nonConstDivisor(divisor);
  if (arraySize > divisor.arraySize) {                  // make sure both arrays are of the same size
    nonConstDivisor.increaseArraySizeTo(maxArraySize);
  }
  else if (divisor.arraySize > arraySize) {
    dividend.newArraySize(maxArraySize);
  }
  UnsignedExtendedInt maskBit;
  maskBit.newArraySize(maxArraySize);
  maskBit.setValueAtIndex(1, 0);
  int i = 32 * maxArraySize;
  maskBit = maskBit << (i - 1);
  while (--i >= 0) {
    if (nonConstDivisor > dividend) {
      // extract bit in position i starting with MSBit to perform long division
      dividend = (((*this & maskBit) >> i) | (dividend << 1));
      maskBit = maskBit >> 1;
    }
    else {
      returnValue = returnValue | (maskBit << 1);
      dividend = dividend - nonConstDivisor;
      i++;
    }
  }
  
  // extract bit 0 of the quotient
  if (nonConstDivisor <= dividend) {
    maskBit.setValueAtIndex(1, 0);
    returnValue = returnValue | maskBit;
    dividend = dividend - nonConstDivisor;              // remainder
  }
  if (op == ExtendedInt::DIVIDE_OP) {
    return returnValue;                                 // return result
  }
  return dividend;                                      // return remainder
}
