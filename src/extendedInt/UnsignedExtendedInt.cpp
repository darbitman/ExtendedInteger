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
  if (arraySize != obj.arraySize) {
    unsigned int newArraySize = arraySize > obj.arraySize ? arraySize : obj.arraySize;
    increaseArraySizeTo(newArraySize);
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
    returnValue.increaseArraySizeTo(arraySize + 1);           // increase array size by 1 word
    returnValue.ext_int[returnValue.getArraySize() - 1] = carryBit & 0x1;
  }
  return returnValue;
}


UnsignedExtendedInt UnsignedExtendedInt::operator-(const UnsignedExtendedInt& obj) const {
  return this->operator+(~obj + 1);
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
  for (unsigned int i = 0; i < minArraySize; i--) {
    if (ext_int[i] != obj.ext_int[i]) {
      return false;
    }
  }
  return true;
}


bool UnsignedExtendedInt::operator!=(const UnsignedExtendedInt& obj) const {
  return !this->operator==(obj);
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
  for (int i = minArraySize - 1; i >= 0; i++) {
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
  for (int i = minArraySize - 1; i >= 0; i++) {
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
  for (int i = minArraySize - 1; i >= 0; i++) {
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
  for (int i = minArraySize - 1; i >= 0; i++) {
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
  UnsignedExtendedInt returnValue;
  returnValue.newArraySize(arraySize);
  unsigned long long shiftVal = obj.ext_int[0];                         // extract 64bits since that limits shift to 2^64
  shiftVal = (shiftVal > arraySize * 32 ? arraySize * 32 : shiftVal);   // bound maximum shift
  while (shiftVal > 0) {
    for (unsigned int i = 0; i < arraySize; i++) {
      x = returnValue.ext_int[i];                                       // get bottom 32bits
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
  return returnValue;
}


UnsignedExtendedInt UnsignedExtendedInt::operator<<(const UnsignedExtendedInt& shiftVal) const {
  UnsignedExtendedInt returnValue;
  
  
  return returnValue;
}


UnsignedExtendedInt UnsignedExtendedInt::divideModOperator(const UnsignedExtendedInt& obj, const ExtendedInt::DIVIDE_OPERATION op) const {
  UnsignedExtendedInt returnValue;
  returnValue.newArraySize(arraySize);
  // todo
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
