#include "stdafx.h"
#include "UnsignedExtendedInt.h"


template class UnsignedExtendedInt<_extint128_t>;
template class UnsignedExtendedInt<_extint256_t>;
template class UnsignedExtendedInt<_extint512_t>;


// Create new extended integer
template<typename T>
UnsignedExtendedInt<T>::UnsignedExtendedInt() {
    this->initialize();
}


// Copy constructor
template<typename T>
UnsignedExtendedInt<T>::UnsignedExtendedInt(const UnsignedExtendedInt& obj) {
    this->ARRAY_SIZE = obj.ARRAY_SIZE;
    this->ext_int = new unsigned int[this->ARRAY_SIZE];
    for (unsigned int i = 0; i < this->ARRAY_SIZE; i++) {
        this->ext_int[i] = obj.ext_int[i];
    }
}


// convert input string to extended integer
template<class T>
UnsignedExtendedInt<T>::UnsignedExtendedInt(const char* s) {
    this->initialize();
    this->stringToExtendedInt(s);
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


template<typename T>
UnsignedExtendedInt<T>::~UnsignedExtendedInt() {
    delete[] this->ext_int;
}


template<typename T>
const UnsignedExtendedInt<T>& UnsignedExtendedInt<T>::operator=(const UnsignedExtendedInt<T>& obj) {
    this->ARRAY_SIZE = obj.ARRAY_SIZE;
    delete[] this->ext_int;
    this->ext_int = new unsigned int[this->ARRAY_SIZE];
    for (unsigned int i = 0; i < this->ARRAY_SIZE; i++) {
        this->ext_int[i] = obj.ext_int[i];
    }
    return *this;
}


template<typename T>
const UnsignedExtendedInt<T>& UnsignedExtendedInt<T>::operator=(const char* s) {
    this->stringToExtendedInt(s);
    return *this;
}


template<class T>
const UnsignedExtendedInt<T> UnsignedExtendedInt<T>::operator+(const UnsignedExtendedInt<T>& obj) {
    unsigned long long x = 0;
    unsigned long long y = 0;
    unsigned long long z = 0;
    unsigned int carryBit = 0;
    UnsignedExtendedInt<T> returnValue;
    for (unsigned int i = 0; i < this->ARRAY_SIZE; i++) {
        x = this->ext_int[i];
        y = obj.ext_int[i];
        z = x + y + carryBit;
        returnValue.ext_int[i] = z & 0xFFFFFFFF;
        carryBit = (z & 0x100000000) >> 32;
    }
    return returnValue;
}


template<typename T>
const UnsignedExtendedInt<T> UnsignedExtendedInt<T>::operator+(const unsigned long long& obj) {
    unsigned long long x = 0;
    unsigned long long y = 0;
    unsigned long long z = 0;
    unsigned int carryBit = 0;
    UnsignedExtendedInt<T> returnValue;
    for (unsigned int i = 0; i < this->ARRAY_SIZE; i++) {
        x = this->ext_int[i];
        y = ((obj >> (i * 32)) & 0xFFFFFFFF);
        z = x + y + carryBit;
        returnValue.ext_int[i] = z & 0xFFFFFFFF;
        carryBit = (z & 0x100000000) >> 32;
    }
    return returnValue;
}


template<typename T>
const UnsignedExtendedInt<T> UnsignedExtendedInt<T>::operator-(const UnsignedExtendedInt& obj) {
    return this->operator+((~obj) + 1);
}


template<typename T>
const UnsignedExtendedInt<T> UnsignedExtendedInt<T>::operator-(const unsigned long long& obj) {
    return this->operator+((~obj) + 1);
}


template<typename T>
const UnsignedExtendedInt<T> UnsignedExtendedInt<T>::operator*(const UnsignedExtendedInt& obj) {
    // This algorithm multiplies 32bit integers using native 64bit integers.
    unsigned long long x = 0;
    unsigned long long y = 0;
    unsigned long long z = 0;
    unsigned int upperResultBits = 0;
    unsigned int lowerResultBits = 0;
    unsigned int leftShiftValue = 0;
    UnsignedExtendedInt<T> returnValue;
    UnsignedExtendedInt<T> uExtIntTemp;
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
                uExtIntTemp.setValueAtIndex(lowerResultBits, leftShiftValue);       // Extract first 32-bits
            }
            if (leftShiftValue < this->ARRAY_SIZE - 1) {
                upperResultBits = (z >> 32) & 0xFFFFFFFF;
                uExtIntTemp.setValueAtIndex(upperResultBits, leftShiftValue + 1);   // Extract upper 32-bits
            }
            returnValue = returnValue + uExtIntTemp;
        }
    }
    return returnValue;
}


