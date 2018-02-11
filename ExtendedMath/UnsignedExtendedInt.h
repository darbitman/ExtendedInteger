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
    UnsignedExtendedInt operator>>(unsigned int shiftVal) const;
    UnsignedExtendedInt operator<<(unsigned int shiftVal) const;
    inline UnsignedExtendedInt operator&(const UnsignedExtendedInt& obj) const;
    inline UnsignedExtendedInt operator&(const unsigned long long& obj) const;
    inline UnsignedExtendedInt operator|(const UnsignedExtendedInt& obj) const;
    inline UnsignedExtendedInt operator|(const unsigned long long& obj) const;
    inline UnsignedExtendedInt operator^(const UnsignedExtendedInt& obj) const;
    inline UnsignedExtendedInt operator^(const unsigned long long& obj) const;
    inline UnsignedExtendedInt operator~() const;
};

/*
// Create new extended integer
template<typename T>
UnsignedExtendedInt<T>::UnsignedExtendedInt() {
    this->initialize();
}


// Copy constructor
template<typename T>
UnsignedExtendedInt<T>::UnsignedExtendedInt(const UnsignedExtendedInt& obj) {
    this->initialize();
    for (unsigned int i = 0; i < this->ARRAY_SIZE; i++) {
        this->ext_int[i] = obj.ext_int[i];
    }
}


// Construct new extended integer using string input 
template<typename T>
void UnsignedExtendedInt<T>::stringToExtendedInt(const char* s) {
    unsigned int strLength = 0;
    while (s[strLength] != 0) {             // compute string length
        strLength++;
    }
    UnsignedExtendedInt<T> TEN;
    UnsignedExtendedInt<T> powersOfTen;
    powersOfTen.setValueAtIndex(1, 0);
    TEN.setValueAtIndex(10, 0);
    UnsignedExtendedInt<T> readInt;
    for (int i = strLength - 1; i >= 0; i--) {
        readInt.setValueAtIndex(s[i] - '0', 0);
        *this = *this + (powersOfTen * readInt);
        powersOfTen = powersOfTen * TEN;
    }
}


// convert input string to extended integer
template<class T>
UnsignedExtendedInt<T>::UnsignedExtendedInt(const char* s) {
    this->initialize();
    this->stringToExtendedInt(s);
}


template<typename T>
UnsignedExtendedInt<T>::~UnsignedExtendedInt() {
    delete[] this->ext_int;
}


template<typename T>
const UnsignedExtendedInt<T>& UnsignedExtendedInt<T>::operator=(const UnsignedExtendedInt& obj) {
    this->ARRAY_SIZE = obj.ARRAY_SIZE;
    this->ext_int = new unsigned int[this->ARRAY_SIZE];
    for (unsigned int i = 0; i < this->ARRAY_SIZE; i++) {
        this->ext_int[i] = obj.ext_int[i];
    }
    return *this;
}


template<typename T>
const UnsignedExtendedInt<T>& UnsignedExtendedInt<T>::operator=(const char* s) {
    this->initialize();
    stringToExtendedInt(s);
    return *this;
}


template<class T>
const UnsignedExtendedInt<T>& UnsignedExtendedInt<T>::operator+(const UnsignedExtendedInt<T>& obj) {
    unsigned long long x = 0;
    unsigned long long y = 0;
    unsigned long long z = 0;
    unsigned int carryBit = 0;
    UnsignedExtendedInt<T>* returnValue = new UnsignedExtendedInt<T>();
    for (unsigned int i = 0; i < this->ARRAY_SIZE; i++) {
        x = this->ext_int[i];
        y = obj.ext_int[i];
        z = x + y + carryBit;
        returnValue->ext_int[i] = z & 0xFFFFFFFF;
        carryBit = (z & 0x100000000) >> 32;
    }
    return *returnValue;
}


template<typename T>
const UnsignedExtendedInt<T>& UnsignedExtendedInt<T>::operator+(const unsigned long long& obj) {
    unsigned long long x = 0;
    unsigned long long y = 0;
    unsigned long long z = 0;
    unsigned int carryBit = 0;
    UnsignedExtendedInt* returnValue = new UnsignedExtendedInt();
    for (unsigned int i = 0; i < this->ARRAY_SIZE; i++) {
        x = this->ext_int[i];
        y = ((obj >> i) & 0xFFFFFFFF);
        z = x + y + carryBit;
        returnValue->ext_int[i] = z & 0xFFFFFFFF;
        carryBit = (z & 0x100000000) >> 32;
    }
    return *returnValue;
}


template<typename T>
const UnsignedExtendedInt<T>& UnsignedExtendedInt<T>::operator-(const UnsignedExtendedInt& obj) {
    UnsignedExtendedInt<T>* returnValue = new UnsignedExtendedInt();
    UnsignedExtendedInt<T>* negativeValue = new UnsignedExtendedInt();
    for (unsigned int i = 0; i < this->ARRAY_SIZE; i++) {
        negativeValue->setValueAtIndex(~(obj.getValueAtIndex(i)), i);
    }
    *negativeValue = *negativeValue + 1;
    *returnValue = this->operator+(*negativeValue);
    delete negativeValue;
    return *returnValue;
}


template<typename T>
const UnsignedExtendedInt<T>& UnsignedExtendedInt<T>::operator*(const UnsignedExtendedInt& obj) {
    // This algorithm multiplies 32bit integers using native 64bit integers.
    unsigned long long x = 0;
    unsigned long long y = 0;
    unsigned long long z = 0;
    unsigned int upperResultBits = 0;
    unsigned int lowerResultBits = 0;
    unsigned int leftShiftValue = 0;
    UnsignedExtendedInt* returnValue = new UnsignedExtendedInt();
    UnsignedExtendedInt uExtIntTemp;
    for (unsigned int i = 0; i < this->ARRAY_SIZE; i++) {
        for (unsigned int j = 0; j < this->ARRAY_SIZE; j++) {
            leftShiftValue = i + j;
            x = this->ext_int[i];
            y = obj.ext_int[j];
            z = x * y;

            if (leftShiftValue < this->ARRAY_SIZE) {
                if (leftShiftValue > 0) {   // clear previous 32-bits because they will introduce an error in the summation
                    uExtIntTemp.setValueAtIndex(0, leftShiftValue - 1);
                }
                lowerResultBits = z & 0xFFFFFFFF;
                uExtIntTemp.setValueAtIndex(lowerResultBits, leftShiftValue);                   // Extract first 32-bits
            }
            if (leftShiftValue < this->ARRAY_SIZE - 1) {
                upperResultBits = (z >> 32) & 0xFFFFFFFF;
                uExtIntTemp.setValueAtIndex(upperResultBits, leftShiftValue + 1);   // Extract upper 32-bits
            }
            *returnValue = *returnValue + uExtIntTemp;
        }
    }
    return *returnValue;
}


template<typename T>
const UnsignedExtendedInt<T>& UnsignedExtendedInt<T>::operator/(const UnsignedExtendedInt& divisor) {
    return divideModOperator(divisor, this->DIVIDE_OP);
}


template<typename T>
const UnsignedExtendedInt<T>& UnsignedExtendedInt<T>::operator%(const UnsignedExtendedInt& divisor) {
    return divideModOperator(divisor, this->MOD_OP);
}


template<typename T>
const UnsignedExtendedInt<T>& UnsignedExtendedInt<T>::divideModOperator(const UnsignedExtendedInt& divisor, const ExtendedInt<T>::DIVIDE_OPERATION op) {
    unsigned long long x = 0;
    unsigned long long y = 0;
    UnsignedExtendedInt* returnValue = new UnsignedExtendedInt();
    UnsignedExtendedInt* tempDividend = new UnsignedExtendedInt();
    UnsignedExtendedInt* maskBit = new UnsignedExtendedInt();
    maskBit->setValueAtIndex(1, 0);
    if (*this < divisor) {
        return *returnValue;    // if dividend is smaller than divisor, return 0 (e.g. 10 / 20 = 0)
    }
    int i = 128;
    *maskBit = *maskBit << (i - 1);
    while (--i >= 0) {
        if (divisor > *tempDividend) {
            // Extract bit i
            *tempDividend = (((*this & *maskBit) >> i) | (*tempDividend << 1));
            *maskBit = *maskBit >> 1;
        }
        else {
            *returnValue = *returnValue | (*maskBit << 1);
            *tempDividend = *tempDividend - divisor;
            i++;
        }
    }

    // Extract bit 0 of the quotient
    if (divisor <= *tempDividend) {
        maskBit->setValueAtIndex(1, 0);
        *returnValue = *returnValue | *maskBit;
        *tempDividend = *tempDividend - divisor;        // remainder
    }

    delete maskBit;
    if (op == this->DIVIDE_OP) {
        delete tempDividend;
        return *returnValue;
    }
    else {      // mod operation returns remainder
        delete returnValue;
        return *tempDividend;
    }
}


template<typename T>
bool UnsignedExtendedInt<T>::operator==(const UnsignedExtendedInt& obj) const {
    for (int i = this->ARRAY_SIZE - 1; i >= 0; i--) {
        if (this->getValueAtIndex(i) == obj.getValueAtIndex(i)) {
            continue;
        }
        else {
            return false;
        }
    }
    return true;
}


template<typename T>
bool UnsignedExtendedInt<T>::operator>(const UnsignedExtendedInt& obj) const {
    for (int i = this->ARRAY_SIZE - 1; i >= 0; i--) {
        if (this->getValueAtIndex(i) > obj.getValueAtIndex(i)) {
            return true;
        }
    }
    return false;
}


template<typename T>
bool UnsignedExtendedInt<T>::operator>=(const UnsignedExtendedInt & obj) const {
    if (*this > obj || *this == obj) {
        return true;
    }
    return false;
}


template<typename T>
bool UnsignedExtendedInt<T>::operator<(const UnsignedExtendedInt& obj) const {
    for (int i = this->ARRAY_SIZE - 1; i >= 0; i--) {
        if (this->getValueAtIndex(i) > obj.getValueAtIndex(i)) {
            return false;
        }
        else if (this->getValueAtIndex(i) == obj.getValueAtIndex(i)) {
            continue;
        }
    }
    return true;
}


template<typename T>
bool UnsignedExtendedInt<T>::operator<=(const UnsignedExtendedInt & obj) const {
    if (*this < obj || *this == obj) {
        return true;
    }
    return false;
}


template<typename T>
UnsignedExtendedInt<T>& UnsignedExtendedInt<T>::operator>>(unsigned int shiftVal) const {
    unsigned long long x = 0;
    unsigned long long y = 0;
    UnsignedExtendedInt* returnValue = new UnsignedExtendedInt(*this);
    shiftVal = (shiftVal > 128 ? 128 : shiftVal);           // maximum shift is 128 bits
    while (shiftVal > 0) {
        for (unsigned int i = 0; i < this->ARRAY_SIZE; i++) {
            x = returnValue->ext_int[i];
            x = x << 32;
            x = x >> (shiftVal > 32 ? 32 : shiftVal);       // perform shift
            returnValue->setValueAtIndex((x & 0xFFFFFFFF00000000) >> 32, i);        // upper 32 bits should be stored
            if (i > 0) {
                y = returnValue->ext_int[i - 1];
                returnValue->setValueAtIndex((x & 0xFFFFFFFF) | y, i - 1);                     // lower 32 bits ORd with previous entry since these bits were shifted into the the adjacent 32-bits
            }
        }
        shiftVal = (shiftVal >= 32 ? shiftVal - 32 : 0);
    }
    return *returnValue;
}


template<typename T>
UnsignedExtendedInt<T>& UnsignedExtendedInt<T>::operator<<(unsigned int shiftVal) const {
    unsigned long long x = 0;
    unsigned long long y = 0;
    UnsignedExtendedInt* returnValue = new UnsignedExtendedInt(*this);
    shiftVal = (shiftVal > 128 ? 128 : shiftVal);           // maximum shift is 128 bits
    while (shiftVal > 0) {
        for (unsigned int i = this->ARRAY_SIZE - 1; i >= 0; i--) {
            x = returnValue->ext_int[i];
            x = x << (shiftVal > 32 ? 32 : shiftVal);       // perform shift
            returnValue->setValueAtIndex(x & 0xFFFFFFFF, i);        // lower 32 bits should be stored
            if (i < this->ARRAY_SIZE - 1) {
                y = returnValue->ext_int[i + 1];
                returnValue->setValueAtIndex((x & 0xFFFFFFFF00000000) >> 32 | y, i + 1);                     // lower 32 bits ORd with previous entry since these bits were shifted into the the adjacent 32-bits
            }
        }
        shiftVal = (shiftVal >= 32 ? shiftVal - 32 : 0);
    }
    return *returnValue;
}


template<typename T>
UnsignedExtendedInt<T>& UnsignedExtendedInt<T>::operator&(const UnsignedExtendedInt& obj) const {
    UnsignedExtendedInt* returnValue = new UnsignedExtendedInt();
    for (unsigned int i = 0; i < this->ARRAY_SIZE; i++) {
        returnValue->setValueAtIndex(this->getValueAtIndex(i) & obj.getValueAtIndex(i), i);
    }
    return *returnValue;
}


template<typename T>
UnsignedExtendedInt<T>& UnsignedExtendedInt<T>::operator&(const unsigned long long& obj) const {
    UnsignedExtendedInt* returnValue = new UnsignedExtendedInt();
    returnValue->setValueAtIndex(this->getValueAtIndex(0) & (obj & 0xFFFFFFFF), 0);
    returnValue->setValueAtIndex(this->getValueAtIndex(1) & ((obj >> 32) & 0xFFFFFFFF), 0);
    return *returnValue;
}


template<typename T>
UnsignedExtendedInt<T>& UnsignedExtendedInt<T>::operator|(const UnsignedExtendedInt& obj) const {
    UnsignedExtendedInt* returnValue = new UnsignedExtendedInt();
    for (unsigned int i = 0; i < this->ARRAY_SIZE; i++) {
        returnValue->setValueAtIndex(this->getValueAtIndex(i) | obj.getValueAtIndex(i), i);
    }
    return *returnValue;
}
*/




#endif
