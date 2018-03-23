#ifndef _UNSIGNEDEXTENDEDINT_H_
#define _UNSIGNEDEXTENDEDINT_H_


#include "ExtendedInt.h"


template<unsigned int t = 4>
class UnsignedExtendedInt : public ExtendedInt<t> {
protected:
    void stringToExtendedInt(const char* s);
    std::string extendedIntToString() const;
    template<unsigned int u> typename extIntReturnSize<t, u>::uIntReturnTypeMax_ divideModOperator(const UnsignedExtendedInt<u>& divisor, const ExtendedInt<t>::DIVIDE_OPERATION op) const;
    template<unsigned int u> typename extIntReturnSize<t, u>::uIntReturnTypeMax_ addOperator(const UnsignedExtendedInt<u>& obj) const;
    template<unsigned int u> typename extIntReturnSize<t, u>::uIntReturnTypeMax_ subtractOperator(const UnsignedExtendedInt<u>& obj) const;
    template<unsigned int u> typename extIntReturnSize<t, u>::uIntReturnTypeTot_ multiplyOperator(const UnsignedExtendedInt<u>& obj) const;
    template<unsigned int u> UnsignedExtendedInt<t> equalOperator(const UnsignedExtendedInt<u>& obj);
    template<unsigned int u> bool isEqualOperator(const UnsignedExtendedInt<u>& obj) const;
    template<unsigned int u> bool greaterThanOperator(const UnsignedExtendedInt<u>& obj) const;
    template<unsigned int u> bool greaterThanOrEqualOperator(const UnsignedExtendedInt<u>& obj) const;
    template<unsigned int u> bool lessThanOperator(const UnsignedExtendedInt<u>& obj) const;
    template<unsigned int u> bool lessThanOrEqualOperator(const UnsignedExtendedInt<u>& obj) const;
    template<unsigned int u> UnsignedExtendedInt<t> rightShiftOperator(const UnsignedExtendedInt<u>& obj) const;
    template<unsigned int u> UnsignedExtendedInt<t> leftShiftOperator(const UnsignedExtendedInt<u>& obj) const;
    template<unsigned int u> typename extIntReturnSize<t, u>::uIntReturnTypeMax_ andOperator(const UnsignedExtendedInt<u>& obj) const;
    template<unsigned int u> typename extIntReturnSize<t, u>::uIntReturnTypeMax_ orOperator(const UnsignedExtendedInt<u>& obj) const;
    template<unsigned int u> typename extIntReturnSize<t, u>::uIntReturnTypeMax_ xorOperator(const UnsignedExtendedInt<u>& obj) const;
public:
	UnsignedExtendedInt();
    template<unsigned int u> UnsignedExtendedInt(const UnsignedExtendedInt<u>& obj);
    template<unsigned int u> UnsignedExtendedInt(const SignedExtendedInt<u>& obj);
    UnsignedExtendedInt(unsigned long long obj);
    UnsignedExtendedInt(const char* s) { stringToExtendedInt(s); }
    ~UnsignedExtendedInt() {}
    template<unsigned int u> UnsignedExtendedInt<t> operator=(const UnsignedExtendedInt<u>& obj) { return equalOperator(obj); }
    const UnsignedExtendedInt& operator=(const char* s) { stringToExtendedInt(s); return *this; }
    template<unsigned int u> inline typename extIntReturnSize<t, u>::uIntReturnTypeMax_ operator+(const UnsignedExtendedInt<u>& obj) const { return addOperator(obj); }
    inline friend UnsignedExtendedInt<t> operator+(const UnsignedExtendedInt<t>& lhs, const UnsignedExtendedInt<t>& rhs) { return lhs.addOperator(rhs); }
    template<unsigned int u> inline typename extIntReturnSize<t, u>::uIntReturnTypeMax_ operator-(const UnsignedExtendedInt<u>& obj) const { return subtractOperator(obj); }
    inline friend UnsignedExtendedInt<t> operator-(const UnsignedExtendedInt<t>& lhs, const UnsignedExtendedInt<t>& rhs) { return lhs.subtractOperator(rhs); }
    template<unsigned int u> typename extIntReturnSize<t, u>::uIntReturnTypeTot_ operator*(const UnsignedExtendedInt<u>& obj) const { return multiplyOperator(obj); }
    inline friend typename extIntReturnSize<t, t>::uIntReturnTypeTot_ operator*(const UnsignedExtendedInt<t>& lhs, const UnsignedExtendedInt<t>& rhs) { return lhs.multiplyOperator(rhs); }
    template<unsigned int u> typename extIntReturnSize<t, u>::uIntReturnTypeMax_ operator/(const UnsignedExtendedInt<u>& divisor) const { return divideModOperator(divisor, ExtendedInt<t>::DIVIDE_OP); }
    inline friend typename extIntReturnSize<t, t>::uIntReturnTypeMax_ operator/(const UnsignedExtendedInt<t>& dividend, const UnsignedExtendedInt<t>& divisor) { return dividend.divideModOperator(divisor, ExtendedInt<t>::DIVIDE_OP); }
    template<unsigned int u> typename extIntReturnSize<t, u>::uIntReturnTypeMax_ operator%(const UnsignedExtendedInt<u>& divisor) const { return divideModOperator(divisor, ExtendedInt<t>::MOD_OP); }
    inline friend typename extIntReturnSize<t, t>::uIntReturnTypeMax_ operator%(const UnsignedExtendedInt<t>& dividend, const UnsignedExtendedInt<t>& divisor) { return dividend.divideModOperator(divisor, ExtendedInt<t>::MOD_OP); }
    template<unsigned int u> inline bool operator==(const UnsignedExtendedInt<u>& obj) const { return isEqualOperator(obj); }
    inline friend bool operator==(const UnsignedExtendedInt<t>& lhs, const UnsignedExtendedInt<t>& rhs) { return lhs.isEqualOperator(rhs); }
    template<unsigned int u> inline bool operator>(const UnsignedExtendedInt<u>& obj) const { return greaterThanOperator(obj); }
    inline friend bool operator>(const UnsignedExtendedInt<t>& lhs, const UnsignedExtendedInt<t>& rhs) { return lhs.greaterThanOperator(rhs); }
    template<unsigned int u> inline bool operator>=(const UnsignedExtendedInt<u>& obj) const { return greaterThanOrEqualOperator(obj); }
    inline friend bool operator>=(const UnsignedExtendedInt<t>& lhs, const UnsignedExtendedInt<t>& rhs) { return lhs.greaterThanOrEqualOperator(rhs); }
    template<unsigned int u> inline bool operator<(const UnsignedExtendedInt<u>& obj) const { return lessThanOperator(obj); }
    inline friend bool operator<(const UnsignedExtendedInt<t>& lhs, const UnsignedExtendedInt<t>& rhs) { return lhs.lessThanOperator(rhs); }
    template<unsigned int u> inline bool operator<=(const UnsignedExtendedInt<u>& obj) const { return lessThanOrEqualOperator(obj); }
    inline friend bool operator<=(const UnsignedExtendedInt<t>& lhs, const UnsignedExtendedInt<t>& rhs) { return lhs.lessThanOrEqualOperator(rhs); }
    template<unsigned int u> inline UnsignedExtendedInt<t> operator>>(const UnsignedExtendedInt<u>& obj) const { return rightShiftOperator(obj); }
    inline friend UnsignedExtendedInt<t> operator>>(const UnsignedExtendedInt<t>& lhs, const UnsignedExtendedInt<t>& rhs) { return lhs.rightShiftOperator(rhs); }
    template<unsigned int u> inline UnsignedExtendedInt<t> operator<<(const UnsignedExtendedInt<u>& obj) const { return leftShiftOperator(obj); }
    inline friend UnsignedExtendedInt<t> operator<<(const UnsignedExtendedInt<t>& lhs, const UnsignedExtendedInt<t>& rhs) { return lhs.leftShiftOperator(rhs); }
    template<unsigned int u> inline typename extIntReturnSize<t, u>::uIntReturnTypeMax_ operator&(const UnsignedExtendedInt<u>& obj) const { return andOperator(obj); }
    inline friend UnsignedExtendedInt<t> operator&(const UnsignedExtendedInt<t>& lhs, const UnsignedExtendedInt<t>& rhs) { return lhs.andOperator(rhs); }
    template<unsigned int u> inline typename extIntReturnSize<t, u>::uIntReturnTypeMax_ operator|(const UnsignedExtendedInt<u>& obj) const { return orOperator(obj); }
    inline friend UnsignedExtendedInt<t> operator|(const UnsignedExtendedInt<t>& lhs, const UnsignedExtendedInt<t>& rhs) { return lhs.orOperator(rhs); }
    template<unsigned int u> inline typename extIntReturnSize<t, u>::uIntReturnTypeMax_ operator^(const UnsignedExtendedInt<u>& obj) const { return xorOperator(obj); }
    inline friend UnsignedExtendedInt<t> operator^(const UnsignedExtendedInt<t>& lhs, const UnsignedExtendedInt<t>& rhs) { return lhs.xorOperator(rhs); }
    UnsignedExtendedInt<t> operator~() const;
    friend std::ostream& operator<<(std::ostream& os, const UnsignedExtendedInt<t>& obj) {
        os << obj.extendedIntToString();
        return os;
    }

