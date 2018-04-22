#include "UnsignedExtendedInt.h"


int main() {
  UnsignedExtendedInt a(0x1000000);
  UnsignedExtendedInt b(0x10);
  a / b;
  return 0;
}
