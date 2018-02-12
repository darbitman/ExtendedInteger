#ifndef _SIGNEDEXTENDEDINT_H_
#define _SIGNEDEXTENDEDINT_H_


#include "ExtendedInt.h"


template<typename T>
class SignedExtendedInt : public ExtendedInt<T> {
protected:
    virtual void stringToExtendedInt(const char* s);
    const SignedExtendedInt divideModOperator(const SignedExtendedInt& divisor, const ExtendedInt<T>::DIVIDE_OPERATION op) const;
public:
    SignedExtendedInt();
    SignedExtendedInt(const SignedExtendedInt& obj);
    SignedExtendedInt(const char* s);
    ~SignedExtendedInt();
    const SignedExtendedInt& operator=(const SignedExtendedInt& obj);
    const SignedExtendedInt& operator=(const char* s);
    const SignedExtendedInt operator+(const SignedExtendedInt& obj) const;
    const SignedExtendedInt operator+(const long long& obj) const;
    const SignedExtendedInt operator-(const SignedExtendedInt& obj) const;
    const SignedExtendedInt operator-(const long long& obj) const;
    const SignedExtendedInt operator*(const SignedExtendedInt& obj) const;
    const SignedExtendedInt operator*(const long long& obj) const;
    const SignedExtendedInt operator/(const SignedExtendedInt& obj) const;
    const SignedExtendedInt operator%(const SignedExtendedInt& obj) const;
    bool operator==(const SignedExtendedInt& obj) const;
    bool operator<(const SignedExtendedInt& obj) const;
    bool operator>(const SignedExtendedInt& obj) const;
    bool operator<=(const SignedExtendedInt& obj) const;
    const SignedExtendedInt operator>>(unsigned int shiftVal) const;
    const SignedExtendedInt operator<<(unsigned int shiftVal) const;
    inline SignedExtendedInt operator&(const SignedExtendedInt& obj) const;
    inline SignedExtendedInt operator|(const SignedExtendedInt& obj) const;
    inline const SignedExtendedInt operator~() const;
};


#endif