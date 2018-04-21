#pragma once
#include "ExtendedInt.h"
#include "UnsignedExtendedInt.h"


class UnsignedExtendedInt : public ExtendedInt {
public:
  UnsignedExtendedInt(unsigned int arrSize = 4);
  UnsignedExtendedInt(const UnsignedExtendedInt& obj);
  UnsignedExtendedInt(unsigned long long obj);
  UnsignedExtendedInt(long long obj);
  UnsignedExtendedInt(int obj);
  //UnsignedExtendedInt(const char* s);
  ~UnsignedExtendedInt();

  //UnsignedExtendedInt operator=(const UnsignedExtendedInt& obj);
  //UnsignedExtendedInt operator=(int obj);
protected:
};