    friend class UnsignedExtendedInt;       // allows access between private members between UnsignedExtendedInt<n> and UnsignedExtendedInt<m> for some n,m
    template<unsigned int u> friend class SignedExtendedInt;
};


// Create new extended integer
template<unsigned int t>
UnsignedExtendedInt<t>::UnsignedExtendedInt() {
    this->initialize();
}


// Copy constructor
template<unsigned int t>
template<unsigned int u>
UnsignedExtendedInt<t>::UnsignedExtendedInt(const UnsignedExtendedInt<u>& obj) {
    this->initialize();
    unsigned int minArraySize = extIntReturnSize<t, u>::multipleOf32BitsMin_;
    for (unsigned int i = 0; i < minArraySize; i++) {
        this->ext_int[i] = obj.getValueAtIndex(i);
    }
}


template<unsigned int t>
template<unsigned int u>
UnsignedExtendedInt<t>::UnsignedExtendedInt(const SignedExtendedInt<u>& obj) {
    unsigned int minArraySize = extIntReturnSize<t, u>::multipleOf32BitsMin_;
    this->initialize();
    for (unsigned int i = 0; i < minArraySize; i++) {
        this->ext_int[i] = obj.ext_int[i];
    }
}


template<unsigned int t>
UnsignedExtendedInt<t>::UnsignedExtendedInt(unsigned long long obj) {
    this->initialize();
    this->ext_int[0] = obj & 0xFFFFFFFF;
    this->ext_int[1] = (obj >> 32) & 0xFFFFFFFF;
}


