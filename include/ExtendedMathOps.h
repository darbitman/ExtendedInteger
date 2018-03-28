#ifndef _EXTENDEDMATHOPS_H_
#define _EXTENDEDMATHOPS_H_


namespace ExtendedIntegerMathOperations {
    template<typename T>
    T log(T val, const T& base) {
        T returnValue(0ULL);
        while (val >= base) {
            ++returnValue;
            val = val / base;
        }
        return returnValue;
    }

    template<typename T>
    T logBase10(T& val) {
        T base(10);
        return log(val, base);
    }

    template<typename T>
    T pow(T val, T exp) {
        T returnValue(1ULL);
        for (; exp > 0ULL; exp--) {
            returnValue = returnValue * val;
        }
        return returnValue;
    }
}


#endif
