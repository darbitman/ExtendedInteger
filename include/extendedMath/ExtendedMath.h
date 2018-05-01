#pragma once


namespace ExtendedMath {
  template<typename T>
  T log(T val, const T& base) {
    T returnValue(0);
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
    T returnValue;
    if (exp < 0) {
      returnValue.setValueAtIndex(0, 0);
      return returnValue;
    }
    if (exp == 0) {
      returnValue.setValueAtIndex(1, 0);
      return returnValue;
    }
    for (; exp > 0; exp--) {
      returnValue = returnValue * val;
    }
    return returnValue;
  }

  template<typename T>
  T factorial(T val) {
    if (val < 0) {
      std::cout << "Cannot run factorial on negative numbers" << std::endl;
      exit(-1);
    }
    T returnValue(1);
    while (val > 0) {
      returnValue = returnValue * val--;
    }
    return returnValue;
  }
}