template<typename T>
const UnsignedExtendedInt<T> UnsignedExtendedInt<T>::operator/(const UnsignedExtendedInt& divisor) {
    return divideModOperator(divisor, this->DIVIDE_OP);
}


template<typename T>
const UnsignedExtendedInt<T> UnsignedExtendedInt<T>::operator%(const UnsignedExtendedInt& divisor) {
    return divideModOperator(divisor, this->MOD_OP);
}


template<typename T>
const UnsignedExtendedInt<T> UnsignedExtendedInt<T>::divideModOperator(const UnsignedExtendedInt& divisor, const ExtendedInt<T>::DIVIDE_OPERATION op) {
    unsigned long long x = 0;
    unsigned long long y = 0;
    UnsignedExtendedInt<T> returnValue;
    UnsignedExtendedInt<T> tempDividend;
    UnsignedExtendedInt<T> maskBit;
    maskBit.setValueAtIndex(1, 0);
    if (*this < divisor) {
        return returnValue;    // if dividend is smaller than divisor, return 0 (e.g. 10 / 20 = 0)
    }
    int i = 128;
    maskBit = maskBit << (i - 1);
    while (--i >= 0) {
        if (divisor > tempDividend) {
            // Extract bit i
            tempDividend = (((*this & maskBit) >> i) | (tempDividend << 1));
            maskBit = maskBit >> 1;
        }
        else {
            returnValue = returnValue | (maskBit << 1);
            tempDividend = tempDividend - divisor;
            i++;
        }
    }

    // Extract bit 0 of the quotient
    if (divisor <= tempDividend) {
        maskBit.setValueAtIndex(1, 0);
        returnValue = returnValue | maskBit;
        tempDividend = tempDividend - divisor;          // remainder
    }

    if (op == this->DIVIDE_OP) return returnValue;      // quotient
    else return tempDividend;                           // mod operation returns remainder
}


template<typename T>
bool UnsignedExtendedInt<T>::operator==(const UnsignedExtendedInt<T>& obj) const {
    for (int i = this->ARRAY_SIZE - 1; i >= 0; i--) {
        if (this->ext_int[i] != obj.ext_int[i]) {
            return false;
        }
    }
    return true;
}


template<typename T>
bool UnsignedExtendedInt<T>::operator>(const UnsignedExtendedInt<T>& obj) const {
    for (int i = this->ARRAY_SIZE - 1; i >= 0; i--) {
        if (this->ext_int[i] > obj.ext_int[i]) {
            return true;
        }
        else if (this->ext_int[i] == obj.ext_int[i]) {
            continue;
        }
        else {
            return false;
        }
    }
    return false;
}


template<typename T> 
bool UnsignedExtendedInt<T>::operator>=(const UnsignedExtendedInt<T>& obj) const {
    for (int i = this->ARRAY_SIZE - 1; i >= 0; i--) {
        if (this->ext_int[i] > obj.ext_int[i]) {
            return true;
        }
        else if (this->ext_int[i] == obj.ext_int[i]) {
            continue;
        }
        else {
            return false;
        }
    }
    return true;
}


template<typename T>
bool UnsignedExtendedInt<T>::operator<(const UnsignedExtendedInt<T>& obj) const {
    for (int i = this->ARRAY_SIZE - 1; i >= 0; i--) {
        if (this->ext_int[i] < obj.ext_int[i]) {
            return true;
        }
        else if (this->ext_int[i] == obj.ext_int[i]) {
            continue;
        }
        else {
            return false;
        }
    }
    return false;
}


template<typename T>
bool UnsignedExtendedInt<T>::operator<=(const UnsignedExtendedInt<T>& obj) const {
    for (int i = this->ARRAY_SIZE - 1; i >= 0; i--) {
        if (this->ext_int[i] < obj.ext_int[i]) {
            return true;
        }
        else if (this->ext_int[i] == obj.ext_int[i]) {
            continue;
        }
        else {
            return false;
        }
    }
    return true;
}


template<typename T>
const UnsignedExtendedInt<T> UnsignedExtendedInt<T>::operator>>(unsigned int shiftVal) const {
    unsigned long long x = 0;
    unsigned long long y = 0;
    UnsignedExtendedInt<T> returnValue(*this);
    shiftVal = (shiftVal > T::_multipleOf32Bits * 32 ? T::_multipleOf32Bits * 32 : shiftVal);       // bound maximum shift
    while (shiftVal > 0) {
        for (unsigned int i = 0; i < this->ARRAY_SIZE; i++) {
            x = returnValue.ext_int[i];
            x = x << 32;
            x = x >> (shiftVal > 32 ? 32 : shiftVal);       // perform shift
            returnValue.setValueAtIndex((x & 0xFFFFFFFF00000000) >> 32, i);     // upper 32 bits should be stored
            if (i > 0) {
                y = returnValue.ext_int[i - 1];
                returnValue.setValueAtIndex((x & 0xFFFFFFFF) | y, i - 1);      // lower 32 bits ORd with previous entry since these bits were shifted into the the adjacent 32-bits
            }
        }
        shiftVal = (shiftVal >= 32 ? shiftVal - 32 : 0);
    }
    return returnValue;
}


