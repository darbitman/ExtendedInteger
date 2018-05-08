#include "UnsignedExtendedInt.h"


int main() {
  UnsignedExtendedInt a("123456789123456789123456789123456789123456789123456789");
  UnsignedExtendedInt b(123456789012345678);
  std::cout << a;
  return 0;
}
