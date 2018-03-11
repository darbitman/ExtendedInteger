#ifndef _SIGNEDEXTENDEDINT_H_
#define _SIGNEDEXTENDEDINT_H_


#include "ExtendedInt.h"


template<unsigned int t = 4>
class SignedExtendedInt : public ExtendedInt<t> {
protected:
    template<unsigned int u> SignedExtendedInt<t> rightShiftOperator(const SignedExtendedInt<u>& obj) const;
    template<unsigned int u> SignedExtendedInt<t> leftShiftOperator(const SignedExtendedInt<u>& obj) const;
    template<unsigned int u> typename extIntReturnSize<t, u>::intReturnTypeMax_ andOperator(const SignedExtendedInt<u>& obj) const;
    template<unsigned int u> typename extIntReturnSize<t, u>::intReturnTypeMax_ orOperator(const SignedExtendedInt<u>& obj) const;
    template<unsigned int u> typename extIntReturnSize<t, u>::intReturnTypeMax_ xorOperator(const SignedExtendedInt<u>& obj) const;
};


#include "SignedExtendedInt.cpp"


#endif
