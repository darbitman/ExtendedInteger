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
  bool isSignedType;                                                  // if set to true, then signed (not necessarily negative)
  ExtendedInt(bool isSigned = false, unsigned int arrSize = 4);       // default type = unsigned, default array size = 4
  ~ExtendedInt();
  void clearValue();                                                  // set array values to 0
  unsigned int arraySize;                                             // array size
  unsigned int* ext_int;                                              // array will store ExtendedInt value
  enum DIVIDE_OPERATION { DIVIDE_OP, MOD_OP };
  bool validateString(const char* s, unsigned int strLen);            // will call the NFA to validate input string
  static NFA& getNFAInstance();                                       // get NFA used to verify string input

  /**
  Allocate new memory and initialize it to 0
  */
  virtual void newArraySize(unsigned int newArraySize);               // delete memory and reinitialize using new size

  /**
  Increase array size while preserving data
  */
  virtual void increaseArraySizeTo(unsigned int newArraySize);        // increase amount of memory allocated for array; keep original data

  /**
  Decrease array size. Data not guaranteed to be preserved
  */
  virtual void decreaseArraySizeTo(unsigned int newArraySize);        // decrease amount of memory allocated for array; may result in loss of data

  /**
  Get rid of redundant MSWords (signed 0xFFFFFFFF or 0x00000000)
  */
  virtual void clearUnusedMemory();                                   // delete unused memory (any values that are 0)
};
