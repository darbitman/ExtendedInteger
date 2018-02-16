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
    unsigned int signBit = 0;
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
        if (i == strLength - 1 && s[i] == '-') {
            signBit = 1;
            continue;
        }
        readInt.ext_int[0] = s[i] - '0';
        *this = *this + (powersOfTen * readInt);
        powersOfTen = powersOfTen * TEN;
    }

}

template<typename T>
char* SignedExtendedInt<T>::extendedIntToString() const {
    char* c = new char();
    return c;
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
const SignedExtendedInt<T> SignedExtendedInt<T>::operator+(const SignedExtendedInt<T>& obj) const {
    unsigned long long x = 0;
    unsigned long long y = 0;
    unsigned long long z = 0;
    unsigned long long carryBit = 0;
    SignedExtendedInt<T> returnValue;
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
const SignedExtendedInt<T> SignedExtendedInt<T>::operator+(const long long& obj) const {
    unsigned long long x = 0;
    unsigned long long y = 0;
    unsigned long long z = 0;
    unsigned int carryBit = 0;
    SignedExtendedInt<T> returnValue;
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
const SignedExtendedInt<T> SignedExtendedInt<T>::operator-(const SignedExtendedInt<T>& obj) const {
    return this->operator+((~obj) + 1);
}


template<typename T>
const SignedExtendedInt<T> SignedExtendedInt<T>::operator-(const long long& obj) const {
    unsigned long long negObj = ~obj + 1;
    unsigned long long x = 0;
    unsigned long long y = 0;
    unsigned long long z = 0;
    unsigned int carryBit = 0;
    SignedExtendedInt<T> returnValue;
    for (unsigned int i = 0; i < this->ARRAY_SIZE; i++) {
        x = this->ext_int[i];
        y = ((negObj >> (i * 32)) & 0xFFFFFFFF);
        z = x + y + carryBit;
        returnValue.ext_int[i] = z & 0xFFFFFFFF;
        carryBit = (z & 0x100000000) >> 32;
    }
    return returnValue;
}


template<typename T>
const SignedExtendedInt<T> SignedExtendedInt<T>::operator*(const SignedExtendedInt<T>& obj) const {
    // This algorithm multiplies 32bit integers using native 64bit integers.
    unsigned long long sign1 = (this->ext_int[this->ARRAY_SIZE - 1] >> 31) & 0x1;       // Extract sign bit of calling obj
    unsigned long long sign2 = (obj.ext_int[obj.ARRAY_SIZE - 1] >> 31) & 0x1;           // Extract sign bit
    SignedExtendedInt<T> unsignedThis(sign1 ? ((~(*this)) + 1) : (*this));              // if calling obj is negative, return positive value
    SignedExtendedInt<T> unsignedObj(sign2 ? ((~obj) + 1) : obj);                       // if multiplier is negative, return positive value
    unsigned long long x = 0;
    unsigned long long y = 0;
    unsigned long long z = 0;
    unsigned int upperResultBits = 0;
    unsigned int lowerResultBits = 0;
    unsigned int leftShiftValue = 0;
    SignedExtendedInt<T> returnValue;
    SignedExtendedInt<T> extIntTemp;
    for (unsigned int i = 0; i < unsignedThis.ARRAY_SIZE; i++) {
        for (unsigned int j = 0; j < unsignedObj.ARRAY_SIZE; j++) {
            leftShiftValue = i + j;
            x = unsignedThis.ext_int[i];
            y = unsignedObj.ext_int[j];
            z = x * y;

            if (leftShiftValue < unsignedThis.ARRAY_SIZE) {
                if (leftShiftValue > 0) {       // clear previous 32-bits because they will introduce an error in the summation
                    extIntTemp.ext_int[leftShiftValue - 1] = 0;
                }
                lowerResultBits = z & 0xFFFFFFFF;
                extIntTemp.ext_int[leftShiftValue] = lowerResultBits;               // Extract first 32-bits
            }
            if (leftShiftValue < unsignedThis.ARRAY_SIZE - 1) {
                upperResultBits = (z >> 32) & 0xFFFFFFFF;
                extIntTemp.ext_int[leftShiftValue + 1] = upperResultBits;           // Extract upper 32-bits
            }
            returnValue = returnValue + extIntTemp;
        }
    }
    if (sign1 ^ sign2) {            // result is negative if one of the ext_ints is negative, otherwise positive (XOR function)
        returnValue = (~returnValue) + 1;
    }
    return returnValue;
}


template<typename T>
const SignedExtendedInt<T> SignedExtendedInt<T>::operator*(const long long& obj) const {
    unsigned long long sign1 = (this->ext_int[this->ARRAY_SIZE - 1] >> 31) & 0x1;       // Extract sign bit of calling obj
    unsigned long long sign2 = (obj >> 63) & 0x1;                                       // Extract sign bit
    SignedExtendedInt<T> unsignedThis(sign1 ? ((~(*this)) + 1) : (*this));              // if calling obj is negative, return positive value
    unsigned long long unsignedObj = sign2 ? ((~obj) + 1) : obj;                        // if multiplier is negative, return positive value
    unsigned long long x = 0;
    unsigned long long y = 0;
    unsigned long long z = 0;
    unsigned int upperResultBits = 0;
    unsigned int lowerResultBits = 0;
    unsigned int leftShiftValue = 0;
    SignedExtendedInt<T> returnValue;
    SignedExtendedInt<T> extIntTemp;
    for (unsigned int i = 0; i < unsignedThis.ARRAY_SIZE; i++) {
        for (unsigned int j = 0; j < 2; j++) {
            leftShiftValue = i + j;
            x = unsignedThis.ext_int[i];
            y = (unsignedObj >> (j * 32)) & 0xFFFFFFFF;
            z = x * y;

            if (leftShiftValue < unsignedThis.ARRAY_SIZE) {
                if (leftShiftValue > 0) {   // clear previous 32-bits because they will introduce an error in the summation
                    extIntTemp.ext_int[leftShiftValue - 1] = 0;
                }
                lowerResultBits = z & 0xFFFFFFFF;
                extIntTemp.ext_int[leftShiftValue] = lowerResultBits;   // Extract first 32-bits
            }
            if (leftShiftValue < unsignedThis.ARRAY_SIZE - 1) {
                upperResultBits = (z >> 32) & 0xFFFFFFFF;
                extIntTemp.ext_int[leftShiftValue + 1];                 // Extract upper 32-bits
            }
            returnValue = returnValue + extIntTemp;
        }
    }
    if (sign1 ^ sign2) {            // result is negative if 1 or the other ext int is negative, otherwise positive (XOR function)
        returnValue = (~returnValue) + 1;
    }
    return returnValue;
}


template<typename T>
const SignedExtendedInt<T> SignedExtendedInt<T>::operator/(const SignedExtendedInt<T>& divisor) const {
    return divideModOperator(divisor, this->DIVIDE_OP);
}


template<typename T>
const SignedExtendedInt<T> SignedExtendedInt<T>::operator%(const SignedExtendedInt<T>& divisor) const {
    return divideModOperator(divisor, this->MOD_OP);
}


template<typename T>
const SignedExtendedInt<T> SignedExtendedInt<T>::divideModOperator(const SignedExtendedInt<T>& divisor, const ExtendedInt<T>::DIVIDE_OPERATION op) const {
    unsigned long long sign1 = (this->ext_int[this->ARRAY_SIZE - 1] >> 31) & 0x1;       // Extract sign bit of calling obj
    unsigned long long sign2 = (divisor.ext_int[divisor.ARRAY_SIZE - 1] >> 31) & 0x1;   // Extract sign bit of divisor
    SignedExtendedInt<T> unsignedThis(sign1 ? ((~(*this)) + 1) : (*this));              // if calling obj is negative, return positive value
    SignedExtendedInt<T> unsignedDivisor(sign2 ? ((~divisor) + 1) : divisor);           // if multiplier is negative, return positive value
    unsigned long long x = 0;
    unsigned long long y = 0;
    SignedExtendedInt<T> returnValue;
    SignedExtendedInt<T> tempDividend;
    SignedExtendedInt<T> maskBit;
    maskBit.ext_int[0] = 1;
    if (unsignedThis < unsignedDivisor) {
        return returnValue;    // if dividend is smaller than divisor, return 0 (e.g. 10 / 20 = 0)
    }
    int i = unsignedThis.ARRAY_SIZE;
    maskBit = maskBit << (i - 1);
    while (--i >= 0) {
        if (unsignedDivisor > tempDividend) {
            // Extract bit i
            tempDividend = (((unsignedThis & maskBit) >> i) | (tempDividend << 1));
            maskBit = maskBit >> 1;
        }
        else {
            returnValue = returnValue | (maskBit << 1);
            tempDividend = tempDividend - divisor;
            i++;
        }
    }

    // Extract bit 0 of the quotient
    if (unsignedDivisor <= tempDividend) {
        maskBit.ext_int[0] = 1;
        returnValue = returnValue | maskBit;
        tempDividend = tempDividend - divisor;   // remainder
    }

    if (op == unsignedThis.DIVIDE_OP) {         // if division
        if (sign1 ^ sign2) {                    // result is negative if one of the ext_ints is negative, otherwise positive (XOR function)
            returnValue = (~returnValue) + 1;   // quotient
        }
        return returnValue;
    }
    else {                                      // otherwise mod
        if (sign1) {                            // result is negative if dividend is negative
            tempDividend = (~tempDividend) + 1; // remainder
        }
        return tempDividend;
    }
}


template<typename T>
bool SignedExtendedInt<T>::operator==(const SignedExtendedInt<T>& obj) const {
    for (int i = this->ARRAY_SIZE - 1; i >= 0; i--) {
        if (this->ext_int[i] != obj.ext_int[i]) {
            return false;
        }
    }
    return true;
}


template<typename T>
bool SignedExtendedInt<T>::operator<(const SignedExtendedInt<T>& obj) const {
    unsigned long long sign1 = (this->ext_int[this->ARRAY_SIZE - 1] >> 31) & 0x1;   // Extract sign bit of calling obj
    unsigned long long sign2 = (obj.ext_int[obj.ARRAY_SIZE - 1] >> 31) & 0x1;       // Extract sign bit of rhs obj
    if (sign1 && !sign2) {
        return true;
    }
    else if (sign2 && !sign1) {
        return false;
    }
    else {
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
}


template<typename T>
bool SignedExtendedInt<T>::operator>(const SignedExtendedInt<T>& obj) const {
    unsigned long long sign1 = (this->ext_int[this->ARRAY_SIZE - 1] >> 31) & 0x1;   // Extract sign bit of calling obj
    unsigned long long sign2 = (obj.ext_int[obj.ARRAY_SIZE - 1] >> 31) & 0x1;       // Extract sign bit of rhs obj
    if (sign1 && !sign2) {
        return false;
    }
    else if (sign2 && !sign1) {
        return true;
    }
    else {
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
}


template<typename T>
bool SignedExtendedInt<T>::operator<=(const SignedExtendedInt<T>& obj) const {
    unsigned long long sign1 = (this->ext_int[this->ARRAY_SIZE - 1] >> 31) & 0x1;   // Extract sign bit of calling obj
    unsigned long long sign2 = (obj.ext_int[obj.ARRAY_SIZE - 1] >> 31) & 0x1;       // Extract sign bit of rhs obj
    if (sign1 && !sign2) {
        return true;
    }
    else if (sign2 && !sign1) {
        return false;
    }
    else {
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
}


template<typename T>
const SignedExtendedInt<T> SignedExtendedInt<T>::operator>>(unsigned int shiftVal) const {
    unsigned long long x = 0;
    unsigned long long y = 0;
    SignedExtendedInt<T> returnValue(*this);
    shiftVal = (shiftVal > T::_multipleOf32Bits * 32 ? T::_multipleOf32Bits * 32 : shiftVal);       // bound maximum shift
    while (shiftVal > 0) {
        for (unsigned int i = 0; i < this->ARRAY_SIZE; i++) {
            x = returnValue.ext_int[i];
            x = x << 32;
            x = x >> (shiftVal > 32 ? 32 : shiftVal);                   // perform shift
            returnValue.ext_int[i] = (x & 0xFFFFFFFF00000000) >> 32;    // upper 32 bits should be stored
            if (i > 0) {
                y = returnValue.ext_int[i - 1];
                returnValue.ext_int[i - 1] = (unsigned int)((x & 0xFFFFFFFF) | y);                  // lower 32 bits ORd with previous entry since these bits were shifted into the the adjacent 32-bits
            }
        }
        shiftVal = (shiftVal >= 32 ? shiftVal - 32 : 0);
    }
    return returnValue;
}


template<typename T>
const SignedExtendedInt<T> SignedExtendedInt<T>::operator<<(unsigned int shiftVal) const {
    unsigned long long x = 0;
    unsigned long long y = 0;
    SignedExtendedInt<T> returnValue(*this);
    shiftVal = (shiftVal > T::_multipleOf32Bits * 32 ? T::_multipleOf32Bits * 32 : shiftVal);       // bound maximum shift
    while (shiftVal > 0) {
        for (unsigned int i = this->ARRAY_SIZE - 1; i >= 0; i--) {
            x = returnValue.ext_int[i];
            x = x << (shiftVal > 32 ? 32 : shiftVal);    // perform shift
            returnValue.ext_int[i] = x & 0xFFFFFFFF;     // lower 32 bits should be stored
            if (i < this->ARRAY_SIZE - 1) {
                y = returnValue.ext_int[i + 1];
                returnValue.ext_int[i + 1] = (unsigned int)((x & 0xFFFFFFFF00000000) >> 32 | y);    // lower 32 bits ORd with previous entry since these bits were shifted into the the adjacent 32-bits
            }
        }
        shiftVal = (shiftVal >= 32 ? shiftVal - 32 : 0);
    }
    return returnValue;
}


template<typename T>
inline SignedExtendedInt<T> SignedExtendedInt<T>::operator&(const SignedExtendedInt<T>& obj) const {
    SignedExtendedInt<T> returnValue;
    for (unsigned int i = 0; i < this->ARRAY_SIZE; i++) {
        returnValue.ext_int[i] = this->ext_int[i] & obj.ext_int[i];
    }
    return returnValue;
}


template<typename T>
inline SignedExtendedInt<T> SignedExtendedInt<T>::operator&(const unsigned long long& obj) const {
    SignedExtendedInt<T> returnValue;
    returnValue.ext_int[0] = this->ext_int[0] & (obj & 0xFFFFFFFF);
    returnValue.ext_int[1] = this->ext_int[1] & ((obj >> 32) & 0xFFFFFFFF);
    return returnValue;
}


template<typename T>
inline SignedExtendedInt<T> SignedExtendedInt<T>::operator|(const SignedExtendedInt<T>& obj) const {
    SignedExtendedInt<T> returnValue;
    for (unsigned int i = 0; i < this->ARRAY_SIZE; i++) {
        returnValue.ext_int[i] = this->ext_int[i] | obj.ext_int[i];
    }
    return returnValue;
}


template<typename T>
inline SignedExtendedInt<T> SignedExtendedInt<T>::operator|(const unsigned long long& obj) const {
    SignedExtendedInt<T> returnValue;
    returnValue.ext_int[0] = this->ext_int[0] | (obj & 0xFFFFFFFF);
    returnValue.ext_int[1] = this->ext_int[1] | ((obj >> 32) & 0xFFFFFFFF);
    return returnValue;
}


template<typename T>
inline SignedExtendedInt<T> SignedExtendedInt<T>::operator^(const SignedExtendedInt<T>& obj) const {
    SignedExtendedInt<T> returnValue;
    for (unsigned int i = 0; i < this->ARRAY_SIZE; i++) {
        returnValue.ext_int[i] = this->ext_int[i] ^ obj.ext_int[i];
    }
    return returnValue;
}


template<typename T>
inline SignedExtendedInt<T> SignedExtendedInt<T>::operator^(const unsigned long long& obj) const {
    SignedExtendedInt<T> returnValue;
    returnValue.ext_int[0] = this->ext_int[0] ^ (obj & 0xFFFFFFFF);
    returnValue.ext_int[1] = this->ext_int[1] ^ ((obj >> 32) & 0xFFFFFFFF);
    return returnValue;
}


template<typename T>
inline const SignedExtendedInt<T> SignedExtendedInt<T>::operator~() const {
    SignedExtendedInt<T> returnValue;
    for (unsigned int i = 0; i < this->ARRAY_SIZE; i++) {
        returnValue.ext_int[i] = ~(this->ext_int[i]);
    }
    return returnValue;
}
