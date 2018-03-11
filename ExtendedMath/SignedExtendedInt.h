#ifndef _SIGNEDEXTENDEDINT_H_
#define _SIGNEDEXTENDEDINT_H_


#include "ExtendedInt.h"


template<unsigned int t = 4>
class SignedExtendedInt : public ExtendedInt<t> {
protected:
    template<unsigned int u> typename extIntReturnSize<t, u>::intReturnTypeMax_ andOperator(const SignedExtendedInt<u>& obj) const;
};


#include "SignedExtendedInt.cpp"


#endif
