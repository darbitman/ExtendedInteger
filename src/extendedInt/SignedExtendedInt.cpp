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
  // TODO
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
    result = x + y + carryBit;                                  // perform 32bit addition of both operands and carrybit from previous addition
    returnValue.ext_int[i] = result & 0xFFFFFFFF;               // extract bottom 32bits of the result of the addition
    carryBit = (result & 0x100000000) >> 32;                    // extract the carry bit if it exists
  }
  if (carryBit) {                                               // if carryBit overflows, need to increase array size
    returnValue.increaseArraySizeTo(returnValue.arraySize + 1); // increase array size by 1 word
    returnValue.ext_int[returnValue.getArraySize() - 1] = carryBit & 0x1;
  }
  returnValue.clearUnusedMemory();
  return returnValue;
}


//SignedExtendedInt SignedExtendedInt::operator-(SignedExtendedInt& obj) const {
//  SignedExtendedInt returnValue(this->operator+(~obj + 1));
//  return returnValue;
//}


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
  lhsObj.increaseArraySizeTo(maxArraySize);
  rhsObj.increaseArraySizeTo(maxArraySize);
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
