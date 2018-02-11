#include "stdafx.h"
#include "SignedExtendedInt.h"


template class SignedExtendedInt<_extint128_t>;
template class SignedExtendedInt<_extint256_t>;
template class SignedExtendedInt<_extint512_t>;


template<typename T>
SignedExtendedInt<T>::SignedExtendedInt() {
    this->initialize();
}


template<typename T>
SignedExtendedInt<T>::SignedExtendedInt(const SignedExtendedInt<T>& obj) {
    this->initialize();
    for (unsigned int i = 0; i < this->ARRAY_SIZE; i++) {
        this->ext_int[i] = obj.ext_int[i];
    }
}


template<typename T>
void SignedExtendedInt<T>::stringToExtendedInt(const char* s) {
    unsigned int strLength = 0;
    while (s[strLength] != 0) {
        strLength++;
    }
    SignedExtendedInt<T> TEN;
    SignedExtendedInt<T> powersOfTen;
    powersOfTen.setValueAtIndex(1, 0);
    TEN.setValueAtIndex(10, 0);
    SignedExtendedInt<T> readInt;
    for (int i = strLength - 1; i >= 0; i--) {
        if (i == 0 && s[i] == '-') {
            for (unsigned int j = 0; j < this->ARRAY_SIZE; j++) {
                this->setValueAtIndex(~(this->getValueAtIndex(i)), i);
            }
            //*this = *this + 1;
            continue;
        }
        readInt.setValueAtIndex(s[i] - '0', 0);
    }
}

template<typename T>
SignedExtendedInt<T>::SignedExtendedInt(const char* s) {
    if (this->ARRAY_SIZE == 0)
        this->initialize();
    this->stringToExtendedInt(s);
}


template<typename T>
SignedExtendedInt<T>::~SignedExtendedInt() {
    delete[] this->ext_int;
}


template<typename T>
const SignedExtendedInt<T>& SignedExtendedInt<T>::operator=(const SignedExtendedInt<T>& obj) {
    this->ARRAY_SIZE = obj.ARRAY_SIZE;
    this->ext_int = new unsigned int[this->ARRAY_SIZE];
    for (unsigned int i = 0; i < this->ARRAY_SIZE; i++) {
        this->ext_int[i] = obj.ext_int[i];
    }
    return *this;
}


template<typename T>
const SignedExtendedInt<T>& SignedExtendedInt<T>::operator=(const char* s) {
    this->initialize();
    this->stringToExtendedInt(s);
    return *this;
}


