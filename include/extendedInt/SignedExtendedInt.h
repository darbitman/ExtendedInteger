#pragma once
#include "ExtendedInt.h"
#include "SignedExtendedInt.h"


class SignedExtendedInt : public ExtendedInt {
public:
  SignedExtendedInt();
  SignedExtendedInt(const SignedExtendedInt& obj);
  SignedExtendedInt(long long obj);
  SignedExtendedInt(int obj);
  SignedExtendedInt(const char* s);
  ~SignedExtendedInt();
  SignedExtendedInt operator=(const SignedExtendedInt& obj);
  SignedExtendedInt operator+(const SignedExtendedInt& obj) const;
  //SignedExtendedInt operator-(const SignedExtendedInt& obj) const;
  //SignedExtendedInt operator*(const SignedExtendedInt& obj) const;
  //SignedExtendedInt operator/(const SignedExtendedInt& divisor) const;
  //SignedExtendedInt operator%(const SignedExtendedInt& divisor) const;
protected:
  //bool operator==(const SignedExtendedInt& obj) const;
  //bool operator!=(const SignedExtendedInt& obj) const;
  //bool operator>(const SignedExtendedInt& obj) const;
  //bool operator>=(const SignedExtendedInt& obj) const;
  //bool operator<(const SignedExtendedInt& obj) const;
  //bool operator<=(const SignedExtendedInt& obj) const;
  //SignedExtendedInt operator>>(const SignedExtendedInt& shiftVal) const;
  //SignedExtendedInt operator<<(const SignedExtendedInt& shiftVal) const;
  //SignedExtendedInt operator&(const SignedExtendedInt& obj) const;
  //SignedExtendedInt operator|(const SignedExtendedInt& obj) const;
  //SignedExtendedInt operator^(const SignedExtendedInt& obj) const;
  //SignedExtendedInt& operator++();
  //SignedExtendedInt operator++(int);
  //SignedExtendedInt& operator--();
  //SignedExtendedInt operator--(int);
  //SignedExtendedInt operator~() const;

  //friend std::ostream& operator<<(std::ostream& os, const SignedExtendedInt& obj);
protected:
  //SignedExtendedInt divideModOperator(const SignedExtendedInt& obj, const ExtendedInt::DIVIDE_OPERATION op) const;
  //void stringToExtendedInt(const char* s);
  //std::string extendedIntToString() const;
};
