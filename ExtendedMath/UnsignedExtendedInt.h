#ifndef _UNSIGNEDEXTENDEDINT_H_
#define _UNSIGNEDEXTENDEDINT_H_
#include "ExtendedInt.h"

class UnsignedExtendedInt : public ExtendedInt {
public:
	UnsignedExtendedInt();
	UnsignedExtendedInt(const UnsignedExtendedInt& obj);
    UnsignedExtendedInt(const char* s);
	~UnsignedExtendedInt();
    const UnsignedExtendedInt& operator=(const UnsignedExtendedInt& obj);
    const UnsignedExtendedInt& operator+(const UnsignedExtendedInt& obj);
    const UnsignedExtendedInt& operator+(const unsigned long long& obj);
    const UnsignedExtendedInt& operator-(const UnsignedExtendedInt& obj);
    const UnsignedExtendedInt& operator*(const UnsignedExtendedInt& obj);
    const UnsignedExtendedInt& operator/(const UnsignedExtendedInt& obj);
    bool operator==(const UnsignedExtendedInt& obj) const;
    bool operator>(const UnsignedExtendedInt& obj) const;
    bool operator>=(const UnsignedExtendedInt& obj) const;
    bool operator<(const UnsignedExtendedInt& obj) const;
    bool operator<=(const UnsignedExtendedInt& obj) const;
    UnsignedExtendedInt& operator>>(unsigned int shiftVal) const;
    UnsignedExtendedInt& operator<<(unsigned int shiftVal) const;
    UnsignedExtendedInt& operator&(const UnsignedExtendedInt& obj) const;
    UnsignedExtendedInt& operator&(const unsigned long long& obj) const;
    UnsignedExtendedInt& operator|(const UnsignedExtendedInt& obj) const;
    void setValueAtIndex(const unsigned long long val, const unsigned int index);
    unsigned long long getValueAtIndex(const unsigned int index) const;
};


#endif