template<unsigned int t>
template<unsigned int u>
UnsignedExtendedInt<t> UnsignedExtendedInt<t>::equalOperator(const UnsignedExtendedInt<u>& obj) {
    this->initialize();
    unsigned int minArraySize = extIntReturnSize<t, u>::multipleOf32BitsMin_;
    for (unsigned int i = 0; i < minArraySize; i++) {
        this->ext_int[i] = obj.getValueAtIndex(i);
    }
    return *this;
}


// Construct new extended integer using string input
template<unsigned int t>
void UnsignedExtendedInt<t>::stringToExtendedInt(const char* s) {
    this->initialize();                     // set values to 0
    unsigned int strLength = 0;
    while (s[strLength] != 0) {             // compute string length
        strLength++;
    }
    UnsignedExtendedInt<t> TEN(10);
    UnsignedExtendedInt<t> powersOfTen(1);
    UnsignedExtendedInt<t> readInt;
    for (int i = strLength - 1; i >= 0; i--) {
        readInt.ext_int[0] = s[i] - '0';
        *this = *this + (powersOfTen * readInt);
        powersOfTen = powersOfTen * TEN;
    }
}


template<unsigned int t>
std::string UnsignedExtendedInt<t>::extendedIntToString() const {
    std::string extIntString;
    UnsignedExtendedInt<t> dividend(*this);
    UnsignedExtendedInt<t> remainder;
    const UnsignedExtendedInt<t> TEN(10);
    while (dividend > 0ULL) {
        remainder = dividend % TEN;
        dividend = dividend / TEN;
        extIntString = (char)((remainder.ext_int[0] & 0xFF) + 48) + extIntString;
    }
    return extIntString;
}


