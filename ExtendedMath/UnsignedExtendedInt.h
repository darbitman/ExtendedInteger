#ifndef _UNSIGNEDEXTENDEDINT_H_
#define _UNSIGNEDEXTENDEDINT_H_


#include "ExtendedInt.h"
#include <iostream>


template<typename T>
class UnsignedExtendedInt : public ExtendedInt<T> {
protected:
    virtual void stringToExtendedInt(const char* s);
    virtual char* extendedIntToString() const;
    const UnsignedExtendedInt divideModOperator(const UnsignedExtendedInt& divisor, const ExtendedInt<T>::DIVIDE_OPERATION op) const;
    UnsignedExtendedInt(const unsigned long long& obj, const unsigned long long& multipleOf32Bits);
public:
	UnsignedExtendedInt();
    UnsignedExtendedInt(const UnsignedExtendedInt& obj);
    UnsignedExtendedInt(const char* s);
    ~UnsignedExtendedInt();
    const UnsignedExtendedInt& operator=(const UnsignedExtendedInt& obj);
    const UnsignedExtendedInt& operator=(const char* s);
    const UnsignedExtendedInt operator+(const UnsignedExtendedInt& obj) const;
    const UnsignedExtendedInt operator+(const unsigned long long& obj) const;
    const UnsignedExtendedInt operator-(const UnsignedExtendedInt& obj) const;
    const UnsignedExtendedInt operator-(const unsigned long long& obj) const;
    const UnsignedExtendedInt operator*(const UnsignedExtendedInt& obj) const;
    const UnsignedExtendedInt operator/(const UnsignedExtendedInt& divisor) const;
    const UnsignedExtendedInt operator%(const UnsignedExtendedInt& divisor) const;
    bool operator==(const UnsignedExtendedInt& obj) const;
    bool operator==(const unsigned long long& obj) const;
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


    friend std::ostream& operator<<(std::ostream& os, const UnsignedExtendedInt& obj) {
        UnsignedExtendedInt<T> original(obj);
        UnsignedExtendedInt<T> remainder;
        UnsignedExtendedInt<T> TEN;
        TEN.setValueAtIndex(10, 0);
        while (!(original == 0)) {
            remainder = original % TEN;
            original = original / TEN;
        }
        return os;
    }
};


#endif
