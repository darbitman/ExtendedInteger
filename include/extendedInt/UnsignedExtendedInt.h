#pragma once
#include "ExtendedInt.h"
#include "UnsignedExtendedInt.h"


class UnsignedExtendedInt : public ExtendedInt {
public:
  UnsignedExtendedInt();
  UnsignedExtendedInt(const UnsignedExtendedInt& obj);
  UnsignedExtendedInt(unsigned long long obj);
  UnsignedExtendedInt(long long obj);
  UnsignedExtendedInt(int obj);
  //UnsignedExtendedInt(const char* s);
  ~UnsignedExtendedInt();
  UnsignedExtendedInt operator=(const UnsignedExtendedInt& obj);
  //UnsignedExtendedInt operator=(int obj);
  UnsignedExtendedInt operator+(const UnsignedExtendedInt& obj) const;
  UnsignedExtendedInt operator-(const UnsignedExtendedInt& obj) const;
  UnsignedExtendedInt operator*(const UnsignedExtendedInt& obj) const;
  UnsignedExtendedInt operator/(const UnsignedExtendedInt& obj) const;
  UnsignedExtendedInt operator%(const UnsignedExtendedInt& obj) const;

  bool operator==(const UnsignedExtendedInt& obj) const;
  bool operator!=(const UnsignedExtendedInt& obj) const;
  bool operator>(const UnsignedExtendedInt& obj) const;
  bool operator>=(const UnsignedExtendedInt& obj) const;
  bool operator<(const UnsignedExtendedInt& obj) const;
  bool operator<=(const UnsignedExtendedInt& obj) const;
  UnsignedExtendedInt operator>>(const UnsignedExtendedInt& shiftVal) const;
  UnsignedExtendedInt operator~() const;
protected:
  //void stringToExtendedInt(const char* s);
  UnsignedExtendedInt divideModOperator(const UnsignedExtendedInt& obj, const ExtendedInt::DIVIDE_OPERATION op) const;
};
