#ifndef _UNSIGNEDEXTENDEDINT_H_
#define _UNSIGNEDEXTENDEDINT_H_


#include "ExtendedInt.h"


template<unsigned int t = 4>
class UnsignedExtendedInt : public ExtendedInt<t> {
protected:
    //virtual void stringToExtendedInt(const char* s);
    //virtual std::string extendedIntToString() const;
    template<unsigned int u> typename extIntReturnSize<t, u>::returnTypeMax_ divideModOperator(const UnsignedExtendedInt<u>& divisor, const ExtendedInt<t>::DIVIDE_OPERATION op) const;
    template<unsigned int u> typename extIntReturnSize<t, u>::returnTypeMax_ addOperator(const UnsignedExtendedInt<u>& obj) const;
    template<unsigned int u> typename extIntReturnSize<t, u>::returnTypeMax_ subtractOperator(const UnsignedExtendedInt<u>& obj) const;
    template<unsigned int u> typename extIntReturnSize<t, u>::returnTypeTot_ multiplyOperator(const UnsignedExtendedInt<u>& obj) const;
    template<unsigned int u> UnsignedExtendedInt<t> equalOperator(const UnsignedExtendedInt<u>& obj);
    template<unsigned int u> bool isEqualOperator(const UnsignedExtendedInt<u>& obj) const;
    template<unsigned int u> bool greaterThanOperator(const UnsignedExtendedInt<u>& obj) const;
    template<unsigned int u> bool greaterThanOrEqualOperator(const UnsignedExtendedInt<u>& obj) const;
    template<unsigned int u> bool lessThanOperator(const UnsignedExtendedInt<u>& obj) const;
    template<unsigned int u> bool lessThanOrEqualOperator(const UnsignedExtendedInt<u>& obj) const;
    template<unsigned int u> UnsignedExtendedInt<t> rightShiftOperator(const UnsignedExtendedInt<u>& obj) const;
    template<unsigned int u> UnsignedExtendedInt<t> leftShiftOperator(const UnsignedExtendedInt<u>& obj) const;
    template<unsigned int u> typename extIntReturnSize<t, u>::returnTypeMax_ andOperator(const UnsignedExtendedInt<u>& obj) const;
    template<unsigned int u> typename extIntReturnSize<t, u>::returnTypeMax_ orOperator(const UnsignedExtendedInt<u>& obj) const;
public:
	UnsignedExtendedInt();
    template<unsigned int u> UnsignedExtendedInt(const UnsignedExtendedInt<u>& obj);
    UnsignedExtendedInt(unsigned long long obj);
    //UnsignedExtendedInt(const char* s);
    //~UnsignedExtendedInt();
    template<unsigned int u> UnsignedExtendedInt<t> operator=(const UnsignedExtendedInt<u>& obj) { return equalOperator(obj); }
    //const UnsignedExtendedInt& operator=(const char* s);
    template<unsigned int u> inline typename extIntReturnSize<t, u>::returnTypeMax_ operator+(const UnsignedExtendedInt<u>& obj) const { return addOperator(obj); }
    inline friend UnsignedExtendedInt<t> operator+(const UnsignedExtendedInt<t>& lhs, const UnsignedExtendedInt<t>& rhs) { return lhs.addOperator(rhs); }
    template<unsigned int u> inline typename extIntReturnSize<t, u>::returnTypeMax_ operator-(const UnsignedExtendedInt<u>& obj) const { return subtractOperator(obj); }
    inline friend UnsignedExtendedInt<t> operator-(const UnsignedExtendedInt<t>& lhs, const UnsignedExtendedInt<t>& rhs) { return lhs.subtractOperator(rhs); }
    template<unsigned int u> typename extIntReturnSize<t, u>::returnTypeTot_ operator*(const UnsignedExtendedInt<u>& obj) const { return multiplyOperator(obj); }
    inline friend typename extIntReturnSize<t, t>::returnTypeMax_ operator*(const UnsignedExtendedInt<t>& lhs, const UnsignedExtendedInt<t>& rhs) { return lhs.multiplyOperator(rhs); }
    template<unsigned int u> typename extIntReturnSize<t, u>::returnTypeMax_ operator/(const UnsignedExtendedInt<u>& divisor) const { return divideModOperator(divisor, ExtendedInt<t>::DIVIDE_OP); }
    inline friend typename extIntReturnSize<t, t>::returnTypeMax_ operator/(const UnsignedExtendedInt<t>& dividend, const UnsignedExtendedInt<t>& divisor) { return dividend.divideModOperator(divisor, ExtendedInt<t>::DIVIDE_OP); }
    //const UnsignedExtendedInt operator%(const UnsignedExtendedInt& divisor) const;
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
    template<unsigned int u> inline UnsignedExtendedInt<t> operator&(const UnsignedExtendedInt<u>& obj) const { return andOperator(obj); }
    inline friend UnsignedExtendedInt<t> operator&(const UnsignedExtendedInt<t>& lhs, const UnsignedExtendedInt<t>& rhs) { return lhs.andOperator(rhs); }
    template<unsigned int u> inline UnsignedExtendedInt<t> operator|(const UnsignedExtendedInt<u>& obj) const { return orOperator(obj); }
    inline friend UnsignedExtendedInt<t> operator|(const UnsignedExtendedInt<t>& lhs, const UnsignedExtendedInt<t>& rhs) { return lhs.orOperator(rhs); }
    //inline UnsignedExtendedInt operator^(const UnsignedExtendedInt& obj) const;
    inline UnsignedExtendedInt operator~() const;

