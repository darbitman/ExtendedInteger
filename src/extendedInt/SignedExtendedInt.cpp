#include "SignedExtendedInt.h"


SignedExtendedInt::SignedExtendedInt() : ExtendedInt(true) {}


SignedExtendedInt::SignedExtendedInt(const SignedExtendedInt& obj) : ExtendedInt(true, obj.arraySize) {
  for (unsigned int i = 0; i < arraySize; i++) {
    ext_int[i] = obj.ext_int[i];
  }
}


SignedExtendedInt::SignedExtendedInt(long long obj): ExtendedInt(true) {
  ext_int[0] = obj & 0xFFFFFFFF;
  ext_int[1] = (obj >> 32) & 0xFFFFFFFF;
  if (obj < 0) {
    for (unsigned int i = 2; i < arraySize; i++) {    // fill in 1's if negative
      ext_int[i] = 0xFFFFFFFF;
    }
  }
}


SignedExtendedInt::SignedExtendedInt(int obj): ExtendedInt(true) {
  ext_int[0] = obj & 0xFFFFFFFF;
  if (obj < 0) {
    for (unsigned int i = 1; i < arraySize; i++) {    // fill in 1's if negative
      ext_int[i] = 0xFFFFFFFF;
    }
  }
}


SignedExtendedInt::SignedExtendedInt(const char* s) : ExtendedInt(true) {
  stringToExtendedInt(s);
}


SignedExtendedInt::~SignedExtendedInt() {}


SignedExtendedInt SignedExtendedInt::operator=(const SignedExtendedInt& obj) {
  // will need to make sure both objects are of the same size
  // to ensure no data loss and not accessing unallocated memory
  if (arraySize != obj.arraySize) {
    newArraySize(obj.arraySize);
  }
  for (unsigned int i = 0; i < arraySize; i++) {
    ext_int[i] = obj.ext_int[i];
  }
  return *this;
}


SignedExtendedInt SignedExtendedInt::operator+(const SignedExtendedInt& obj) const {
  SignedExtendedInt obj1(*this);                                // make local copies to allow the objects to change size
  SignedExtendedInt obj2(obj);
  obj1.increaseArraySizeTo(obj1.arraySize + 1);                 // need extra word to store sign bits in case of overflow
  obj2.increaseArraySizeTo(obj2.arraySize + 1);
  bool isNegativeObj1 = false;
  bool isNegativeObj2 = false;
  if (obj1.ext_int[obj1.arraySize - 1] & 0x80000000) {
    isNegativeObj1 = true;
  }
  if (obj2.ext_int[obj2.arraySize - 1] & 0x80000000) {
    isNegativeObj2 = true;
  }
  unsigned int maxArraySize = (obj1.arraySize > obj2.arraySize ? obj1.arraySize : obj2.arraySize);
  SignedExtendedInt returnValue;
  returnValue.newArraySize(maxArraySize);
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
    result = x + y + carryBit;                                    // perform 32bit addition of both operands and carrybit from previous addition
    returnValue.ext_int[i] = result & 0xFFFFFFFF;                 // extract bottom 32bits of the result of the addition
    carryBit = (result & 0x100000000) >> 32;                      // extract the carry bit if it exists
  }
                                                                  // carryBit applies only when both are positive
  if (!isNegativeObj1 && !isNegativeObj2 && carryBit) {           // if overflow (carryBit), need to increase array size
    returnValue.increaseArraySizeTo(returnValue.arraySize + 1);   // increase array size by 1 word
    returnValue.ext_int[returnValue.getArraySize() - 1] = carryBit & 0x1;
  }
  returnValue.clearUnusedMemory();
  return returnValue;
}


SignedExtendedInt SignedExtendedInt::operator-(const SignedExtendedInt& obj) const {
  SignedExtendedInt obj2(obj);
  obj2.increaseArraySizeTo(obj2.arraySize + 1);                   // if most negative value, adding 1 will cause an error
                                                                  // for an 8bit signed number, range is -128 to 127
                                                                  // so getting a positive 128 if the input is -128 requires an extra array entry
  SignedExtendedInt returnValue(this->operator+(~obj2 + 1));
  return returnValue;
}


