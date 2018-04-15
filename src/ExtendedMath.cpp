#include <iostream>
#include "ExtendedInteger.h"


using namespace std;
using namespace ExtendedIntegerMathOperations;


int main() {
  uextint256_t a(0);
  uextint128_t b(0xffffffffff);
  b / a;
  return 0;
}
