#include "ExtendedInt.h"

unsigned int ExtendedInt::MIN_ARRAY_SIZE = 4;


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


ExtendedInt::ExtendedInt(unsigned int arrSize) : arraySize(arrSize) {
  ext_int = new unsigned int[arraySize];
  clearValue();
}


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


void ExtendedInt::newArraySize(unsigned int newArraySize) {
  if (newArraySize != arraySize) {
    arraySize = newArraySize;
    delete[] ext_int;
    ext_int = new unsigned int[newArraySize];
    clearValue();
  }
}


void ExtendedInt::increaseArraySizeTo(unsigned int newArraySize) {
  unsigned int* newExtIntPtr = new unsigned int[newArraySize];
  for (unsigned int i = 0; i < newArraySize; i++) {         // clear new array
    newExtIntPtr[i] = 0;
  }
  for (unsigned int i = 0; i < arraySize; i++) {            // copy over previous values
    newExtIntPtr[i] = ext_int[i];
  }
  delete[] ext_int;
  ext_int = newExtIntPtr;
  arraySize = newArraySize;
}


void ExtendedInt::decreaseArraySizeTo(unsigned int newArraySize) {
  try {
    if (newArraySize < MIN_ARRAY_SIZE) {
      throw MinArraySizeExceededException();
    }
    unsigned int* newExtIntPtr = new unsigned int[newArraySize];
    for (unsigned int i = 0; i < newArraySize; i++) {       // clear new array
      newExtIntPtr[i] = 0;
    }
    for (unsigned int i = 0; i < newArraySize; i++) {       // copy over previous values
      newExtIntPtr[i] = ext_int[i];
    }
    delete[] ext_int;
    ext_int = newExtIntPtr;
    arraySize = newArraySize;
  }
  catch (const Exception& e) {
    e.printError();
  }
}


void ExtendedInt::clearUnusedMemory() {
  unsigned int numEntriesToDelete = 0;
  for (int i = arraySize - 1; i >= 0; i--) {                // count how many consecutive 0s there are MSByte -> LSByte
    if (ext_int[i] == 0) {
      numEntriesToDelete++;
    }
    else {
      break;
    }
  }
  if (numEntriesToDelete > 0) {
    unsigned int newArraySize = arraySize - numEntriesToDelete;
    newArraySize = (newArraySize > 3 ? newArraySize : 4);   // minimum array size is 4
    decreaseArraySizeTo(newArraySize);
  }
}