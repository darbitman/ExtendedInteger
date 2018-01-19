#ifndef _EXTENDEDINT_H_
#define _EXTENDEDINT_H_

class UnsignedExtendedInt;

class ExtendedInt {
protected:
    enum DIVIDE_OPERATION { DIVIDE_OP, MOD_OP };
	static const unsigned int ARRAY_SIZE = 4;
	unsigned int ext_int[ARRAY_SIZE];
public:
    virtual ~ExtendedInt() {}
	virtual const UnsignedExtendedInt& operator=(const UnsignedExtendedInt& obj) = 0;
    virtual const UnsignedExtendedInt& operator+(const UnsignedExtendedInt& obj) = 0;
    virtual const UnsignedExtendedInt& operator+(const unsigned long long& obj) = 0;
    virtual const UnsignedExtendedInt& operator-(const UnsignedExtendedInt& obj) = 0;
    virtual const UnsignedExtendedInt& operator*(const UnsignedExtendedInt& obj) = 0;
    virtual const UnsignedExtendedInt& operator/(const UnsignedExtendedInt& divisor) = 0;
    virtual const UnsignedExtendedInt& operator%(const UnsignedExtendedInt& divisor) = 0;
    virtual const UnsignedExtendedInt& divideModOperator(const UnsignedExtendedInt& divisor, const DIVIDE_OPERATION op) = 0;
    virtual bool operator==(const UnsignedExtendedInt& obj) const = 0;
    virtual bool operator>(const UnsignedExtendedInt& obj) const = 0;
    virtual bool operator>=(const UnsignedExtendedInt& obj) const = 0;
    virtual bool operator<=(const UnsignedExtendedInt& obj) const = 0;
    virtual bool operator<(const UnsignedExtendedInt& obj) const = 0;
    virtual UnsignedExtendedInt& operator>>(unsigned int shiftVal) const = 0;
    virtual UnsignedExtendedInt& operator<<(unsigned int shiftVal) const = 0;
    virtual UnsignedExtendedInt& operator&(const UnsignedExtendedInt& obj) const = 0;
    virtual UnsignedExtendedInt& operator&(const unsigned long long& obj) const = 0;
    virtual UnsignedExtendedInt& operator|(const UnsignedExtendedInt& obj) const = 0;
    virtual void setValueAtIndex(const unsigned long long val, const unsigned int index) = 0;
    virtual unsigned long long getValueAtIndex(const unsigned int index) const = 0;
};


#endif
