#include "UnsignedExtendedInt.h"


int main() {
  UnsignedExtendedInt a;
  a.setValueAtIndex(0xa, 0);
  UnsignedExtendedInt b;
  b.setValueAtIndex(0x5, 0);
  UnsignedExtendedInt c;
  a.increaseArraySizeTo(10);
  a.decreaseArraySizeTo(5);
  return 0;
}