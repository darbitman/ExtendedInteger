

template<unsigned int t>
SignedExtendedInt<t>::SignedExtendedInt() {
    this->initialize();
}


template<unsigned int t>
template<unsigned int u>
SignedExtendedInt<t>::SignedExtendedInt(const SignedExtendedInt<u>& obj) {
    this->initialize();
    unsigned int minArraySize = extIntReturnSize<t, u>::multipleOf32BitsMin_;
    for (unsigned int i = 0; i < minArraySize; i++) {
        this->ext_int[i] = obj.getValueAtIndex(i);
    }
}


template<unsigned int t>
SignedExtendedInt<t>::SignedExtendedInt(long long obj) {
    this->initialize();
    this->ext_int[0] = obj & 0xFFFFFFFF;
    this->ext_int[1] = (obj >> 32) & 0xFFFFFFFF;
    if (obj < 0) {
        for (unsigned int i = 2; i < this->ARRAY_SIZE; i++) {
            this->ext_int[i] = 0xFFFFFFFF;
        }
    }
}


template<unsigned int t>
template<unsigned int u>
SignedExtendedInt<t>& SignedExtendedInt<t>::equalOperator(const SignedExtendedInt<u>& obj) {
    this->initialize();
    for (unsigned int i = 0; i < minArraySize; i++) {
        this->ext_int[i] = obj.getValueAtIndex(i);
    }
    return *this;
}