template<typename T>
const UnsignedExtendedInt<T> UnsignedExtendedInt<T>::operator<<(unsigned int shiftVal) const {
    unsigned long long x = 0;
    unsigned long long y = 0;
    UnsignedExtendedInt<T> returnValue(*this);
    shiftVal = (shiftVal > T::_multipleOf32Bits * 32 ? T::_multipleOf32Bits * 32 : shiftVal);       // bound maximum shift
    while (shiftVal > 0) {
        for (unsigned int i = this->ARRAY_SIZE - 1; i >= 0; i--) {
            x = returnValue.ext_int[i];
            x = x << (shiftVal > 32 ? 32 : shiftVal);           // perform shift
            returnValue.setValueAtIndex(x & 0xFFFFFFFF, i);     // lower 32 bits should be stored
            if (i < this->ARRAY_SIZE - 1) {
                y = returnValue.ext_int[i + 1];
                returnValue.setValueAtIndex((x & 0xFFFFFFFF00000000) >> 32 | y, i + 1);            // lower 32 bits ORd with previous entry since these bits were shifted into the the adjacent 32-bits
            }
        }
        shiftVal = (shiftVal >= 32 ? shiftVal - 32 : 0);
    }
    return returnValue;
}


template<typename T>
inline UnsignedExtendedInt<T> UnsignedExtendedInt<T>::operator&(const UnsignedExtendedInt<T>& obj) const {
    UnsignedExtendedInt<T> returnValue;
    for (unsigned int i = 0; i < this->ARRAY_SIZE; i++) {
        returnValue.ext_int[i] = this->ext_int[i] & obj.ext_int[i];
    }
    return returnValue;
}


template<typename T>
inline UnsignedExtendedInt<T> UnsignedExtendedInt<T>::operator&(const unsigned long long& obj) const {
    UnsignedExtendedInt<T> returnValue;
    returnValue.ext_int[0] = this->ext_int[0] & (obj & 0xFFFFFFFF);
    returnValue.ext_int[1] = this->ext_int[1] & ((obj >> 32) & 0xFFFFFFFF);
    return returnValue;
}


template<typename T>
inline UnsignedExtendedInt<T> UnsignedExtendedInt<T>::operator|(const UnsignedExtendedInt<T>& obj) const {
    UnsignedExtendedInt<T> returnValue;
    for (unsigned int i = 0; i < this->ARRAY_SIZE; i++) {
        returnValue.ext_int[i] = this->ext_int[i] | obj.ext_int[i];
    }
    return returnValue;
}

template<typename T>
inline UnsignedExtendedInt<T> UnsignedExtendedInt<T>::operator|(const unsigned long long& obj) const {
    UnsignedExtendedInt<T> returnValue;
    returnValue.ext_int[0] = this->ext_int[0] | (obj & 0xFFFFFFFF);
    returnValue.ext_int[1] = this->ext_int[1] | ((obj >> 32) & 0xFFFFFFFF);
    return returnValue;
}


template<typename T>
inline UnsignedExtendedInt<T> UnsignedExtendedInt<T>::operator^(const UnsignedExtendedInt<T>& obj) const {
    UnsignedExtendedInt<T> returnValue;
    for (unsigned int i = 0; i < this->ARRAY_SIZE; i++) {
        returnValue.ext_int[i] = this->ext_int[i] ^ obj.ext_int[i];
    }
    return returnValue;
}

template<typename T>
inline UnsignedExtendedInt<T> UnsignedExtendedInt<T>::operator^(const unsigned long long& obj) const {
    UnsignedExtendedInt<T> returnValue;
    returnValue.ext_int[0] = this->ext_int[0] ^ (obj & 0xFFFFFFFF);
    returnValue.ext_int[1] = this->ext_int[1] ^ ((obj >> 32) & 0xFFFFFFFF);
    return returnValue;
}


template<typename T>
inline UnsignedExtendedInt<T> UnsignedExtendedInt<T>::operator~() const {
    UnsignedExtendedInt<T> returnValue;
    for (unsigned int i = 0; i < this->ARRAY_SIZE; i++) {
        returnValue.ext_int[i] = ~(this->ext_int[i]);
    }
    return returnValue;
}