template<unsigned int t>
template<unsigned int u>
typename extIntReturnSize<t, u>::uIntReturnTypeMax_ UnsignedExtendedInt<t>::addOperator(const UnsignedExtendedInt<u>& obj) const {
    extIntReturnSize<t, u>::uIntReturnTypeMax_ thisOfMaxSize(*this);
    extIntReturnSize<t, u>::uIntReturnTypeMax_ objOfMaxSize(obj);
    extIntReturnSize<t, u>::uIntReturnTypeMax_ returnValue;
    unsigned long long x = 0;
    unsigned long long y = 0;
    unsigned long long z = 0;
    unsigned int carryBit = 0;
    unsigned int arraySize = extIntReturnSize<t, u>::multipleOf32BitsMax_;
    for (unsigned int i = 0; i < arraySize; i++) {
        x = thisOfMaxSize.ext_int[i];
        y = objOfMaxSize.ext_int[i];
        z = x + y + carryBit;
        returnValue.ext_int[i] = z & 0xFFFFFFFF;
        carryBit = (z & 0x100000000) >> 32;
    }
    return returnValue;
}


template<unsigned int t>
template<unsigned int u>
typename extIntReturnSize<t, u>::uIntReturnTypeMax_  UnsignedExtendedInt<t>::subtractOperator(const UnsignedExtendedInt<u>& obj) const {
    return this->operator+(~obj + 1);
}


template<unsigned int t>
template<unsigned int u>
typename extIntReturnSize<t, u>::uIntReturnTypeTot_ UnsignedExtendedInt<t>::multiplyOperator(const UnsignedExtendedInt<u>& obj) const {
    // This algorithm multiplies 32bit integers using native 64bit integers.
    unsigned long long x = 0;
    unsigned long long y = 0;
    unsigned long long z = 0;
    unsigned int upperResultBits = 0;
    unsigned int lowerResultBits = 0;
    unsigned int leftShiftValue = 0;
    extIntReturnSize<t, u>::uIntReturnTypeTot_ returnValue;
    extIntReturnSize<t, u>::uIntReturnTypeTot_ uExtIntTemp;
    for (unsigned int i = 0; i < this->ARRAY_SIZE; i++) {
        for (unsigned int j = 0; j < obj.ARRAY_SIZE; j++) {
            leftShiftValue = i + j;
            x = this->ext_int[i];
            y = obj.ext_int[j];
            z = x * y;
            if (leftShiftValue > 0) {           // clear previously set lower 32-bits because they will introduce an error in the summation
                uExtIntTemp.ext_int[leftShiftValue - 1] = 0;
            }
            uExtIntTemp.ext_int[leftShiftValue] = z & 0xFFFFFFFF;                   // Extract lower 32-bits
            if (leftShiftValue < uExtIntTemp.ARRAY_SIZE - 1) {                      // Make sure we won't be writing past the last array entry
                uExtIntTemp.ext_int[leftShiftValue + 1] = (z >> 32) & 0xFFFFFFFF;   // Extract upper 32-bits
            }
            returnValue = returnValue + uExtIntTemp;
        }
    }
    return returnValue;
}