    //template<unsigned int u>
    //friend std::ostream& operator<<(std::ostream& os, const UnsignedExtendedInt& obj) {
    //    os << obj.extendedIntToString();
    //    return os;
    //}



    //template<unsigned int u>
    //friend UnsignedExtendedInt<extIntReturnSize<t, u>::multipleOf32Bits_> operator*(UnsignedExtendedInt<t>& lhs, UnsignedExtendedInt<u>& rhs) {
    //    unsigned int maxArraySize = extIntReturnSize<t, u>::multipleOf32Bits_;
    //    if (lhs.ARRAY_SIZE < rhs.ARRAY_SIZE) {

    //    }
    //    int returnValueArraySize = 0;
    //    if (lhs.ARRAY_SIZE > rhs.getArraySize()) {
    //        returnValueArraySize = lhs.ARRAY_SIZE;
    //    }

    //    UnsignedExtendedInt<extIntReturnSize<t, u>::multipleOf32Bits_> returnValue;
    //    return returnValue;
    //}
    friend class UnsignedExtendedInt;       // allows access between private members between UnsignedExtendedInt<n> and UnsignedExtendedInt<m> for some n,m
};


//template<typename T> template<typename U> UnsignedExtendedInt<T>::UnsignedExtendedInt(const UnsignedExtendedInt<U>& obj) {
//    this->ARRAY_SIZE = T::_multipleOf32Bits;
//    for (unsigned int i = 0; i < this->ARRAY_SIZE; i++) {
//        this->ext_int[i] = 0;
//    }
//    if (this->ARRAY_SIZE > obj.getArraySize()) {
//        for (unsigned int i = 0; i < obj.getArraySize(); i++) {
//            this->ext_int[i] = obj.getValueAtIndex(i);
//        }
//    }
//    else {
//        for (unsigned int i = 0; i < this->ARRAY_SIZE; i++) {
//            this->ext_int[i] = obj.getValueAtIndex(i);
//        }
//    }
//}
//
//
//template<unsigned int t>
//template<unsigned int u>
//UnsignedExtendedInt<t>::UnsignedExtendedInt(const UnsignedExtendedInt<u>& obj) {
//    unsigned int minArraySize = extIntReturnSize<t, u>::multipleOf32BitsMin_;
//    for (unsigned int i = 0; i < minArraySize; i++) {
//        this->ext_int[i] = obj.getValueAtIndex(i);
//    }
//}

#include "UnsignedExtendedInt.cpp"

#endif
