#include "stdafx.h"
#include "UnsignedExtendedInt.h"

UnsignedExtendedInt::UnsignedExtendedInt() {
    for (int i = 0; i < ARRAY_SIZE; i++) {
        this->ext_int[i] = 0;
    }
}

UnsignedExtendedInt::UnsignedExtendedInt(const UnsignedExtendedInt& obj) {
    for (int i = 0; i < ARRAY_SIZE; i++) {
        this->ext_int[i] = obj.ext_int[i];
    }
}

UnsignedExtendedInt::UnsignedExtendedInt(const char* s) {
    for (int i = 0; i < ARRAY_SIZE; i++) {
        this->ext_int[i] = 0;
    }
    unsigned int strLength = 0;
    while (s[strLength++] != 0) {}   // compute string length
    if (strLength > 0) {
        strLength--;
    }
    UnsignedExtendedInt TEN;
    UnsignedExtendedInt powersOfTen;
    powersOfTen.setValueAtIndex(1, 0);
    TEN.setValueAtIndex(10, 0);
    UnsignedExtendedInt readInt;
    for (int i = strLength - 1; i >= 0; i--) {
        readInt.setValueAtIndex(s[i] - '0', 0);
        *this = *this + (powersOfTen * readInt);
        powersOfTen = powersOfTen * TEN;
    }
}

UnsignedExtendedInt::~UnsignedExtendedInt() {}

const UnsignedExtendedInt& UnsignedExtendedInt::operator=(const UnsignedExtendedInt& obj) {
    for (int i = 0; i < ARRAY_SIZE; i++) {
        this->ext_int[i] = obj.ext_int[i];
    }
    return *this;
}

const UnsignedExtendedInt& UnsignedExtendedInt::operator+(const UnsignedExtendedInt& obj) {
    unsigned long long x = 0;
    unsigned long long y = 0;
    unsigned long long z = 0;
    unsigned int carryBit = 0;
    UnsignedExtendedInt* returnValue = new UnsignedExtendedInt();
    for (int i = 0; i < ARRAY_SIZE; i++) {
        x = this->ext_int[i];
        y = obj.ext_int[i];
        z = x + y + carryBit;
        returnValue->ext_int[i] = z & 0xFFFFFFFF;
        carryBit = (z & 0x100000000) >> 32;
        // TODO
    }
    return *returnValue;
}

const UnsignedExtendedInt& UnsignedExtendedInt::operator+(const unsigned long long& obj) {
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

const UnsignedExtendedInt& UnsignedExtendedInt::operator-(const UnsignedExtendedInt& obj) {
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

const UnsignedExtendedInt& UnsignedExtendedInt::operator*(const UnsignedExtendedInt& obj) {
    unsigned long long x = 0;
    unsigned long long y = 0;
    unsigned long long z = 0;
    unsigned int upperResultBits = 0;
    unsigned int lowerResultBits = 0;
    unsigned int leftShiftValue = 0;
    UnsignedExtendedInt* returnValue = new UnsignedExtendedInt();
    UnsignedExtendedInt uExtIntTemp;
    for (int i = 0; i < ARRAY_SIZE; i++) {
        for (int j = 0; j < ARRAY_SIZE; j++) {
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

const UnsignedExtendedInt& UnsignedExtendedInt::operator/(const UnsignedExtendedInt& divisor) {
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
    if (divisor > *tempDividend) {
        // Extract bit i
        *tempDividend = ((*this & *maskBit) | (*tempDividend << 1));
    }
    else {
        maskBit->setValueAtIndex(1, 0);
        *returnValue = *returnValue | *maskBit;
        *tempDividend = *tempDividend - divisor;
    }
    return (*returnValue);
}

bool UnsignedExtendedInt::operator==(const UnsignedExtendedInt& obj) const {
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

bool UnsignedExtendedInt::operator>(const UnsignedExtendedInt& obj) const {
    for (int i = ARRAY_SIZE - 1; i >= 0; i--) {
        if (this->getValueAtIndex(i) > obj.getValueAtIndex(i)) {
            return true;
        }
    }
    return false;
}

bool UnsignedExtendedInt::operator>=(const UnsignedExtendedInt & obj) const {
    if (*this > obj || *this == obj) {
        return true;
    }
    return false;
}

bool UnsignedExtendedInt::operator<(const UnsignedExtendedInt& obj) const {
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

bool UnsignedExtendedInt::operator<=(const UnsignedExtendedInt & obj) const {
    if (*this < obj || *this == obj) {
        return true;
    }
    return false;
}

UnsignedExtendedInt& UnsignedExtendedInt::operator>>(unsigned int shiftVal) const {
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

UnsignedExtendedInt& UnsignedExtendedInt::operator<<(unsigned int shiftVal) const {
    unsigned long long x = 0;
    unsigned long long y = 0;
    UnsignedExtendedInt* returnValue = new UnsignedExtendedInt(*this);
    shiftVal = (shiftVal > 128 ? 128 : shiftVal);           // maximum shift is 128 bits
    while (shiftVal > 0) {
        for (int i = ARRAY_SIZE - 1; i >= 0; i--) {
            x = returnValue->ext_int[i];
            x = x << (shiftVal > 32 ? 32 : shiftVal);       // perform shift
            returnValue->setValueAtIndex(x & 0xFFFFFFFF , i);        // lower 32 bits should be stored
            if (i < ARRAY_SIZE - 1) {
                y = returnValue->ext_int[i + 1];
                returnValue->setValueAtIndex((x & 0xFFFFFFFF00000000) >> 32 | y, i + 1);                     // lower 32 bits ORd with previous entry since these bits were shifted into the the adjacent 32-bits
            }
        }
        shiftVal = (shiftVal >= 32 ? shiftVal - 32 : 0);
    }
    return *returnValue;
}

UnsignedExtendedInt& UnsignedExtendedInt::operator&(const UnsignedExtendedInt& obj) const {
    UnsignedExtendedInt* returnValue = new UnsignedExtendedInt();
    for (int i = 0; i < ARRAY_SIZE; i++) {
        returnValue->setValueAtIndex(this->getValueAtIndex(i) & obj.getValueAtIndex(i), i);
    }
    return *returnValue;
}

UnsignedExtendedInt& UnsignedExtendedInt::operator&(const unsigned long long& obj) const {
    UnsignedExtendedInt* returnValue = new UnsignedExtendedInt();
    returnValue->setValueAtIndex(this->getValueAtIndex(0) & (obj & 0xFFFFFFFF), 0);
    returnValue->setValueAtIndex(this->getValueAtIndex(1) & ((obj >> 32) & 0xFFFFFFFF), 0);
    return *returnValue;
}

UnsignedExtendedInt& UnsignedExtendedInt::operator|(const UnsignedExtendedInt& obj) const {
    UnsignedExtendedInt* returnValue = new UnsignedExtendedInt();
    for (int i = 0; i < ARRAY_SIZE; i++) {
        returnValue->setValueAtIndex(this->getValueAtIndex(i) | obj.getValueAtIndex(i), i);
    }
    return *returnValue;
}

void UnsignedExtendedInt::setValueAtIndex(const unsigned long long val, const unsigned int index) {
    this->ext_int[index] = val & 0xFFFFFFFF;
}

unsigned long long UnsignedExtendedInt::getValueAtIndex(const unsigned int index) const {
    return this->ext_int[index];
}
