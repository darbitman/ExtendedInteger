#pragma once

#include "ExtendedIntLengths.h"
#include "NFA.h"
#include <iostream>
#include <string>

template<unsigned int t = 4>
class ExtendedInt {
protected:
  enum DIVIDE_OPERATION { DIVIDE_OP, MOD_OP };
  unsigned int ARRAY_SIZE;
  unsigned int ext_int[t];
  void clearValue();
  bool validateString(const char* s, unsigned int strLen);
  static NFA& getNFAInstance();
  ExtendedInt();
public:
  virtual void setValueAtIndex(const unsigned long long val, const unsigned int index);
  virtual unsigned int getValueAtIndex(const unsigned int index) const;
  virtual unsigned int getArraySize();
};


template<unsigned int t = 4>
NFA& ExtendedInt<t>::getNFAInstance() {
  static std::string regExp = "(((0x)|(-)).(0|1|2|3|4|5|6|7|8|9)*)";
  static NFA inputValidationNFA(regExp.c_str(), regExp.length());
  return inputValidationNFA;
}


template<unsigned int t>
ExtendedInt<t>::ExtendedInt(): ARRAY_SIZE(t) {
  this->clearValue();
}


template<unsigned int t>
void ExtendedInt<t>::clearValue() {
  for (unsigned int i = 0; i < this->ARRAY_SIZE; i++) {
    this->ext_int[i] = 0;
  }
}


template<unsigned int t>
void ExtendedInt<t>::setValueAtIndex(const unsigned long long val, const unsigned int index) {
  if ((index < this->ARRAY_SIZE) && (index >= 0)) {
    this->ext_int[index] = val & 0xFFFFFFFF;
  }
}


template<unsigned int t>
unsigned int ExtendedInt<t>::getValueAtIndex(const unsigned int index) const {
  if ((this->ARRAY_SIZE > 0) && (index < this->ARRAY_SIZE) && (index >= 0)) {
    return this->ext_int[index];
  }
  return 0;
}


template<unsigned int t>
unsigned int ExtendedInt<t>::getArraySize() {
  return this->ARRAY_SIZE;
}


template<unsigned int t>
bool ExtendedInt<t>::validateString(const char* s, unsigned int strLen) {
  return getNFAInstance().validateTxt(s, strLen);
}
