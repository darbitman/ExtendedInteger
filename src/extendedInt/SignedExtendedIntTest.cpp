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
  return 0;
}
