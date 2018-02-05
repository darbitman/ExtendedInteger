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
SignedExtendedInt<T>::SignedExtendedInt(const SignedExtendedInt& obj) {
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
const SignedExtendedInt<T>& SignedExtendedInt<T>::operator=(const SignedExtendedInt& obj) {
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
const SignedExtendedInt<T>& SignedExtendedInt<T>::operator+(const SignedExtendedInt& obj) {
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
    SignedExtendedInt<T>* returnValue = new SignedExtendedInt<T>();
    return *returnValue;
}