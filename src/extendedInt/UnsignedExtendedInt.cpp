#include "UnsignedExtendedInt.h"


UnsignedExtendedInt::UnsignedExtendedInt() : ExtendedInt() {}


UnsignedExtendedInt::UnsignedExtendedInt(const UnsignedExtendedInt& obj) : ExtendedInt(obj.arraySize) {
  for (unsigned int i = 0; i < arraySize; i++) {
    ext_int[i] = obj.ext_int[i];
  }
}


UnsignedExtendedInt::UnsignedExtendedInt(unsigned long long obj) : ExtendedInt() {
  ext_int[0] = obj & 0xFFFFFFFF;
  ext_int[1] = (obj >> 32) & 0xFFFFFFFF;
}


UnsignedExtendedInt::UnsignedExtendedInt(long long obj) : ExtendedInt() {
  ext_int[0] = obj & 0xFFFFFFFF;
}


UnsignedExtendedInt::UnsignedExtendedInt(int obj) : ExtendedInt() {
  ext_int[0] = obj & 0xFFFFFFFF;
}


UnsignedExtendedInt::UnsignedExtendedInt(const char* s) : ExtendedInt() {
  try {
    stringToExtendedInt(s);
  }
  catch (const Exception& e) {
    e.printError();
  }
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
  return *this;
}


UnsignedExtendedInt::~UnsignedExtendedInt() {}


UnsignedExtendedInt UnsignedExtendedInt::operator+(const UnsignedExtendedInt& obj) const {
  unsigned int maxArraySize = (arraySize > obj.arraySize ? arraySize : obj.arraySize);
  UnsignedExtendedInt returnValue;
  returnValue.newArraySize(maxArraySize);
  UnsignedExtendedInt obj1(*this);                          // make local copies to allow the objects to change size
  UnsignedExtendedInt obj2(obj);                            // make local copies to allow the objects to change size
  if (obj1.arraySize > obj2.arraySize) {
    obj2.increaseArraySizeTo(maxArraySize);
  }
  else if (obj2.arraySize > obj1.arraySize) {
    obj1.increaseArraySizeTo(maxArraySize);
  }
  unsigned long long x = 0;
  unsigned long long y = 0;
  unsigned long long result = 0;
  unsigned long long carryBit = 0;
  for (unsigned int i = 0; i < maxArraySize; i++) {
    x = obj1.ext_int[i];
    y = obj2.ext_int[i];
    result = x + y + carryBit;                              // perform 32bit addition of left and right operand plus carry bit from previous addition
    returnValue.ext_int[i] = result & 0xFFFFFFFF;           // extract bottom 32bits of the result of the addition
    carryBit = (result & 0x100000000) >> 32;                // extract the carry bit if it exists
  }
  if (carryBit) {                                           // if carryBit overflows, need to increase array size
    returnValue.increaseArraySizeTo(arraySize + 1);         // increase array size by 1 word
    returnValue.ext_int[returnValue.getArraySize() - 1] = carryBit & 0x1;
  }
  returnValue.clearUnusedMemory();
  return returnValue;
}


UnsignedExtendedInt UnsignedExtendedInt::operator-(const UnsignedExtendedInt& obj) const {
  UnsignedExtendedInt returnValue(this->operator+(~obj + 1));
  returnValue.decreaseArraySizeTo(returnValue.arraySize - 1);   // subtraction can sometimes lead to overflow, so need to delete the carry bit that was generated
  return returnValue;
}


