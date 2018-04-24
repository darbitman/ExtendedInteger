#pragma once
#include "NFA.h"
#include "Exception.h"
#include <iostream>
#include <string>


class ExtendedInt {
public:
  virtual void setValueAtIndex(const unsigned long long val, const unsigned int index);
  virtual unsigned int getValueAtIndex(const unsigned int index) const;
  virtual unsigned int getArraySize() const;
protected:
  static unsigned int MIN_ARRAY_SIZE;                                 // absolute minimum array size
  ExtendedInt(unsigned int arrSize = 4);                              // default array size = 4
  ~ExtendedInt();
  void clearValue();                                                  // set array values to 0
  unsigned int arraySize;                                             // array size
  unsigned int* ext_int;                                              // array
  enum DIVIDE_OPERATION { DIVIDE_OP, MOD_OP };
  bool validateString(const char* s, unsigned int strLen);            // will call the NFA to validate input string
  static NFA& getNFAInstance();                                       // get NFA used to verify string input
  virtual void newArraySize(unsigned int newArraySize);               // delete memory and reinitialize using new size
  virtual void increaseArraySizeTo(unsigned int newArraySize);        // increase amount of memory allocated for array; keep original data
  virtual void decreaseArraySizeTo(unsigned int newArraySize);        // decrease amount of memory allocated for array; may result in loss of data
  virtual void clearUnusedMemory();                                   // delete unused memory (any values that are 0)
};
