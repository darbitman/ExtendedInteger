#include <iostream>
#include "ExtendedInteger.h"


using namespace std;
using namespace ExtendedIntegerMathOperations;


int main() {
  uextint512_t a;
  a.setValueAtIndex(0xFFFFFFFF, 0);
  a.setValueAtIndex(0xFFFFFFFF, 1);
  a.setValueAtIndex(0xFFFFFFFF, 2);
  a.setValueAtIndex(0xFFFFFFFF, 3);
  a.setValueAtIndex(0xFFFFFFFF, 4);
  a.setValueAtIndex(0xFFFFFFFF, 5);
  a.setValueAtIndex(0xFFFFFFFF, 6);
  a.setValueAtIndex(0xFFFFFFFF, 7);
  a.setValueAtIndex(0xFFFFFFFF, 8);
  a.setValueAtIndex(0xFFFFFFFF, 9);
  a.setValueAtIndex(0xFFFFFFFF, 10);
  a.setValueAtIndex(0xFFFFFFFF, 11);
  a.setValueAtIndex(0xFFFFFFFF, 12);
  a.setValueAtIndex(0xFFFFFFFF, 13);
  a.setValueAtIndex(0xFFFFFFFF, 14);
  a.setValueAtIndex(0xFFFFFFFF, 15);
  cout << a;
  return 0;
}
