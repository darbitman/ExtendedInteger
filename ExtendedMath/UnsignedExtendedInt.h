#ifndef _UNSIGNEDEXTENDEDINT_H_
#define _UNSIGNEDEXTENDEDINT_H_

#include "ExtendedIntLengths.h"

template<typename T>
class UnsignedExtendedInt {
protected:
    enum DIVIDE_OPERATION { DIVIDE_OP, MOD_OP };
    static unsigned int ARRAY_SIZE;
    unsigned int* ext_int;
    void initializeClass();
    void stringToUnsignedExtendedInt(const char* s);
public:
	UnsignedExtendedInt();
	UnsignedExtendedInt(const UnsignedExtendedInt& obj);
    UnsignedExtendedInt(const char* s);
	~UnsignedExtendedInt();
    const UnsignedExtendedInt& operator=(const UnsignedExtendedInt& obj);
    const UnsignedExtendedInt& operator=(const char* s);
    const UnsignedExtendedInt& operator+(const UnsignedExtendedInt& obj);
    const UnsignedExtendedInt& operator+(const unsigned long long& obj);
    const UnsignedExtendedInt& operator-(const UnsignedExtendedInt& obj);
    const UnsignedExtendedInt& operator*(const UnsignedExtendedInt& obj);
    const UnsignedExtendedInt& operator/(const UnsignedExtendedInt& divisor);
    const UnsignedExtendedInt& operator%(const UnsignedExtendedInt& divisor);
    const UnsignedExtendedInt& divideModOperator(const UnsignedExtendedInt& divisor, const DIVIDE_OPERATION op);
    bool operator==(const UnsignedExtendedInt& obj) const;
    bool operator>(const UnsignedExtendedInt& obj) const;
    bool operator>=(const UnsignedExtendedInt& obj) const;
    bool operator<(const UnsignedExtendedInt& obj) const;
    bool operator<=(const UnsignedExtendedInt& obj) const;
    UnsignedExtendedInt& operator>>(unsigned int shiftVal) const;
    UnsignedExtendedInt& operator<<(unsigned int shiftVal) const;
    UnsignedExtendedInt& operator&(const UnsignedExtendedInt& obj) const;
    UnsignedExtendedInt& operator&(const unsigned long long& obj) const;
    UnsignedExtendedInt& operator|(const UnsignedExtendedInt& obj) const;
    void setValueAtIndex(const unsigned long long val, const unsigned int index);
    unsigned long long getValueAtIndex(const unsigned int index) const;
};


template<typename T>
unsigned int UnsignedExtendedInt<T>::ARRAY_SIZE = 0;


template<typename T>
void UnsignedExtendedInt<T>::initializeClass() {
    ARRAY_SIZE = T::_multipleOf32Bits;
    ext_int = new unsigned int[ARRAY_SIZE];
    for (unsigned int i = 0; i < ARRAY_SIZE; i++) {
        ext_int[i] = 0;
    }
}