template<unsigned int t>
template<unsigned int u>
typename extIntReturnSize<t, u>::uIntReturnTypeMax_ UnsignedExtendedInt<t>::divideModOperator(const UnsignedExtendedInt<u>& divisor, const ExtendedInt<t>::DIVIDE_OPERATION op) const {
    unsigned long long x = 0;
    unsigned long long y = 0;
    extIntReturnSize<t, u>::uIntReturnTypeMax_ returnValue;
    extIntReturnSize<t, u>::uIntReturnTypeMax_ tempDividend;
    extIntReturnSize<t, u>::uIntReturnTypeMax_ maskBit;
    maskBit.setValueAtIndex(1, 0);
    if (*this < divisor) {              // if dividend is smaller than divisor (e.g. 10 / 20 = 0)
        if (op == ExtendedInt<t>::DIVIDE_OP) {
            return returnValue;
        }
        else if (op == ExtendedInt<t>::MOD_OP) {
            return *this;
        }
    }
    int i = 32 * this->ARRAY_SIZE;
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
        tempDividend = tempDividend - divisor;                    // remainder
    }

    if (op == ExtendedInt<t>::DIVIDE_OP) return returnValue;      // quotient
    else return tempDividend;                                     // mod operation returns remainder
}


template<unsigned int t>
template<unsigned int u>
bool UnsignedExtendedInt<t>::isEqualOperator(const UnsignedExtendedInt<u>& obj) const {
    if (this->ARRAY_SIZE > obj.ARRAY_SIZE) {        // if calling object has upper bits not 0, then can't be equal
        for (unsigned int i = obj.ARRAY_SIZE; i < this->ARRAY_SIZE; i++) {
            if (this->ext_int[i] != 0) {
                return false;
            }
        }
    }
    if (obj.ARRAY_SIZE > this->ARRAY_SIZE) {        // if object being compared to has its upper bits not 0, then can't be qual
        for (unsigned int i = this->ARRAY_SIZE; i < obj.ARRAY_SIZE; i++) {
            if (obj.ext_int[i] != 0) {
                return false;
            }
        }
    }
    unsigned int minSize = this->ARRAY_SIZE > obj.ARRAY_SIZE ? obj.ARRAY_SIZE : this->ARRAY_SIZE;
    for (int i = minSize - 1; i >= 0; i--) {
        if (this->ext_int[i] != obj.ext_int[i]) {
            return false;
        }
    }
    return true;
}


