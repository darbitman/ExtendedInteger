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

  static unsigned int MIN_ARRAY_SIZE;                                 // absolute minimum array size
  ExtendedInt(unsigned int arrSize = 4);                              // default array size = 4
  ~ExtendedInt();
  void clearValue();                                                  // set array values to 0
  unsigned int arraySize;                                             // array size
  unsigned int* ext_int;                                              // array
  enum DIVIDE_OPERATION { DIVIDE_OP, MOD_OP };
  bool validateString(const char* s, unsigned int strLen);            // will call the NFA to validate input string
  static NFA& getNFAInstance();                                       // get NFA used to verify string input
  virtual void newArraySize(unsigned int newArraySize);               // clear old array/arraySize and use new values
  virtual void increaseArraySizeTo(unsigned int newArraySize);
  virtual void decreaseArraySizeTo(unsigned int newArraySize);
  virtual void clearUnusedMemory();                                   // delete unused memory (any values that are 0)
};
