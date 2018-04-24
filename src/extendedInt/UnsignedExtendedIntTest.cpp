#include "UnsignedExtendedInt.h"


int main() {
  UnsignedExtendedInt a("123456789123456789");
  UnsignedExtendedInt b(0x10);
  a / b;
  return 0;
}
