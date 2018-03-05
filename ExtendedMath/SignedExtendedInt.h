#ifndef _SIGNEDEXTENDEDINT_H_
#define _SIGNEDEXTENDEDINT_H_





template<unsigned int t>
class SignedExtendedInt : public ExtendedInt<t> {
protected:
    virtual void stringToExtendedInt(const char* s);
    virtual std::string extendedIntToString() const;
    const SignedExtendedInt divideModOperator(const SignedExtendedInt& divisor, const ExtendedInt<T>::DIVIDE_OPERATION op) const;
public:
    SignedExtendedInt();
    SignedExtendedInt(const SignedExtendedInt& obj);
    SignedExtendedInt(const char* s);
    SignedExtendedInt(const unsigned long long& obj);
    template<typename U> SignedExtendedInt(const SignedExtendedInt<U>& obj);
    ~SignedExtendedInt();
    const SignedExtendedInt& operator=(const SignedExtendedInt& obj);
    const SignedExtendedInt& operator=(const char* s);
    const SignedExtendedInt operator+(const SignedExtendedInt& obj) const;
    const SignedExtendedInt operator+(const long long& obj) const;
    const SignedExtendedInt operator-(const SignedExtendedInt& obj) const;
    const SignedExtendedInt operator-(const long long& obj) const;
    const SignedExtendedInt operator*(const SignedExtendedInt& obj) const;
    const SignedExtendedInt operator*(const long long& obj) const;
    const SignedExtendedInt operator/(const SignedExtendedInt& obj) const;
    const SignedExtendedInt operator%(const SignedExtendedInt& obj) const;
    bool operator==(const SignedExtendedInt& obj) const;
    bool operator<(const SignedExtendedInt& obj) const;
    bool operator>(const SignedExtendedInt& obj) const;
    bool operator<=(const SignedExtendedInt& obj) const;
    const SignedExtendedInt operator>>(unsigned int shiftVal) const;
    const SignedExtendedInt operator<<(unsigned int shiftVal) const;
    inline SignedExtendedInt operator&(const SignedExtendedInt& obj) const;
    inline SignedExtendedInt operator&(const unsigned long long& obj) const;
    inline SignedExtendedInt operator|(const SignedExtendedInt& obj) const;
    inline SignedExtendedInt operator|(const unsigned long long& obj) const;
    inline SignedExtendedInt operator^(const SignedExtendedInt& obj) const;
    inline SignedExtendedInt operator^(const unsigned long long& obj) const;
    inline const SignedExtendedInt operator~() const;
};


template<typename T> template<typename U> SignedExtendedInt<T>::SignedExtendedInt(const SignedExtendedInt<U>& obj) {
    this->ARRAY_SIZE = T::_multipleOf32Bits;
    for (unsigned int i = 0; i < this->ARRAY_SIZE; i++) {
        this->ext_int[i] = 0;
    }
    // TODO
}
#endif