template<typename T>
void UnsignedExtendedInt<T>::stringToUnsignedExtendedInt(const char* s) {
    for (unsigned int i = 0; i < ARRAY_SIZE; i++) {
        this->ext_int[i] = 0;
    }
    unsigned int strLength = 0;
    while (s[strLength++] != 0) {}   // compute string length
    if (strLength > 0) {
        strLength--;
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


// Create new 128bit integer. Initialize to 0.
template<typename T>
UnsignedExtendedInt<T>::UnsignedExtendedInt() {
    initializeClass();
}


// Copy constructor
template<typename T>
UnsignedExtendedInt<T>::UnsignedExtendedInt(const UnsignedExtendedInt<T>& obj) {
    ARRAY_SIZE = obj.ARRAY_SIZE;
    ext_int = new unsigned int[ARRAY_SIZE];
    for (unsigned int i = 0; i < ARRAY_SIZE; i++) {
        this->ext_int[i] = obj.ext_int[i];
    }
}


// convert input string to extended integer
template<class T>
UnsignedExtendedInt<T>::UnsignedExtendedInt(const char* s) {
    initializeClass();
    stringToUnsignedExtendedInt(s);
}


template<typename T>
UnsignedExtendedInt<T>::~UnsignedExtendedInt() {
    delete[] ext_int;
}


template<typename T>
const UnsignedExtendedInt<T>& UnsignedExtendedInt<T>::operator=(const UnsignedExtendedInt& obj) {
    ARRAY_SIZE = obj.ARRAY_SIZE;
    ext_int = new unsigned int[ARRAY_SIZE];
    for (unsigned int i = 0; i < ARRAY_SIZE; i++) {
        this->ext_int[i] = obj.ext_int[i];
    }
    return *this;
}


template<typename T>
const UnsignedExtendedInt<T>& UnsignedExtendedInt<T>::operator=(const char* s) {
    ARRAY_SIZE = T::_multipleOf32Bits;
    ext_int = new unsigned int[ARRAY_SIZE];
    stringToUnsignedExtendedInt(s);
    return *this;
}


template<class T>
const UnsignedExtendedInt<T>& UnsignedExtendedInt<T>::operator+(const UnsignedExtendedInt<T>& obj) {
    unsigned long long x = 0;
    unsigned long long y = 0;
    unsigned long long z = 0;
    unsigned int carryBit = 0;
    UnsignedExtendedInt<T>* returnValue = new UnsignedExtendedInt<T>();
    for (unsigned int i = 0; i < ARRAY_SIZE; i++) {
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
    for (int i = 0; i < ARRAY_SIZE; i++) {
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
    long long x = 0;
    long long y = 0;
    UnsignedExtendedInt* returnValue = new UnsignedExtendedInt();
    UnsignedExtendedInt* negativeValue = new UnsignedExtendedInt();
    for (int i = 0; i < ARRAY_SIZE; i++) {
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
    for (unsigned int i = 0; i < ARRAY_SIZE; i++) {
        for (unsigned int j = 0; j < ARRAY_SIZE; j++) {
            leftShiftValue = i + j;
            x = this->ext_int[i];
            y = obj.ext_int[j];
            z = x * y;

            if (leftShiftValue < ARRAY_SIZE) {
                if (leftShiftValue > 0) {   // clear previous 32-bits because they will introduce an error in the summation
                    uExtIntTemp.setValueAtIndex(0, leftShiftValue - 1);
                }
                lowerResultBits = z & 0xFFFFFFFF;
                uExtIntTemp.setValueAtIndex(lowerResultBits, leftShiftValue);                   // Extract first 32-bits
            }
            if (leftShiftValue < ARRAY_SIZE - 1) {
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
    return divideModOperator(divisor, DIVIDE_OP);
}

template<typename T>
const UnsignedExtendedInt<T>& UnsignedExtendedInt<T>::operator%(const UnsignedExtendedInt& divisor) {
    return divideModOperator(divisor, MOD_OP);
}

template<typename T>
const UnsignedExtendedInt<T>& UnsignedExtendedInt<T>::divideModOperator(const UnsignedExtendedInt& divisor, const DIVIDE_OPERATION op) {
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
    if (op == DIVIDE_OP) {
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
    for (int i = ARRAY_SIZE - 1; i >= 0; i--) {
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
    for (int i = ARRAY_SIZE - 1; i >= 0; i--) {
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
    for (int i = ARRAY_SIZE - 1; i >= 0; i--) {
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
        for (int i = 0; i < ARRAY_SIZE; i++) {
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
        for (int i = ARRAY_SIZE - 1; i >= 0; i--) {
            x = returnValue->ext_int[i];
            x = x << (shiftVal > 32 ? 32 : shiftVal);       // perform shift
            returnValue->setValueAtIndex(x & 0xFFFFFFFF, i);        // lower 32 bits should be stored
            if (i < ARRAY_SIZE - 1) {
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
    for (int i = 0; i < ARRAY_SIZE; i++) {
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
    for (int i = 0; i < ARRAY_SIZE; i++) {
        returnValue->setValueAtIndex(this->getValueAtIndex(i) | obj.getValueAtIndex(i), i);
    }
    return *returnValue;
}

template<typename T>
void UnsignedExtendedInt<T>::setValueAtIndex(const unsigned long long val, const unsigned int index) {
    this->ext_int[index] = val & 0xFFFFFFFF;
}

template<typename T>
unsigned long long UnsignedExtendedInt<T>::getValueAtIndex(const unsigned int index) const {
    return this->ext_int[index];
}



typedef UnsignedExtendedInt<_extint128_t> extint128_t;
typedef UnsignedExtendedInt<_extint256_t> extint256_t;
typedef UnsignedExtendedInt<_extint512_t> extint512_t;

#endif