template<typename T>
const SignedExtendedInt<T>& SignedExtendedInt<T>::operator+(const SignedExtendedInt<T>& obj) {
    unsigned long long x = 0;
    unsigned long long y = 0;
    unsigned long long z = 0;
    unsigned long long carryBit = 0;
    SignedExtendedInt<T>* returnValue = new SignedExtendedInt<T>();
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
const SignedExtendedInt<T>& SignedExtendedInt<T>::operator+(const long long& obj) {
    unsigned long long x = 0;
    unsigned long long y = 0;
    unsigned long long z = 0;
    unsigned int carryBit = 0;
    SignedExtendedInt<T>* returnValue = new SignedExtendedInt<T>();
    for (unsigned int i = 0; i < this->ARRAY_SIZE; i++) {
        x = this->ext_int[i];
        y = ((obj >> (i * 32)) & 0xFFFFFFFF);
        z = x + y + carryBit;
        returnValue->ext_int[i] = z & 0xFFFFFFFF;
        carryBit = (z & 0x100000000) >> 32;
    }
    return *returnValue;
}


template<typename T>
const SignedExtendedInt<T>& SignedExtendedInt<T>::operator-(const SignedExtendedInt<T>& obj) {
    SignedExtendedInt<T>* returnValue = new SignedExtendedInt<T>();
    SignedExtendedInt<T>* negativeValue = new SignedExtendedInt<T>();
    for (unsigned int i = 0; i < this->ARRAY_SIZE; i++) {
        negativeValue->setValueAtIndex(~(obj.getValueAtIndex(i)), i);
    }
    *negativeValue = *negativeValue + 1;
    *returnValue = this->operator+(*negativeValue);
    delete negativeValue;
    return *returnValue;
}


template<typename T>
const SignedExtendedInt<T>& SignedExtendedInt<T>::operator-(const long long& obj) {
    unsigned long long negObj = ~obj + 1;
    unsigned long long x = 0;
    unsigned long long y = 0;
    unsigned long long z = 0;
    unsigned int carryBit = 0;
    SignedExtendedInt<T>* returnValue = new SignedExtendedInt<T>();
    for (unsigned int i = 0; i < this->ARRAY_SIZE; i++) {
        x = this->ext_int[i];
        y = ((negObj >> (i * 32)) & 0xFFFFFFFF);
        z = x + y + carryBit;
        returnValue->ext_int[i] = z & 0xFFFFFFFF;
        carryBit = (z & 0x100000000) >> 32;
    }
    return *returnValue;
}


template<typename T>
const SignedExtendedInt<T>& SignedExtendedInt<T>::operator*(const SignedExtendedInt<T>& obj) {
    // This algorithm multiplies 32bit integers using native 64bit integers.
    unsigned long long sign1 = (this->getValueAtIndex(this->ARRAY_SIZE - 1) >> 31) & 0x1;       // Extract sign bit
    unsigned long long x = 0;
    unsigned long long y = 0;
    unsigned long long z = 0;
    unsigned int upperResultBits = 0;
    unsigned int lowerResultBits = 0;
    unsigned int leftShiftValue = 0;
    SignedExtendedInt<T>* returnValue = new SignedExtendedInt<T>();
    SignedExtendedInt<T> uExtIntTemp;
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
const SignedExtendedInt<T>& SignedExtendedInt<T>::operator*(const long long& obj) {
    unsigned long long sign1 = (this->getValueAtIndex(this->ARRAY_SIZE - 1) >> 31) & 0x1;       // extract sign bit
    if (sign1) {
        *this = ~(*this) + 1;
    }
    unsigned long long sign2 = (obj >> 63) & 0x1;
    unsigned long long unsignedObj = obj;
    if (sign2) {
        unsignedObj = ~unsignedObj + 1;
    }
    unsigned long long x = 0;
    unsigned long long y = 0;
    unsigned long long z = 0;
    unsigned int upperResultBits = 0;
    unsigned int lowerResultBits = 0;
    unsigned int leftShiftValue = 0;
    SignedExtendedInt<T>* returnValue = new SignedExtendedInt<T>();
    SignedExtendedInt<T> uExtIntTemp;
    for (unsigned int i = 0; i < this->ARRAY_SIZE; i++) {
        for (unsigned int j = 0; j < 2; j++) {
            leftShiftValue = i + j;
            x = this->ext_int[i];
            y = (unsignedObj >> (j * 32)) & 0xFFFFFFFF;
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
    if (sign1 ^ sign2) {
        *returnValue = ~(*returnValue) + 1;
    }
    return *returnValue;
}


template<typename T>
const SignedExtendedInt<T>& SignedExtendedInt<T>::operator/(const SignedExtendedInt<T>& divisor) {
    return divideModOperator(divisor, this->DIVIDE_OP);
}


template<typename T>
const SignedExtendedInt<T>& SignedExtendedInt<T>::divideModOperator(const SignedExtendedInt<T>& divisor, const ExtendedInt<T>::DIVIDE_OPERATION op) {
    unsigned long long sign1 = (this->getValueAtIndex(this->ARRAY_SIZE - 1) >> 31) & 0x1;       // extract sign bit
    if (sign1) {
        *this = (*this) + 1;
    }
    return *(new SignedExtendedInt<T>());
}


template<typename T>
SignedExtendedInt<T>& SignedExtendedInt<T>::operator~() const {
    SignedExtendedInt<T>* returnValue = new SignedExtendedInt<T>();
    for (unsigned int i = 0; i < this->ARRAY_SIZE; i++) {
        returnValue->ext_int[i] = ~(this->ext_int[i]);
    }
    return *returnValue;
}