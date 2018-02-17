#ifndef _EXTENDEDINT_H_
#define _EXTENDEDINT_H_

#include "ExtendedIntLengths.h"

template<typename T>
class ExtendedInt {
protected:
    enum DIVIDE_OPERATION { DIVIDE_OP, MOD_OP };
    unsigned int ARRAY_SIZE;
    unsigned int ext_int[T::_multipleOf32Bits];
    virtual void initialize();
    virtual void stringToExtendedInt(const char* s) = 0;
    virtual char* extendedIntToString() const = 0;
public:
    virtual void setValueAtIndex(const unsigned long long val, const unsigned int index);
    virtual unsigned long long getValueAtIndex(const unsigned int index) const;  
};

template<typename T>
void ExtendedInt<T>::initialize() {
    this->ARRAY_SIZE = T::_multipleOf32Bits;
    for (unsigned int i = 0; i < this->ARRAY_SIZE; i++) {
        this->ext_int[i] = 0;
    }
}


template<typename T>
void ExtendedInt<T>::setValueAtIndex(const unsigned long long val, const unsigned int index) {
    if ((index < this->ARRAY_SIZE) && (index >= 0)) {
        this->ext_int[index] = val & 0xFFFFFFFF;
    }
}


template<typename T>
unsigned long long ExtendedInt<T>::getValueAtIndex(const unsigned int index) const {
    if ((this->ARRAY_SIZE > 0) && (index < this->ARRAY_SIZE) && (index >= 0)) {
        return this->ext_int[index];
    }
    return 0;
}



#endif