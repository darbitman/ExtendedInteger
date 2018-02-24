#ifndef _UNSIGNEDEXTENDEDINT_H_
#define _UNSIGNEDEXTENDEDINT_H_


#include "ExtendedInt.h"
#include <iostream>
#include <string>


template<typename T>
class UnsignedExtendedInt : public ExtendedInt<T> {
protected:
    virtual void stringToExtendedInt(const char* s);
    virtual std::string extendedIntToString() const;
    const UnsignedExtendedInt divideModOperator(const UnsignedExtendedInt& divisor, const ExtendedInt<T>::DIVIDE_OPERATION op) const;
public:
	UnsignedExtendedInt();
    UnsignedExtendedInt(const UnsignedExtendedInt& obj);
    UnsignedExtendedInt(const char* s);
    UnsignedExtendedInt(const unsigned long long& obj);
    template<typename U> UnsignedExtendedInt(const UnsignedExtendedInt<U>& obj);
    ~UnsignedExtendedInt();
    const UnsignedExtendedInt& operator=(const UnsignedExtendedInt& obj);
    const UnsignedExtendedInt& operator=(const char* s);
    const UnsignedExtendedInt operator+(const UnsignedExtendedInt& obj) const;
    const UnsignedExtendedInt operator-(const UnsignedExtendedInt& obj) const;
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
    inline UnsignedExtendedInt operator|(const UnsignedExtendedInt& obj) const;
    inline UnsignedExtendedInt operator^(const UnsignedExtendedInt& obj) const;
    inline UnsignedExtendedInt operator~() const;

    void printDecimalString() const;


    friend std::ostream& operator<<(std::ostream& os, const UnsignedExtendedInt& obj) {
        os << obj.extendedIntToString();
        return os;
    }
};

template<typename T> template<typename U> UnsignedExtendedInt<T>::UnsignedExtendedInt(const UnsignedExtendedInt<U>& obj) {
    this->ARRAY_SIZE = T::_multipleOf32Bits;
    for (unsigned int i = 0; i < this->ARRAY_SIZE; i++) {
        this->ext_int[i] = 0;
    }
    if (this->ARRAY_SIZE > obj.getArraySize()) {
        for (unsigned int i = 0; i < obj.getArraySize(); i++) {
            this->ext_int[i] = obj.getValueAtIndex(i);
        }
    }
    else {
        for (unsigned int i = 0; i < this->ARRAY_SIZE; i++) {
            this->ext_int[i] = obj.getValueAtIndex(i);
        }
    }
}

#endif
