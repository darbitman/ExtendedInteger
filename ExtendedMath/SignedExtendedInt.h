#ifndef _SIGNEDEXTENDEDINT_H_
#define _SIGNEDEXTENDEDINT_H_


#include "ExtendedInt.h"


template<unsigned int t = 4>
class SignedExtendedInt : public ExtendedInt<t> {
protected:
    template<unsigned int u> typename extIntReturnSize<t, u>::intReturnTypeMax_ addOperator(const SignedExtendedInt<u>& obj) const;
    template<unsigned int u> typename extIntReturnSize<t, u>::intReturnTypeMax_ subtractOperator(const SignedExtendedInt<u>& obj) const;
    template<unsigned int u> SignedExtendedInt<t>& equalOperator(const SignedExtendedInt<u>& obj);
    template<unsigned int u> bool isEqualOperator(const SignedExtendedInt<u>& obj) const;
    template<unsigned int u> bool greaterThanOperator(const SignedExtendedInt<u>& obj) const;
    template<unsigned int u> bool greaterThanOrEqualOperator(const SignedExtendedInt<u>& obj) const;
    template<unsigned int u> bool lessThanOperator(const SignedExtendedInt<u>& obj) const;
    template<unsigned int u> bool lessThanOrEqualOperator(const SignedExtendedInt<u>& obj) const;
    template<unsigned int u> SignedExtendedInt<t> rightShiftOperator(const SignedExtendedInt<u>& obj) const;
    template<unsigned int u> SignedExtendedInt<t> leftShiftOperator(const SignedExtendedInt<u>& obj) const;
    template<unsigned int u> typename extIntReturnSize<t, u>::intReturnTypeMax_ andOperator(const SignedExtendedInt<u>& obj) const;
    template<unsigned int u> typename extIntReturnSize<t, u>::intReturnTypeMax_ orOperator(const SignedExtendedInt<u>& obj) const;
    template<unsigned int u> typename extIntReturnSize<t, u>::intReturnTypeMax_ xorOperator(const SignedExtendedInt<u>& obj) const;
public:
    SignedExtendedInt();
    template<unsigned int u> SignedExtendedInt(const SignedExtendedInt<u>& obj);
    SignedExtendedInt(long long obj);
    //SignedExtendedInt(const char* s) { stringToExtendedInt(s); }
    ~SignedExtendedInt() {}
    template<unsigned int u> const SignedExtendedInt<t>& operator=(const SignedExtendedInt<u>& obj) { return equalOperator(obj); }
    //const SignedExtendedInt<t>& operator=(const char* s) { stringToExtendedInt(s); return *this; }
    template<unsigned int u> inline typename extIntReturnSize<t, u>::intReturnTypeMax_ operator+(const SignedExtendedInt<u>& obj) const { return addOperator(obj); }
    inline friend SignedExtendedInt<t> operator+(const SignedExtendedInt<t>& lhs, const SignedExtendedInt<t>& rhs) { return lhs.addOperator(rhs); }
    template<unsigned int u> inline typename extIntReturnSize<t, u>::intReturnTypeMax_ operator-(const SignedExtendedInt<u>& obj) const { return subtractOperator(obj); }
    inline friend SignedExtendedInt<t> operator-(const SignedExtendedInt<t>& lhs, const SignedExtendedInt<t>& rhs) { return lhs.subtractOperator(rhs); }
    template<unsigned int u> inline bool operator==(const SignedExtendedInt<u>& obj) const { return isEqualOperator(obj); }
    inline friend bool operator==(const SignedExtendedInt<t>& lhs, const SignedExtendedInt<t>& rhs) { return lhs.isEqualOperator(rhs); }
    template<unsigned int u> inline bool operator>(const SignedExtendedInt<u>& obj) const { return greaterThanOperator(obj); }
    inline friend bool operator>(const SignedExtendedInt<t>& lhs, const SignedExtendedInt<t>& rhs) { return lhs.greaterThanOperator(rhs); }
    template<unsigned int u> inline bool operator>=(const SignedExtendedInt<u>& obj) const { return greaterThanOrEqualOperator(obj); }
    inline friend bool operator>=(const SignedExtendedInt<t>& lhs, const SignedExtendedInt<t>& rhs) { return lhs.greaterThanOrEqualOperator(rhs); }
    template<unsigned int u> inline bool operator<(const SignedExtendedInt<u>& obj) const { return lessThanOperator(obj); }
    inline friend bool operator<(const SignedExtendedInt<t>& lhs, const SignedExtendedInt<t>& rhs) { return lhs.lessThanOperator(rhs); }
    template<unsigned int u> inline bool operator<=(const SignedExtendedInt<u>& obj) const { return lessThanOrEqualOperator(obj); }
    inline friend bool operator<=(const SignedExtendedInt<t>& lhs, const SignedExtendedInt<t>& rhs) { return lhs.lessThanOrEqualOperator(rhs); }
    template<unsigned int u> inline SignedExtendedInt<t> operator>>(const SignedExtendedInt<u>& obj) const { return rightShiftOperator(obj); }
    inline friend SignedExtendedInt<t> operator>>(const SignedExtendedInt<t>& lhs, const SignedExtendedInt<t>& rhs) { return lhs.rightShiftOperator(obj); }
    template<unsigned int u> inline typename extIntReturnSize<t, u>::intReturnTypeMax_ operator&(const SignedExtendedInt<u>& obj) const { return andOperator(obj); }
    inline friend SignedExtendedInt<t> operator&(const SignedExtendedInt<t>& lhs, const SignedExtendedInt<t>& rhs) { return lhs.andOperator(rhs); }
    template<unsigned int u> inline typename extIntReturnSize<t, u>::intReturnTypeMax_ operator|(const SignedExtendedInt<u>& obj) const { return orOperator(obj); }
    inline friend SignedExtendedInt<t> operator|(const SignedExtendedInt<t>& lhs, const SignedExtendedInt<t>& rhs) { return lhs.orOperator(rhs); }
    template<unsigned int u> inline typename extIntReturnSize<t, u>::intReturnTypeMax_ operator^(const SignedExtendedInt<u>& obj) const { return xorOperator(obj); }
    inline friend SignedExtendedInt<t> operator^(const SignedExtendedInt<t>& lhs, const SignedExtendedInt<t>& rhs) { return lhs.xorOperator(rhs); }
    SignedExtendedInt<t> operator~() const;

};


#include "SignedExtendedInt.cpp"


#endif
