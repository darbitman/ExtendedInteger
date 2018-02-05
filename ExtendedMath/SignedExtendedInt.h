#ifndef _SIGNEDEXTENDEDINT_H_
#define _SIGNEDEXTENDEDINT_H_


#include "ExtendedInt.h"


template<typename T>
class SignedExtendedInt : public ExtendedInt<T> {
protected:
    virtual void stringToExtendedInt(const char* s);
public:
    SignedExtendedInt();
    SignedExtendedInt(const SignedExtendedInt& obj);
    SignedExtendedInt(const char* s);
    ~SignedExtendedInt();
    const SignedExtendedInt& operator=(const SignedExtendedInt& obj);
    const SignedExtendedInt& operator=(const char* s);
    const SignedExtendedInt& operator+(const SignedExtendedInt& obj);
    const SignedExtendedInt& operator+(const long long& obj);
};


#endif