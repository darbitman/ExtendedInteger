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


ExtendedInt::ExtendedInt(bool signBit, unsigned int arrSize) : arraySize(arrSize), isSigned(signBit) {
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
  for (unsigned int i = 0; i < newArraySize; i++) {           // clear new array
    newExtIntPtr[i] = 0;
  }
  for (unsigned int i = 0; i < arraySize; i++) {              // copy over previous values
    newExtIntPtr[i] = ext_int[i];
  }
  delete[] ext_int;
  ext_int = newExtIntPtr;
  if (isSigned && (ext_int[arraySize - 1] & 0x80000000)) {    // check if SignedExtendedInt and if sign bit is set
    for (unsigned int i = arraySize; i < newArraySize; i++) { // extend sign bit to all newly added words
      ext_int[i] = 0xFFFFFFFF;
    }
  }
  arraySize = newArraySize;
}


void ExtendedInt::decreaseArraySizeTo(unsigned int newArraySize) {
AfterExceptionCaught:
  try {
    if (newArraySize < MIN_ARRAY_SIZE) {
      newArraySize = MIN_ARRAY_SIZE;                        // force newArraySize
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
    return;
  }
  catch (const Exception& e) {
    e.printError();
    goto AfterExceptionCaught;
  }
  // TODO handle isSigned case
}


// delete unnecessary 1's or 0's to save memory
void ExtendedInt::clearUnusedMemory() {
  unsigned int numEntriesToDelete = 0;
  bool isNegative = false;
  if (isSigned && (ext_int[arraySize - 1] & 0x80000000)) {              // check if negative
    isNegative = true;
  }
  for (int i = arraySize - 1; i >= (int)MIN_ARRAY_SIZE; i--) {          // count how many consecutive 0's or 1's there are MSWord -> LSWord
    if (isNegative) {
      if (ext_int[i] == 0xFFFFFFFF && (ext_int[i - 1] & 0x80000000))  { // if word == 0xFFFFFFFF and the next word has upper bit set then 0xFFFFFFFF is unnecessary
        numEntriesToDelete++;
      }
      else {                                                            // break from counting the rest once it doesn't match
        break;
      }
    }
    else {
      if (ext_int[i] == 0) {
        numEntriesToDelete++;
      }
      else {                                                            // break from counting adjacent 0 on first nonzero word
        break;
      }
    }
  }
  if (numEntriesToDelete > 0) {
    unsigned int newArraySize = arraySize - numEntriesToDelete;
    decreaseArraySizeTo(newArraySize);
  }
}
