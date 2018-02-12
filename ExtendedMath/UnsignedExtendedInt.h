#ifndef _UNSIGNEDEXTENDEDINT_H_
#define _UNSIGNEDEXTENDEDINT_H_

#include "ExtendedInt.h"

template<typename T>
class UnsignedExtendedInt : public ExtendedInt<T> {
protected:
    virtual void stringToExtendedInt(const char* s);
    const UnsignedExtendedInt divideModOperator(const UnsignedExtendedInt& divisor, const ExtendedInt<T>::DIVIDE_OPERATION op);
public:
	UnsignedExtendedInt();
    UnsignedExtendedInt(const UnsignedExtendedInt& obj);
    UnsignedExtendedInt(const char* s);
    ~UnsignedExtendedInt();
    const UnsignedExtendedInt& operator=(const UnsignedExtendedInt& obj);
    const UnsignedExtendedInt& operator=(const char* s);
    const UnsignedExtendedInt operator+(const UnsignedExtendedInt& obj);
    const UnsignedExtendedInt operator+(const unsigned long long& obj);
    const UnsignedExtendedInt operator-(const UnsignedExtendedInt& obj);
    const UnsignedExtendedInt operator-(const unsigned long long& obj);
    const UnsignedExtendedInt operator*(const UnsignedExtendedInt& obj);    
    const UnsignedExtendedInt operator/(const UnsignedExtendedInt& divisor);
    const UnsignedExtendedInt operator%(const UnsignedExtendedInt& divisor);
    bool operator==(const UnsignedExtendedInt& obj) const;
    bool operator>(const UnsignedExtendedInt& obj) const;
    bool operator>=(const UnsignedExtendedInt& obj) const;
    bool operator<(const UnsignedExtendedInt& obj) const;
    bool operator<=(const UnsignedExtendedInt& obj) const;
    const UnsignedExtendedInt operator>>(unsigned int shiftVal) const;
    const UnsignedExtendedInt operator<<(unsigned int shiftVal) const;
    inline UnsignedExtendedInt operator&(const UnsignedExtendedInt& obj) const;
    inline UnsignedExtendedInt operator&(const unsigned long long& obj) const;
    inline UnsignedExtendedInt operator|(const UnsignedExtendedInt& obj) const;
    inline UnsignedExtendedInt operator|(const unsigned long long& obj) const;
    inline UnsignedExtendedInt operator^(const UnsignedExtendedInt& obj) const;
    inline UnsignedExtendedInt operator^(const unsigned long long& obj) const;
    inline UnsignedExtendedInt operator~() const;
};


#endif