template<unsigned int t>
template<unsigned int u>
bool SignedExtendedInt<t>::isEqualOperator(const SignedExtendedInt<u>& obj) const {
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
bool SignedExtendedInt<t>::greaterThanOperator(const SignedExtendedInt<u>& obj) const {
    extIntReturnSize<t, u>::intReturnTypeMax_ thisOfMaxSize(*this);
    extIntReturnSize<t, u>::intReturnTypeMax_ objOfMaxSize(obj);
    extIntReturnSize<t, u>::intReturnTypeMax_ returnValue;
    unsigned long long sign1 = (thisOfMaxSize.ext_int[thisOfMaxSize.ARRAY_SIZE - 1] >> 31) & 0x1;   // Extract sign bit of calling obj
    unsigned long long sign2 = (objOfMaxSize.ext_int[objOfMaxSize.ARRAY_SIZE - 1] >> 31) & 0x1;     // Extract sign bit of rhs obj
    if (sign1 && !sign2) {
        return false;
    }
    else if (sign2 && !sign1) {
        return true;
    }
    else {
        for (int i = thisOfMaxSize.ARRAY_SIZE - 1; i >= 0; i--) {
            if (thisOfMaxSize.ext_int[i] > objOfMaxSize.ext_int[i]) {
                return true;
            }
            else if (thisOfMaxSize.ext_int[i] == objOfMaxSize.ext_int[i]) {
                continue;
            }
            else {
                return false;
            }
        }
        return false;
    }
}


template<unsigned int t>
template<unsigned int u>
bool SignedExtendedInt<t>::greaterThanOrEqualOperator(const SignedExtendedInt<u>& obj) const {
    extIntReturnSize<t, u>::intReturnTypeMax_ thisOfMaxSize(*this);
    extIntReturnSize<t, u>::intReturnTypeMax_ objOfMaxSize(obj);
    extIntReturnSize<t, u>::intReturnTypeMax_ returnValue;
    unsigned long long sign1 = (thisOfMaxSize.ext_int[thisOfMaxSize.ARRAY_SIZE - 1] >> 31) & 0x1;   // Extract sign bit of calling obj
    unsigned long long sign2 = (objOfMaxSize.ext_int[objOfMaxSize.ARRAY_SIZE - 1] >> 31) & 0x1;     // Extract sign bit of rhs obj
    if (sign1 && !sign2) {
        return false;
    }
    else if (sign2 && !sign1) {
        return true;
    }
    else {
        for (int i = thisOfMaxSize.ARRAY_SIZE - 1; i >= 0; i--) {
            if (thisOfMaxSize.ext_int[i] > objOfMaxSize.ext_int[i]) {
                return true;
            }
            else if (thisOfMaxSize.ext_int[i] == objOfMaxSize.ext_int[i]) {
                continue;
            }
            else {
                return false;
            }
        }
        return true;
    }
}


template<unsigned int t>
template<unsigned int u>
bool SignedExtendedInt<t>::lessThanOperator(const SignedExtendedInt<u>& obj) const {
    extIntReturnSize<t, u>::intReturnTypeMax_ thisOfMaxSize(*this);
    extIntReturnSize<t, u>::intReturnTypeMax_ objOfMaxSize(obj);
    extIntReturnSize<t, u>::intReturnTypeMax_ returnValue;
    unsigned long long sign1 = (thisOfMaxSize.ext_int[thisOfMaxSize.ARRAY_SIZE - 1] >> 31) & 0x1;   // Extract sign bit of calling obj
    unsigned long long sign2 = (objOfMaxSize.ext_int[objOfMaxSize.ARRAY_SIZE - 1] >> 31) & 0x1;     // Extract sign bit of rhs obj
    if (sign1 && !sign2) {
        return true;
    }
    else if (sign2 && !sign1) {
        return false;
    }
    else {
        for (int i = thisOfMaxSize.ARRAY_SIZE - 1; i >= 0; i--) {
            if (thisOfMaxSize.ext_int[i] < objOfMaxSize.ext_int[i]) {
                return true;
            }
            else if (thisOfMaxSize.ext_int[i] == objOfMaxSize.ext_int[i]) {
                continue;
            }
            else {
                return false;
            }
        }
        return false;
    }
}


template<unsigned int t>
template<unsigned int u>
bool SignedExtendedInt<t>::lessThanOrEqualOperator(const SignedExtendedInt<u>& obj) const {
    extIntReturnSize<t, u>::intReturnTypeMax_ thisOfMaxSize(*this);
    extIntReturnSize<t, u>::intReturnTypeMax_ objOfMaxSize(obj);
    extIntReturnSize<t, u>::intReturnTypeMax_ returnValue;
    unsigned long long sign1 = (thisOfMaxSize.ext_int[thisOfMaxSize.ARRAY_SIZE - 1] >> 31) & 0x1;   // Extract sign bit of calling obj
    unsigned long long sign2 = (objOfMaxSize.ext_int[objOfMaxSize.ARRAY_SIZE - 1] >> 31) & 0x1;     // Extract sign bit of rhs obj
    if (sign1 && !sign2) {
        return true;
    }
    else if (sign2 && !sign1) {
        return false;
    }
    else {
        for (int i = thisOfMaxSize.ARRAY_SIZE - 1; i >= 0; i--) {
            if (thisOfMaxSize.ext_int[i] < objOfMaxSize.ext_int[i]) {
                return true;
            }
            else if (thisOfMaxSize.ext_int[i] == objOfMaxSize.ext_int[i]) {
                continue;
            }
            else {
                return false;
            }
        }
        return true;
    }
}


template<unsigned int t>
template<unsigned int u>
typename extIntReturnSize<t, u>::intReturnTypeMax_ SignedExtendedInt<t>::addOperator(const SignedExtendedInt<u>& obj) const {
    extIntReturnSize<t, u>::intReturnTypeMax_ thisOfMaxSize(*this);
    extIntReturnSize<t, u>::intReturnTypeMax_ objOfMaxSize(obj);
    extIntReturnSize<t, u>::intReturnTypeMax_ returnValue;
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
typename extIntReturnSize<t, u>::intReturnTypeMax_ SignedExtendedInt<t>::subtractOperator(const SignedExtendedInt<u>& obj) const {
    extIntReturnSize<t, u>::intReturnTypeMax_ thisOfMaxSize(*this);
    extIntReturnSize<t, u>::intReturnTypeMax_ objOfMaxSize(~obj + 1);
    extIntReturnSize<t, u>::intReturnTypeMax_ returnValue;
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
SignedExtendedInt<t> SignedExtendedInt<t>::rightShiftOperator(const SignedExtendedInt<u>& obj) const {
    unsigned long long shiftVal = obj.ext_int[0];               // extract 64 bits since that limits shift to 2^64
    unsigned long long x = 0;
    unsigned long long y = 0;
    SignedExtendedInt<t> returnValue(*this);
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
SignedExtendedInt<t> SignedExtendedInt<t>::leftShiftOperator(const SignedExtendedInt<u>& obj) const {
    unsigned long long shiftVal = obj.ext_int[0];               // extract 64 bits since that limits shift to 2^32
    unsigned long long x = 0;
    unsigned long long y = 0;
    SignedExtendedInt<t> returnValue(*this);
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
typename extIntReturnSize<t, u>::intReturnTypeMax_ SignedExtendedInt<t>::andOperator(const SignedExtendedInt<u>& obj) const {
    typename extIntReturnSize<t, u>::intReturnTypeMax_ returnValue;
    unsigned int minArraySize = extIntReturnSize<t, u>::multipleOf32BitsMin_;
    for (unsigned int i = 0; i < minArraySize; i++) {
        returnValue.ext_int[i] = this->ext_int[i] & obj.ext_int[i];
    }
    return returnValue;
}


template<unsigned int t>
template<unsigned int u>
typename extIntReturnSize<t, u>::intReturnTypeMax_ SignedExtendedInt<t>::orOperator(const SignedExtendedInt<u>& obj) const {
    typename extIntReturnSize<t, u>::intReturnTypeMax_ returnValue;
    unsigned int minArraySize = extIntReturnSize<t, u>::multipleOf32BitsMin_;
    for (unsigned int i = 0; i < minArraySize; i++) {
        returnValue.ext_int[i] = this->ext_int[i] | obj.ext_int[i];
    }
    return returnValue;
}


template<unsigned int t>
template<unsigned int u>
typename extIntReturnSize<t, u>::intReturnTypeMax_ SignedExtendedInt<t>::xorOperator(const SignedExtendedInt<u>& obj) const {
    typename extIntReturnSize<t, u>::intReturnTypeMax_ returnValue;
    unsigned int minArraySize = extIntReturnSize<t, u>::multipleOf32BitsMin_;
    for (unsigned int i = 0; i < minArraySize; i++) {
        returnValue.ext_int[i] = this->ext_int[i] ^ obj.ext_int[i];
    }
    return returnValue;
}


template<unsigned int t>
SignedExtendedInt<t> SignedExtendedInt<t>::operator~() const {
    SignedExtendedInt<t> returnValue;
    for (unsigned int i = 0; i < this->ARRAY_SIZE; i++) {
        returnValue.ext_int[i] = ~(this->ext_int[i]);
    }
    return returnValue;
}



//template<typename T>
//void SignedExtendedInt<T>::stringToExtendedInt(const char* s) {
//    unsigned int signBit = 0;
//    unsigned int strLength = 0;
//    while (s[strLength] != 0) {
//        strLength++;
//    }
//    SignedExtendedInt<T> TEN;
//    SignedExtendedInt<T> powersOfTen;
//    powersOfTen.setValueAtIndex(1, 0);
//    TEN.setValueAtIndex(10, 0);
//    SignedExtendedInt<T> readInt;
//    for (int i = strLength - 1; i >= 0; i--) {
//        if (i == strLength - 1 && s[i] == '-') {
//            signBit = 1;
//            continue;
//        }
//        readInt.ext_int[0] = s[i] - '0';
//        *this = *this + (powersOfTen * readInt);
//        powersOfTen = powersOfTen * TEN;
//    }
//
//}
//
//
//template<typename T>
//std::string SignedExtendedInt<T>::extendedIntToString() const {
//    bool isNegative = false;
//    std::string extIntString;
//    SignedExtendedInt<T> unsignedObj;
//    if (*this < 0ULL) {
//        isNegative = true;
//        unsignedObj = ~(*this) + 1;
//    }
//    else {
//        unsignedObj = *this;
//    }
//    SignedExtendedInt<T> dividend(*this);
//    SignedExtendedInt<T> remainder;
//    const SignedExtendedInt<T> TEN(10);
//    while (dividend > 0ULL) {
//        remainder = dividend % TEN;
//        dividend = dividend / TEN;
//        extIntString = (char)((remainder.ext_int[0] & 0xFF) + 48) + extIntString;
//    }
//    if (isNegative) {
//        extIntString = '-' + extIntString;
//    }
//    return extIntString;
//}
//
//
//template<typename T>
//SignedExtendedInt<T>::SignedExtendedInt(const char* s) {
//    if (this->ARRAY_SIZE == 0)
//        this->initialize();
//    this->stringToExtendedInt(s);
//}


//
//
//template<typename T>
//const SignedExtendedInt<T> SignedExtendedInt<T>::operator*(const SignedExtendedInt<T>& obj) const {
//    // This algorithm multiplies 32bit integers using native 64bit integers.
//    unsigned long long sign1 = (this->ext_int[this->ARRAY_SIZE - 1] >> 31) & 0x1;       // Extract sign bit of calling obj
//    unsigned long long sign2 = (obj.ext_int[obj.ARRAY_SIZE - 1] >> 31) & 0x1;           // Extract sign bit
//    SignedExtendedInt<T> unsignedThis(sign1 ? ((~(*this)) + 1) : (*this));              // if calling obj is negative, return positive value
//    SignedExtendedInt<T> unsignedObj(sign2 ? ((~obj) + 1) : obj);                       // if multiplier is negative, return positive value
//    unsigned long long x = 0;
//    unsigned long long y = 0;
//    unsigned long long z = 0;
//    unsigned int upperResultBits = 0;
//    unsigned int lowerResultBits = 0;
//    unsigned int leftShiftValue = 0;
//    SignedExtendedInt<T> returnValue;
//    SignedExtendedInt<T> extIntTemp;
//    for (unsigned int i = 0; i < unsignedThis.ARRAY_SIZE; i++) {
//        for (unsigned int j = 0; j < unsignedObj.ARRAY_SIZE; j++) {
//            leftShiftValue = i + j;
//            x = unsignedThis.ext_int[i];
//            y = unsignedObj.ext_int[j];
//            z = x * y;
//
//            if (leftShiftValue < unsignedThis.ARRAY_SIZE) {
//                if (leftShiftValue > 0) {       // clear previous 32-bits because they will introduce an error in the summation
//                    extIntTemp.ext_int[leftShiftValue - 1] = 0;
//                }
//                lowerResultBits = z & 0xFFFFFFFF;
//                extIntTemp.ext_int[leftShiftValue] = lowerResultBits;               // Extract first 32-bits
//            }
//            if (leftShiftValue < unsignedThis.ARRAY_SIZE - 1) {
//                upperResultBits = (z >> 32) & 0xFFFFFFFF;
//                extIntTemp.ext_int[leftShiftValue + 1] = upperResultBits;           // Extract upper 32-bits
//            }
//            returnValue = returnValue + extIntTemp;
//        }
//    }
//    if (sign1 ^ sign2) {            // result is negative if one of the ext_ints is negative, otherwise positive (XOR function)
//        returnValue = (~returnValue) + 1;
//    }
//    return returnValue;
//}
//
//
//template<typename T>
//const SignedExtendedInt<T> SignedExtendedInt<T>::operator*(const long long& obj) const {
//    unsigned long long sign1 = (this->ext_int[this->ARRAY_SIZE - 1] >> 31) & 0x1;       // Extract sign bit of calling obj
//    unsigned long long sign2 = (obj >> 63) & 0x1;                                       // Extract sign bit
//    SignedExtendedInt<T> unsignedThis(sign1 ? ((~(*this)) + 1) : (*this));              // if calling obj is negative, return positive value
//    unsigned long long unsignedObj = sign2 ? ((~obj) + 1) : obj;                        // if multiplier is negative, return positive value
//    unsigned long long x = 0;
//    unsigned long long y = 0;
//    unsigned long long z = 0;
//    unsigned int upperResultBits = 0;
//    unsigned int lowerResultBits = 0;
//    unsigned int leftShiftValue = 0;
//    SignedExtendedInt<T> returnValue;
//    SignedExtendedInt<T> extIntTemp;
//    for (unsigned int i = 0; i < unsignedThis.ARRAY_SIZE; i++) {
//        for (unsigned int j = 0; j < 2; j++) {
//            leftShiftValue = i + j;
//            x = unsignedThis.ext_int[i];
//            y = (unsignedObj >> (j * 32)) & 0xFFFFFFFF;
//            z = x * y;
//
//            if (leftShiftValue < unsignedThis.ARRAY_SIZE) {
//                if (leftShiftValue > 0) {   // clear previous 32-bits because they will introduce an error in the summation
//                    extIntTemp.ext_int[leftShiftValue - 1] = 0;
//                }
//                lowerResultBits = z & 0xFFFFFFFF;
//                extIntTemp.ext_int[leftShiftValue] = lowerResultBits;   // Extract first 32-bits
//            }
//            if (leftShiftValue < unsignedThis.ARRAY_SIZE - 1) {
//                upperResultBits = (z >> 32) & 0xFFFFFFFF;
//                extIntTemp.ext_int[leftShiftValue + 1];                 // Extract upper 32-bits
//            }
//            returnValue = returnValue + extIntTemp;
//        }
//    }
//    if (sign1 ^ sign2) {            // result is negative if 1 or the other ext int is negative, otherwise positive (XOR function)
//        returnValue = (~returnValue) + 1;
//    }
//    return returnValue;
//}
//
//
//template<typename T>
//const SignedExtendedInt<T> SignedExtendedInt<T>::operator/(const SignedExtendedInt<T>& divisor) const {
//    return divideModOperator(divisor, ExtendedInt<T>::DIVIDE_OP);
//}
//
//
//template<typename T>
//const SignedExtendedInt<T> SignedExtendedInt<T>::operator%(const SignedExtendedInt<T>& divisor) const {
//    return divideModOperator(divisor, ExtendedInt<T>::MOD_OP);
//}
//
//
//template<typename T>
//const SignedExtendedInt<T> SignedExtendedInt<T>::divideModOperator(const SignedExtendedInt<T>& divisor, const ExtendedInt<T>::DIVIDE_OPERATION op) const {
//    unsigned long long sign1 = (this->ext_int[this->ARRAY_SIZE - 1] >> 31) & 0x1;       // Extract sign bit of calling obj
//    unsigned long long sign2 = (divisor.ext_int[divisor.ARRAY_SIZE - 1] >> 31) & 0x1;   // Extract sign bit of divisor
//    SignedExtendedInt<T> unsignedThis(sign1 ? ((~(*this)) + 1) : (*this));              // if calling obj is negative, return positive value
//    SignedExtendedInt<T> unsignedDivisor(sign2 ? ((~divisor) + 1) : divisor);           // if multiplier is negative, return positive value
//    unsigned long long x = 0;
//    unsigned long long y = 0;
//    SignedExtendedInt<T> returnValue;
//    SignedExtendedInt<T> tempDividend;
//    SignedExtendedInt<T> maskBit;
//    maskBit.ext_int[0] = 1;
//    if (unsignedThis < unsignedDivisor) {
//        if (op == unsignedThis.DIVIDE_OP) {         // if division
//            return returnValue;
//        }
//        else {                                      // otherwise mod
//            if (sign1) {                            // result is negative if dividend is negative
//                return *this;                       // dividend is remainder in this case
//            }
//            return unsignedThis;
//        }
//    }
//
//    int i = unsignedThis.ARRAY_SIZE;
//    maskBit = maskBit << (i - 1);
//    while (--i >= 0) {
//        if (unsignedDivisor > tempDividend) {
//            // Extract bit i
//            tempDividend = (((unsignedThis & maskBit) >> i) | (tempDividend << 1));
//            maskBit = maskBit >> 1;
//        }
//        else {
//            returnValue = returnValue | (maskBit << 1);
//            tempDividend = tempDividend - divisor;
//            i++;
//        }
//    }
//
//    // Extract bit 0 of the quotient
//    if (unsignedDivisor <= tempDividend) {
//        maskBit.ext_int[0] = 1;
//        returnValue = returnValue | maskBit;
//        tempDividend = tempDividend - divisor;   // remainder
//    }
//
//    if (op == unsignedThis.DIVIDE_OP) {         // if division
//        if (sign1 ^ sign2) {                    // result is negative if one of the ext_ints is negative, otherwise positive (XOR function)
//            returnValue = (~returnValue) + 1;   // quotient
//        }
//        return returnValue;
//    }
//    else {                                      // otherwise mod
//        if (sign1) {                            // result is negative if dividend is negative
//            tempDividend = (~tempDividend) + 1; // remainder
//        }
//        return tempDividend;
//    }
//}


//template<typename T>
//bool SignedExtendedInt<T>::operator<=(const SignedExtendedInt<T>& obj) const {
//    unsigned long long sign1 = (this->ext_int[this->ARRAY_SIZE - 1] >> 31) & 0x1;   // Extract sign bit of calling obj
//    unsigned long long sign2 = (obj.ext_int[obj.ARRAY_SIZE - 1] >> 31) & 0x1;       // Extract sign bit of rhs obj
//    if (sign1 && !sign2) {
//        return true;
//    }
//    else if (sign2 && !sign1) {
//        return false;
//    }
//    else {
//        for (int i = this->ARRAY_SIZE - 1; i >= 0; i--) {
//            if (this->ext_int[i] < obj.ext_int[i]) {
//                return true;
//            }
//            else if (this->ext_int[i] == obj.ext_int[i]) {
//                continue;
//            }
//            else {
//                return false;
//            }
//        }
//        return true;
//    }
//}