template<unsigned int t>
template<unsigned int u>
bool UnsignedExtendedInt<t>::greaterThanOperator(const UnsignedExtendedInt<u>& obj) const {
    if (obj.ARRAY_SIZE > this->ARRAY_SIZE) {        // if object being compared to has its upper bits not 0, then it's bigger
        for (unsigned int i = this->ARRAY_SIZE; i < obj.ARRAY_SIZE; i++) {
            if (obj.ext_int[i] != 0) {
                return false;
            }
        }
    }
    else if (this->ARRAY_SIZE > obj.ARRAY_SIZE) {   // if calling object's upper bits are not 0, then it's greater than
        for (unsigned int i = obj.ARRAY_SIZE; i < this->ARRAY_SIZE; i++) {
            if (this->ext_int[i] != 0) {
                return true;
            }
        }
    }
    unsigned int minSize = this->ARRAY_SIZE > obj.ARRAY_SIZE ? obj.ARRAY_SIZE : this->ARRAY_SIZE;
    for (int i = minSize - 1; i >= 0; i--) {
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


template<unsigned int t>
template<unsigned int u>
bool UnsignedExtendedInt<t>::greaterThanOrEqualOperator(const UnsignedExtendedInt<u>& obj) const {
    if (this->ARRAY_SIZE > obj.ARRAY_SIZE) {    // if calling object's upper bits are not 0, then it's greater than
        for (unsigned int i = obj.ARRAY_SIZE; i < this->ARRAY_SIZE; i++) {
            if (this->ext_int[i] != 0) {
                return true;
            }
        }
    }
    if (obj.ARRAY_SIZE > this->ARRAY_SIZE) {    // if object being compared to has its upper bits not 0, then it's bigger
        for (unsigned int i = this->ARRAY_SIZE; i < obj.ARRAY_SIZE; i++) {
            if (this->ext_int[i] != 0) {
                return false;
            }
        }
    }
    unsigned int minSize = this->ARRAY_SIZE > obj.ARRAY_SIZE ? obj.ARRAY_SIZE : this->ARRAY_SIZE;
    for (int i = minSize - 1; i >= 0; i--) {
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


template<unsigned int t>
template<unsigned int u>
bool UnsignedExtendedInt<t>::lessThanOperator(const UnsignedExtendedInt<u>& obj) const {
    if (this->ARRAY_SIZE > obj.ARRAY_SIZE) {        // if calling object's upper bits are not 0, then it's greater
        for (unsigned int i = obj.ARRAY_SIZE; i < this->ARRAY_SIZE; i++) {
            if (this->ext_int[i] != 0)
                return false;
        }
    }
    else if (obj.ARRAY_SIZE > this->ARRAY_SIZE) {   // if object being compared to has its upper bits not 0, then it's less than
        for (unsigned int i = this->ARRAY_SIZE; i < obj.ARRAY_SIZE; i++) {
            if (obj.ext_int[i] != 0)
                return true;
        }
    }
    unsigned int minSize = this->ARRAY_SIZE > obj.ARRAY_SIZE ? obj.ARRAY_SIZE : this->ARRAY_SIZE;
    for (int i = minSize - 1; i >= 0; i--) {
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


template<unsigned int t>
template<unsigned int u>
bool UnsignedExtendedInt<t>::lessThanOrEqualOperator(const UnsignedExtendedInt<u>& obj) const {
    if (this->ARRAY_SIZE > obj.ARRAY_SIZE) {        // if calling object's upper bits are not 0, then it's greater
        for (unsigned int i = obj.ARRAY_SIZE; i < this->ARRAY_SIZE; i++) {
            if (this->ext_int[i] != 0)
                return false;
        }
    }
    else if (obj.ARRAY_SIZE > this->ARRAY_SIZE) {   // if object being compared to has its upper bits not 0, then it's less than
        for (unsigned int i = this->ARRAY_SIZE; i < obj.ARRAY_SIZE; i++) {
            if (obj.ext_int[i] != 0)
                return true;
        }
    }
    unsigned int minSize = this->ARRAY_SIZE > obj.ARRAY_SIZE ? obj.ARRAY_SIZE : this->ARRAY_SIZE;
    for (int i = minSize - 1; i >= 0; i--) {
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


template<unsigned int t>
template<unsigned int u>
UnsignedExtendedInt<t> UnsignedExtendedInt<t>::rightShiftOperator(const UnsignedExtendedInt<u>& obj) const {
    unsigned long long shiftVal = obj.ext_int[0];               // extract 64 bits since that limits shift to 2^64
    unsigned long long x = 0;
    unsigned long long y = 0;
    UnsignedExtendedInt<t> returnValue(*this);
    shiftVal = (shiftVal > t * 32 ? t * 32 : shiftVal);         // bound maximum shift
    while (shiftVal > 0) {
        for (unsigned int i = 0; i < this->ARRAY_SIZE; i++) {
            x = returnValue.ext_int[i];
            x = x << 32;
            x = x >> (shiftVal > 32 ? 32 : shiftVal);                   // perform shift
            returnValue.ext_int[i] = (x & 0xFFFFFFFF00000000) >> 32;    // upper 32 bits should be stored
            if (i > 0) {
                y = returnValue.ext_int[i - 1];
                returnValue.ext_int[i - 1] = (unsigned int)((x & 0xFFFFFFFF) | y);      // lower 32 bits ORd with previous entry since these bits were shifted into the the adjacent 32-bits
            }
        }
        shiftVal = (shiftVal >= 32 ? shiftVal - 32 : 0);
    }
    return returnValue;
}


template<unsigned int t>
template<unsigned int u>
UnsignedExtendedInt<t> UnsignedExtendedInt<t>::leftShiftOperator(const UnsignedExtendedInt<u>& obj) const {
    unsigned long long shiftVal = obj.ext_int[0];               // extract 64 bits since that limits shift to 2^32
    unsigned long long x = 0;
    unsigned long long y = 0;
    UnsignedExtendedInt<t> returnValue(*this);
    shiftVal = (shiftVal > t * 32 ? t * 32 : shiftVal);         // bound maximum shift
    while (shiftVal > 0) {
        for (int i = this->ARRAY_SIZE - 1; i >= 0; i--) {
            x = returnValue.ext_int[i];
            x = x << (shiftVal > 32 ? 32 : shiftVal);           // perform shift
            returnValue.ext_int[i] = x & 0xFFFFFFFF;            // lower 32 bits should be stored
            if (i < (int)this->ARRAY_SIZE - 1) {
                y = returnValue.ext_int[i + 1];
                returnValue.ext_int[i + 1] = (unsigned int)((x & 0xFFFFFFFF00000000) >> 32 | y);    // lower 32 bits ORd with previous entry since these bits were shifted into the the adjacent 32-bits
            }
        }
        shiftVal = (shiftVal >= 32 ? shiftVal - 32 : 0);
    }
    return returnValue;
}


template<unsigned int t>
template<unsigned int u>
typename extIntReturnSize<t, u>::uIntReturnTypeMax_ UnsignedExtendedInt<t>::andOperator(const UnsignedExtendedInt<u>& obj) const {
    typename extIntReturnSize<t, u>::uIntReturnTypeMax_ returnValue;
    unsigned int minArraySize = extIntReturnSize<t, u>::multipleOf32BitsMin_;
    for (unsigned int i = 0; i < minArraySize; i++) {
        returnValue.ext_int[i] = this->ext_int[i] & obj.ext_int[i];
    }
    return returnValue;
}


template<unsigned int t>
template<unsigned int u>
typename extIntReturnSize<t, u>::uIntReturnTypeMax_ UnsignedExtendedInt<t>::orOperator(const UnsignedExtendedInt<u>& obj) const {
    typename extIntReturnSize<t, u>::uIntReturnTypeMax_ returnValue;
    unsigned int minArraySize = extIntReturnSize<t, u>::multipleOf32BitsMin_;
    for (unsigned int i = 0; i < minArraySize; i++) {
        returnValue.ext_int[i] = this->ext_int[i] | obj.ext_int[i];
    }
    return returnValue;
}


template<unsigned int t>
template<unsigned int u>
typename extIntReturnSize<t, u>::uIntReturnTypeMax_ UnsignedExtendedInt<t>::xorOperator(const UnsignedExtendedInt<u>& obj) const {
    typename extIntReturnSize<t, u>::uIntReturnTypeMax_ returnValue;
    unsigned int minArraySize = extIntReturnSize<t, u>::multipleOf32BitsMin_;
    for (unsigned int i = 0; i < minArraySize; i++) {
        returnValue.ext_int[i] = this->ext_int[i] ^ obj.ext_int[i];
    }
    return returnValue;
}


template<unsigned int t>
UnsignedExtendedInt<t> UnsignedExtendedInt<t>::operator~() const {
    UnsignedExtendedInt<t> returnValue;
    for (unsigned int i = 0; i < this->ARRAY_SIZE; i++) {
        returnValue.ext_int[i] = ~(this->ext_int[i]);
    }
    return returnValue;
}


#endif