UnsignedExtendedInt UnsignedExtendedInt::operator*(const UnsignedExtendedInt& obj) const {
  unsigned int resultArraySize = arraySize + obj.arraySize;
  UnsignedExtendedInt returnValue;
  returnValue.newArraySize(resultArraySize);
  unsigned int leftShiftValue = 0;
  unsigned long long x = 0;
  unsigned long long y = 0;
  unsigned long long z = 0;
  UnsignedExtendedInt intermediateResult;
  intermediateResult.newArraySize(resultArraySize);
  for (unsigned int i = 0; i < arraySize; i++) {
    for (unsigned int j = 0; j < obj.arraySize; j++) {
      leftShiftValue = i + j;
      x = ext_int[i];
      y = obj.ext_int[j];
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
        return true;
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
  unsigned int maxArraySize = (arraySize > obj.arraySize ? arraySize : obj.arraySize);
  unsigned int minArraySize = (arraySize > obj.arraySize ? obj.arraySize : arraySize);
  UnsignedExtendedInt returnValue;
  if (returnValue.arraySize != maxArraySize) {
    returnValue.newArraySize(maxArraySize);
  }
  // need to AND only the same indices
  // any array entries between minArraySize and maxArraySize will be 0 so don't need to loop over those
  for (unsigned int i = 0; i < minArraySize; i++) {
    returnValue.ext_int[i] = ext_int[i] & obj.ext_int[i];
  }
  return returnValue;
}


UnsignedExtendedInt UnsignedExtendedInt::operator|(const UnsignedExtendedInt& obj) const {
  unsigned int maxArraySize = (arraySize > obj.arraySize ? arraySize : obj.arraySize);
  UnsignedExtendedInt returnValue;
  if (returnValue.arraySize != maxArraySize) {
    returnValue.newArraySize(maxArraySize);
  }
  UnsignedExtendedInt lhs(*this);
  UnsignedExtendedInt rhs(obj);
  if (lhs.arraySize != maxArraySize) {
    lhs.increaseArraySizeTo(maxArraySize);
  }
  if (rhs.arraySize != maxArraySize) {
    rhs.increaseArraySizeTo(maxArraySize);
  }
  for (unsigned int i = 0; i < maxArraySize; i++) {
    returnValue.ext_int[i] = lhs.ext_int[i] | rhs.ext_int[i];
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
  if (dividend.arraySize > nonConstDivisor.arraySize) {                  // make sure both arrays are of the same size
    nonConstDivisor.increaseArraySizeTo(maxArraySize);
  }
  else if (nonConstDivisor.arraySize > dividend.arraySize) {
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


void UnsignedExtendedInt::stringToExtendedInt(const char* s) {
  bool isHexVal = false;
  unsigned int strLength = 0;
  while (s[strLength] != 0) {                           // compute string length
    strLength++;
  }
  // TODO Validate string here

  if (s[0] == '0' && s[1] == 'x') {
    isHexVal = true;
  }
  UnsignedExtendedInt baseValue(10);
  UnsignedExtendedInt powersOfBaseValue(1);
  if (isHexVal) {
    baseValue.setValueAtIndex(16, 0);
  }
  UnsignedExtendedInt readInt;                          // single char -> int
  for (int i = strLength - 1; i >= 0; i--) {
    if (isHexVal && (i == 0 || i == 1)) {                // if hex value, ignore bit 0 and bit 1 for ('0x')
      continue;
    }
    if (isHexVal) {
      // TODO implement conversion from hex input
    }
    else {
      readInt.setValueAtIndex(s[i] - '0', 0);
    }
    *this = *this + (powersOfBaseValue * readInt);
    powersOfBaseValue = powersOfBaseValue * baseValue;
  }
}


std::string UnsignedExtendedInt::extendedIntToString() const {
  std::string extIntString;
  UnsignedExtendedInt dividend(*this);
  UnsignedExtendedInt remainder;
  remainder.newArraySize(arraySize);
  UnsignedExtendedInt TEN(10);
  TEN.increaseArraySizeTo(arraySize);
  while (dividend > 0) {
    remainder = dividend % TEN;
    dividend = dividend / TEN;
    extIntString = (char) ((remainder.ext_int[0] & 0xFF) + 48) + extIntString;
  }
  return extIntString;
}


std::ostream& operator<<(std::ostream& os, const UnsignedExtendedInt& obj) {
  os << obj.extendedIntToString();
  return os;
}