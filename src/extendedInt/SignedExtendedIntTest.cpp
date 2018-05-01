#include "SignedExtendedInt.h"
#include <assert.h>

int main() {
  SignedExtendedInt a(-10);
  SignedExtendedInt b(10);
  SignedExtendedInt c(-20);
  SignedExtendedInt d(20);
  assert((a > c) == true);
  assert((a > a) == false);
  assert((c > a) == false);
  assert((b > a) == true);
  assert((d > b) == true);
  assert((d > d) == false);
  assert((b > d) == false);

  SignedExtendedInt aa;
  aa.setValueAtIndex(0x80000000, 3);
  SignedExtendedInt bb;
  bb.newArraySize(5);
  bb.setValueAtIndex(0x80000000, 3);
  aa / bb;
  SignedExtendedInt cc("-123456789012345678901234567890123456789012345678901234567890");
  std::cout << cc;
  return 0;
}
