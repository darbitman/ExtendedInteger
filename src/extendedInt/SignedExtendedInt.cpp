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
    ext_int[arraySize - 1] = 0x80000000;
  }
}


SignedExtendedInt::SignedExtendedInt(int obj): ExtendedInt(true) {
  ext_int[0] = obj & 0xFFFFFFFF;
  if (obj < 0) {
    ext_int[arraySize - 1] = 0x80000000;
  }
}


SignedExtendedInt::SignedExtendedInt(const char* s) : ExtendedInt(true) {
  // TODO
}


SignedExtendedInt::~SignedExtendedInt() {}


//SignedExtendedInt SignedExtendedInt::operator=(const SignedExtendedInt& obj) {
//  if (arraySize != obj.arraySize) {
//    if (arraySize > obj.arraySize) {
//      decreaseArraySizeTo(obj.arraySize);
//    }
//    else {
//      increaseArraySizeTo(obj.arraySize);
//    }
//  }
//  for (unsigned int i = 0; i < arraySize; i++) {
//    ext_int[i] = obj.ext_int[i];
//  }
//  return *this;
//}


SignedExtendedInt SignedExtendedInt::operator+(const SignedExtendedInt& obj) const {
  SignedExtendedInt obj1(*this);                                // make local copies to allow the objects to change size
  SignedExtendedInt obj2(obj);
  obj1.increaseArraySizeTo(obj1.arraySize + 1);                 // need extra word to store signs in case of overflow
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
