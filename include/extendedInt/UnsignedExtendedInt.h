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
  UnsignedExtendedInt(const char* s);
  ~UnsignedExtendedInt();
  UnsignedExtendedInt operator=(const UnsignedExtendedInt& obj);
  UnsignedExtendedInt operator+(const UnsignedExtendedInt& obj) const;
  UnsignedExtendedInt operator-(const UnsignedExtendedInt& obj) const;
  UnsignedExtendedInt operator*(const UnsignedExtendedInt& obj) const;
  UnsignedExtendedInt operator/(const UnsignedExtendedInt& divisor) const;
  UnsignedExtendedInt operator%(const UnsignedExtendedInt& divisor) const;
protected:
  bool operator==(const UnsignedExtendedInt& obj) const;
  bool operator!=(const UnsignedExtendedInt& obj) const;
  bool operator>(const UnsignedExtendedInt& obj) const;
  bool operator>=(const UnsignedExtendedInt& obj) const;
  bool operator<(const UnsignedExtendedInt& obj) const;
  bool operator<=(const UnsignedExtendedInt& obj) const;
  UnsignedExtendedInt operator>>(const UnsignedExtendedInt& shiftVal) const;
  UnsignedExtendedInt operator<<(const UnsignedExtendedInt& shiftVal) const;
  UnsignedExtendedInt operator&(const UnsignedExtendedInt& obj) const;
  UnsignedExtendedInt operator|(const UnsignedExtendedInt& obj) const;
  UnsignedExtendedInt operator^(const UnsignedExtendedInt& obj) const;
  UnsignedExtendedInt& operator++();
  UnsignedExtendedInt operator++(int);
  UnsignedExtendedInt& operator--();
  UnsignedExtendedInt operator--(int);
  UnsignedExtendedInt operator~() const;

  friend std::ostream& operator<<(std::ostream& os, const UnsignedExtendedInt& obj);
protected:
  UnsignedExtendedInt divideModOperator(const UnsignedExtendedInt& obj, const ExtendedInt::DIVIDE_OPERATION op) const;
  void stringToExtendedInt(const char* s);
  std::string extendedIntToString() const;
};
