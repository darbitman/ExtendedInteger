#include "UnsignedExtendedInt.h"


int main() {
  UnsignedExtendedInt a;
  for (unsigned int i = 0; i < a.getArraySize(); i++) {
    a.setValueAtIndex(0xFFFFFFFF, i);
  }
  UnsignedExtendedInt b;
  for (unsigned int i = 0; i < a.getArraySize(); i++) {
    b.setValueAtIndex(0xFFFFFFFF, i);
  }
  UnsignedExtendedInt c(a + b);
  UnsignedExtendedInt d(a + 1);
  UnsignedExtendedInt e(100);
  UnsignedExtendedInt f(e - 10);
  e == 100;
  return 0;
}