SignedExtendedInt SignedExtendedInt::operator*(const SignedExtendedInt& obj) const {
  SignedExtendedInt obj1(*this);
  SignedExtendedInt obj2(obj);
  // if most negative value, adding 1 will not yield the most positive value
  // when negating in order to multiply positive numbers
  // e.g. an 8bit signed number, range is -128 to 127
  // e.g. negating -128 and adding 1 results in -128
  obj1.increaseArraySizeTo(obj1.arraySize + 1);
  obj2.increaseArraySizeTo(obj2.arraySize + 1);
  bool isNegativeObj1 = obj1.ext_int[obj1.arraySize - 1] & 0x80000000;
  bool isNegativeObj2 = obj2.ext_int[obj2.arraySize - 1] & 0x80000000;
  if (isNegativeObj1) {
    obj1 = ~obj1 + 1;
  };
  if (isNegativeObj2) {
    obj2 = ~obj2 + 1;
  }
  unsigned int resultArraySize = obj1.arraySize + obj2.arraySize;
  SignedExtendedInt returnValue;
  returnValue.newArraySize(resultArraySize);
  SignedExtendedInt intermediateResult;
  intermediateResult.newArraySize(resultArraySize);
  unsigned int leftShiftValue = 0;
  unsigned long long x = 0;
  unsigned long long y = 0;
  unsigned long long z = 0;
  for (unsigned int i = 0; i < obj1.arraySize; i++) {
    x = obj1.ext_int[i];
    for (unsigned int j = 0; j < obj2.arraySize; j++) {
      leftShiftValue = i + j;
      y = obj2.ext_int[j];
      z = x * y;
      if (leftShiftValue > 0) {                                                 // ensure valid memory can be accessed
        intermediateResult.ext_int[leftShiftValue - 1] = 0;                     // clear previously set lower 32bits because they will introduce a summation error
      }
      intermediateResult.ext_int[leftShiftValue] = z & 0xFFFFFFFF;              // extract lower 32bits of result
      intermediateResult.ext_int[leftShiftValue + 1] = (z >> 32) & 0xFFFFFFFF;  // extract upper 32bits of results
      returnValue = returnValue + intermediateResult;                           // add to previous summation
    }
  }
  if (isNegativeObj1 ^ isNegativeObj2) {                                         // result is negative if one of the ext_ints is negative, otherwise positive (XOR function)
    returnValue = ~returnValue + 1;
  }
  return returnValue;
}


SignedExtendedInt SignedExtendedInt::operator/(const SignedExtendedInt& obj) const {
  return divideModOperator(obj, ExtendedInt::DIVIDE_OP);
}


SignedExtendedInt SignedExtendedInt::operator%(const SignedExtendedInt& obj) const {
  return divideModOperator(obj, ExtendedInt::MOD_OP);
}


