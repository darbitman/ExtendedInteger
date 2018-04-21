#include "ExtendedInt.h"


void ExtendedInt::setValueAtIndex(const unsigned long long val, const unsigned int index) {
  if (index >= arraySize) {
    throw IndexOutOfBoundsException();
  }
  ext_int[index] = val & 0xFFFFFFFF;
}


unsigned int ExtendedInt::getValueAtIndex(const unsigned int index) const {
  if (index >= arraySize) {
    throw IndexOutOfBoundsException();
  }
  return ext_int[index];
}


unsigned int ExtendedInt::getArraySize() const {
  return arraySize;
}


ExtendedInt::ExtendedInt(unsigned int arrSize) : arraySize(arrSize) {}


ExtendedInt::~ExtendedInt() {
  delete[] ext_int;
}


void ExtendedInt::clearValue() {
  for (unsigned int i = 0; i < arraySize; i++) {
    ext_int[i] = 0;
  }
}


bool ExtendedInt::validateString(const char* s, unsigned int strLen) {
  return getNFAInstance().validateTxt(s, strLen);
}


NFA& ExtendedInt::getNFAInstance() {
  static std::string regExp = "(((-).(0|1|2|3|4|5|6|7|8|9)*)|((0x)(0|1|2|3|4|5|6|7|8|9|A|B|C|D|E|F)*))";
  static NFA inputValidationNFA(regExp.c_str(), regExp.length());
  return inputValidationNFA;
}
