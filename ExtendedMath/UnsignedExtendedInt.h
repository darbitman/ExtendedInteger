#ifndef _UNSIGNEDEXTENDEDINT_H_
#define _UNSIGNEDEXTENDEDINT_H_


#include "ExtendedInt.h"


template<unsigned int t = 4>
class UnsignedExtendedInt : public ExtendedInt<t> {
protected:
    //void stringToExtendedInt(const char* s);
    //virtual std::string extendedIntToString() const;
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
    UnsignedExtendedInt(unsigned long long obj);
    ~UnsignedExtendedInt();
    template<unsigned int u> UnsignedExtendedInt<t> operator=(const UnsignedExtendedInt<u>& obj) { return equalOperator(obj); }
    //const UnsignedExtendedInt& operator=(const char* s) { stringToExtendedInt(s); return *this;  }
    template<unsigned int u> inline typename extIntReturnSize<t, u>::uIntReturnTypeMax_ operator+(const UnsignedExtendedInt<u>& obj) const { return addOperator(obj); }
    inline friend UnsignedExtendedInt<t> operator+(const UnsignedExtendedInt<t>& lhs, const UnsignedExtendedInt<t>& rhs) { return lhs.addOperator(rhs); }
    template<unsigned int u> inline typename extIntReturnSize<t, u>::uIntReturnTypeMax_ operator-(const UnsignedExtendedInt<u>& obj) const { return subtractOperator(obj); }
    inline friend UnsignedExtendedInt<t> operator-(const UnsignedExtendedInt<t>& lhs, const UnsignedExtendedInt<t>& rhs) { return lhs.subtractOperator(rhs); }
    template<unsigned int u> typename extIntReturnSize<t, u>::uIntReturnTypeTot_ operator*(const UnsignedExtendedInt<u>& obj) const { return multiplyOperator(obj); }
    inline friend typename extIntReturnSize<t, t>::uIntReturnTypeTot_ operator*(const UnsignedExtendedInt<t>& lhs, const UnsignedExtendedInt<t>& rhs) { return lhs.multiplyOperator(rhs); }
    template<unsigned int u> typename extIntReturnSize<t, u>::uIntReturnTypeMax_ operator/(const UnsignedExtendedInt<u>& divisor) const { return divideModOperator(divisor, ExtendedInt<t>::DIVIDE_OP); }
    inline friend typename extIntReturnSize<t, t>::uIntReturnTypeMax_ operator/(const UnsignedExtendedInt<t>& dividend, const UnsignedExtendedInt<t>& divisor) { return dividend.divideModOperator(divisor, ExtendedInt<t>::MOD_OP); }
    template<unsigned int u> typename extIntReturnSize<t, u>::uIntReturnTypeMax_ operator%(const UnsignedExtendedInt<u>& divisor) const { return divideModOperator(divisor, ExtendedInt<t>::DIVIDE_OP); }
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

    inline UnsignedExtendedInt operator~() const;

    //template<unsigned int u>
    //friend std::ostream& operator<<(std::ostream& os, const UnsignedExtendedInt& obj) {
    //    os << obj.extendedIntToString();
    //    return os;
    //}

    friend class UnsignedExtendedInt;       // allows access between private members between UnsignedExtendedInt<n> and UnsignedExtendedInt<m> for some n,m
};


#include "UnsignedExtendedInt.cpp"


#endif