bool SignedExtendedInt::operator==(const SignedExtendedInt& obj) const {
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


bool SignedExtendedInt::operator!=(const SignedExtendedInt& obj) const {
  return !(this->operator==(obj));
}


bool SignedExtendedInt::operator>(const SignedExtendedInt& obj) const {
  SignedExtendedInt lhsObj(*this);
  SignedExtendedInt rhsObj(obj);
  unsigned int maxArraySize = (lhsObj.arraySize > rhsObj.arraySize ? lhsObj.arraySize : rhsObj.arraySize);
  if (lhsObj.arraySize != maxArraySize) {
    lhsObj.increaseArraySizeTo(maxArraySize);
  }
  if (rhsObj.arraySize != maxArraySize) {
    rhsObj.increaseArraySizeTo(maxArraySize);
  }
  bool isNegativeLhs = lhsObj.ext_int[lhsObj.arraySize - 1] & 0x80000000;
  bool isNegativeRhs = rhsObj.ext_int[rhsObj.arraySize - 1] & 0x80000000;
  if (isNegativeLhs && !isNegativeRhs) {
    return false;
  }
  else if (isNegativeRhs && !isNegativeLhs) {
    return true;
  }
  else {
    for (int i = maxArraySize - 1; i >= 0; i--) {
      if (lhsObj.ext_int[i] > rhsObj.ext_int[i]) {
        return true;
      }
      else if (lhsObj.ext_int[i] == rhsObj.ext_int[i]) {
        continue;
      }
      else {
        return false;
      }
    }
    return false;
  }
}


bool SignedExtendedInt::operator>=(const SignedExtendedInt& obj) const {
  SignedExtendedInt lhsObj(*this);
  SignedExtendedInt rhsObj(obj);
  unsigned int maxArraySize = (lhsObj.arraySize > rhsObj.arraySize ? lhsObj.arraySize : rhsObj.arraySize);
  if (lhsObj.arraySize != maxArraySize) {
    lhsObj.increaseArraySizeTo(maxArraySize);
  }
  if (rhsObj.arraySize != maxArraySize) {
    rhsObj.increaseArraySizeTo(maxArraySize);
  }
  bool isNegativeLhs = lhsObj.ext_int[lhsObj.arraySize - 1] & 0x80000000;
  bool isNegativeRhs = rhsObj.ext_int[rhsObj.arraySize - 1] & 0x80000000;
  if (isNegativeLhs && !isNegativeRhs) {
    return false;
  }
  else if (isNegativeRhs && !isNegativeLhs) {
    return true;
  }
  else {
    for (int i = maxArraySize - 1; i >= 0; i--) {
      if (lhsObj.ext_int[i] > rhsObj.ext_int[i]) {
        return true;
      }
      else if (lhsObj.ext_int[i] == rhsObj.ext_int[i]) {
        continue;
      }
      else {
        return false;
      }
    }
    return true;
  }
}


bool SignedExtendedInt::operator<(const SignedExtendedInt& obj) const {
  SignedExtendedInt lhsObj(*this);
  SignedExtendedInt rhsObj(obj);
  unsigned int maxArraySize = (lhsObj.arraySize > rhsObj.arraySize ? lhsObj.arraySize : rhsObj.arraySize);
  if (lhsObj.arraySize != maxArraySize) {
    lhsObj.increaseArraySizeTo(maxArraySize);
  }
  if (rhsObj.arraySize != maxArraySize) {
    rhsObj.increaseArraySizeTo(maxArraySize);
  }
  bool isNegativeLhs = lhsObj.ext_int[lhsObj.arraySize - 1] & 0x80000000;
  bool isNegativeRhs = rhsObj.ext_int[rhsObj.arraySize - 1] & 0x80000000;
  if (isNegativeLhs && !isNegativeRhs) {
    return true;
  }
  else if (isNegativeRhs && !isNegativeLhs) {
    return false;
  }
  else {
    for (int i = maxArraySize - 1; i >= 0; i--) {
      if (lhsObj.ext_int[i] < rhsObj.ext_int[i]) {
        return true;
      }
      else if (lhsObj.ext_int[i] == rhsObj.ext_int[i]) {
        continue;
      }
      else {
        return false;
      }
    }
    return false;
  }
}


bool SignedExtendedInt::operator<=(const SignedExtendedInt& obj) const {
  SignedExtendedInt lhsObj(*this);
  SignedExtendedInt rhsObj(obj);
  unsigned int maxArraySize = (lhsObj.arraySize > rhsObj.arraySize ? lhsObj.arraySize : rhsObj.arraySize);
  if (lhsObj.arraySize != maxArraySize) {
    lhsObj.increaseArraySizeTo(maxArraySize);
  }
  if (rhsObj.arraySize != maxArraySize) {
    rhsObj.increaseArraySizeTo(maxArraySize);
  }
  bool isNegativeLhs = lhsObj.ext_int[lhsObj.arraySize - 1] & 0x80000000;
  bool isNegativeRhs = rhsObj.ext_int[rhsObj.arraySize - 1] & 0x80000000;
  if (isNegativeLhs && !isNegativeRhs) {
    return true;
  }
  else if (isNegativeRhs && !isNegativeLhs) {
    return false;
  }
  else {
    for (int i = maxArraySize - 1; i >= 0; i--) {
      if (lhsObj.ext_int[i] < rhsObj.ext_int[i]) {
        return true;
      }
      else if (lhsObj.ext_int[i] == rhsObj.ext_int[i]) {
        continue;
      }
      else {
        return false;
      }
    }
    return true;
  }
}

SignedExtendedInt SignedExtendedInt::operator>>(const SignedExtendedInt& obj) const {
  if (obj.ext_int[obj.arraySize - 1] & 0x80000000) {
    throw NegativeShiftValueException();
  }
  unsigned long long x = 0;
  unsigned long long y = 0;
  SignedExtendedInt returnValue(*this);
  bool isNegativeLhs = false;
  if (ext_int[arraySize - 1] & 0x80000000) {
    isNegativeLhs = true;
  }
  unsigned long long signBits = 0;
  unsigned long long shiftVal = obj.ext_int[0];                         // extract 64bits since that limits shift to 2^64
  shiftVal = (shiftVal > arraySize * 32 ? arraySize * 32 : shiftVal);   // bound maximum shift
  while (shiftVal > 0) {
    for (unsigned int i = 0; i < returnValue.arraySize; i++) {
      x = returnValue.ext_int[i];                                       // get lower 32 bits
      x = x << 32;                                                      // left shift to upper 32bits
      x = x >> (shiftVal > 32 ? 32 : shiftVal);                         // perform shift

      // if int to shift is negative, want to preserve MSBits to indicate its sign
      // so shift in 1's
      if ((i == arraySize - 1) && isNegativeLhs) {
        signBits = 0xFFFFFFFF00000000;
        signBits = signBits >> (shiftVal > 32 ? 32 : shiftVal);
        signBits = signBits << 32;                                      // upper word contains sign bits to OR
        x = x | (signBits & 0xFFFFFFFF00000000);
      }
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


SignedExtendedInt SignedExtendedInt::operator<<(const SignedExtendedInt& obj) const {
  if (obj.ext_int[obj.arraySize - 1] & 0x80000000) {
    throw NegativeShiftValueException();
  }
  unsigned long long x = 0;
  unsigned long long y = 0;
  SignedExtendedInt returnValue(*this);
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
  return returnValue;
}


SignedExtendedInt SignedExtendedInt::operator&(const SignedExtendedInt& obj) const {
  unsigned int maxArraySize = (arraySize > obj.arraySize ? arraySize : obj.arraySize);
  unsigned int minArraySize = (arraySize > obj.arraySize ? obj.arraySize : arraySize);
  SignedExtendedInt returnValue;
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


SignedExtendedInt SignedExtendedInt::operator|(const SignedExtendedInt& obj) const {
  unsigned int maxArraySize = (arraySize > obj.arraySize ? arraySize : obj.arraySize);
  SignedExtendedInt returnValue;
  if (returnValue.arraySize != maxArraySize) {
    returnValue.newArraySize(maxArraySize);
  }
  SignedExtendedInt lhs(*this);
  SignedExtendedInt rhs(obj);
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


SignedExtendedInt SignedExtendedInt::operator^(const SignedExtendedInt& obj) const {
  unsigned int maxArraySize = (arraySize > obj.arraySize ? arraySize : obj.arraySize);
  SignedExtendedInt returnValue;
  if (returnValue.arraySize != maxArraySize) {
    returnValue.newArraySize(maxArraySize);
  }
  SignedExtendedInt lhs(*this);
  SignedExtendedInt rhs(obj);
  if (lhs.arraySize != maxArraySize) {
    lhs.increaseArraySizeTo(maxArraySize);
  }
  if (rhs.arraySize != maxArraySize) {
    rhs.increaseArraySizeTo(maxArraySize);
  }
  for (unsigned int i = 0; i < maxArraySize; i++) {
    returnValue.ext_int[i] = lhs.ext_int[i] ^ rhs.ext_int[i];
  }
  return returnValue;
}


SignedExtendedInt& SignedExtendedInt::operator++() {
  *this = *this + 1;
  return *this;
}


SignedExtendedInt SignedExtendedInt::operator++(int) {
  SignedExtendedInt returnValue(*this);
  *this = *this + 1;
  return returnValue;
}


SignedExtendedInt& SignedExtendedInt::operator--() {
  *this = *this - 1;
  return *this;
}


SignedExtendedInt SignedExtendedInt::operator--(int) {
  SignedExtendedInt returnValue(*this);
  *this = *this - 1;
  return returnValue;
}


SignedExtendedInt SignedExtendedInt::operator~() const {
  SignedExtendedInt returnValue;
  returnValue.newArraySize(arraySize);
  for (unsigned int i = 0; i < arraySize; i++) {
    returnValue.ext_int[i] = ~ext_int[i];
  }
  return returnValue;
}


std::ostream& operator<<(std::ostream& os, const SignedExtendedInt& obj) {
  os << obj.extendedIntToString();
  return os;
}


SignedExtendedInt SignedExtendedInt::divideModOperator(const SignedExtendedInt& divisor, const ExtendedInt::DIVIDE_OPERATION op) const {
  SignedExtendedInt returnValue;
  if (divisor == 0) {
    throw DivideByZeroException();
  }
  SignedExtendedInt obj1(*this);
  SignedExtendedInt obj2(divisor);
  // if most negative value, adding 1 will not yield the most positive value
  // when negating in order to multiply positive numbers
  // e.g. an 8bit signed number, range is -128 to 127
  // e.g. negating -128 and adding 1 results in -128
  obj1.increaseArraySizeTo(obj1.arraySize + 1);
  obj2.increaseArraySizeTo(obj2.arraySize + 1);
  bool isNegativeObj1 = obj1.ext_int[obj1.arraySize - 1] & 0x80000000;
  bool isNegativeObj2 = obj2.ext_int[obj2.arraySize - 1] & 0x80000000;
  if (isNegativeObj1) {
    obj1 = ~obj1 + 1;
  }
  if (isNegativeObj2) {
    obj2 = ~obj2 + 1;
  }
  if (obj1 < obj2) {                                // if dividend is smaller than divisor (e.g. 10 / 20 = 0)
    if (op == ExtendedInt::DIVIDE_OP) {
      return returnValue;
    }
    else {                                              // op == ExtendedInt::MOD_OP
      return obj1;
    }
  }
  unsigned int maxArraySize = (obj1.arraySize > obj2.arraySize ? obj1.arraySize : obj2.arraySize);
  if (obj1.arraySize != maxArraySize) {
    obj1.increaseArraySizeTo(maxArraySize);
  }
  if (obj2.arraySize != maxArraySize) {
    obj2.increaseArraySizeTo(maxArraySize);
  }
  returnValue.newArraySize(maxArraySize);
  SignedExtendedInt partialDividend;
  if (partialDividend.arraySize != maxArraySize) {
    partialDividend.newArraySize(maxArraySize);
  }
  SignedExtendedInt maskBit;
  maskBit.newArraySize(maxArraySize + 1);               // needs to be larger so that when MSBit is shifted right, a sign bit isn't shifted in.
  maskBit.setValueAtIndex(1, 0);
  int i = 32 * maxArraySize;
  maskBit = maskBit << (i - 1);
  while (--i >= 0) {
    if (obj2 > partialDividend) {

      // extract bit in position i starting with MSBit to perform long division
      partialDividend = (((obj1 & maskBit) >> i) | (partialDividend << 1));
      maskBit = maskBit >> 1;
    }
    else {
      returnValue = returnValue | (maskBit << 1);
      partialDividend = partialDividend - obj2;
      i++;
    }
  }
  // extract bit 0 of the quotient
  if (obj2 <= partialDividend) {
    maskBit.setValueAtIndex(1, 0);
    returnValue = returnValue | maskBit;
    partialDividend = partialDividend - obj2;           // remainder
  }
  if (op == ExtendedInt::DIVIDE_OP) {
    if (isNegativeObj1 ^ isNegativeObj2) {
      returnValue = ~returnValue + 1;
      returnValue.clearUnusedMemory();
      return returnValue;
    }
    returnValue.clearUnusedMemory();
    return returnValue;                                 // return result
  }
  if (isNegativeObj1 ^ isNegativeObj2) {
    partialDividend = ~partialDividend + 1;
    partialDividend.clearUnusedMemory();
    return partialDividend;
  }
  partialDividend.clearUnusedMemory();
  return partialDividend;                               // return remainder
}


void SignedExtendedInt::stringToExtendedInt(const char* s) {
  bool isNegative = false;
  bool isHexVal = false;
  unsigned int strLength = 0;
  while (s[strLength] != 0) {                           // compute string length
    strLength++;
  }
  if (!validateString(s, strLength)) {
    throw InputStringInvalidCharacterException();
  }
  if (s[0] == '0' && s[1] == 'x') {
    isHexVal = true;
  }
  if (s[0] == '-') {
    isNegative = true;
  }
  SignedExtendedInt baseValue(10);
  SignedExtendedInt powersOfBaseValue(1);
  if (isHexVal) {
    baseValue.setValueAtIndex(16, 0);
  }
  SignedExtendedInt readInt;
  for (int i = strLength - 1; i >= 0; i--) {
    if (isNegative && i == 0) {                         // if sign bit, ignore bit 0 for ('-')
      continue;
    }
    if (isHexVal && (i == 0 || i == 1)) {               // if hex value, ignore bit 0 and bit 1 for ('0x')
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
  if (isNegative) {
    increaseArraySizeTo(arraySize + 1);
    *this = (~(*this) + 1);
    clearUnusedMemory();
  }
}


std::string SignedExtendedInt::extendedIntToString() const {
  bool isNegative = false;
  std::string extIntString;
  SignedExtendedInt dividend(*this);
  if (ext_int[arraySize - 1] & 0x80000000) {
    isNegative = true;
    dividend = ~dividend + 1;
  }
  SignedExtendedInt remainder;
  const SignedExtendedInt TEN(10);
  while (dividend > 0) {
    remainder = dividend % TEN;
    dividend = dividend / TEN;
    extIntString = (char) ((remainder.ext_int[0] & 0xFF) + 48) + extIntString;
  }
  if (isNegative) {
    extIntString = '-' + extIntString;
  }
  return extIntString;
}

