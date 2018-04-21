#include "UnsignedExtendedInt.h"


UnsignedExtendedInt::UnsignedExtendedInt(unsigned int arrSize) : ExtendedInt(arrSize) {
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


UnsignedExtendedInt::~UnsignedExtendedInt() {}
