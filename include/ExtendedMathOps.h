#ifndef _EXTENDEDMATHOPS_H_
#define _EXTENDEDMATHOPS_H_


namespace ExtendedIntegerMathOperations {
    template<typename T>
    void log(T val, const T& base) {
        T result(0ULL);
        while (val >= base) {
            ++result;
            val = val / base;
        }
    }

    template<typename T>
    void logBase10(T& val) {
        T base(10);
        log(val, base);
    }
}


#endif
