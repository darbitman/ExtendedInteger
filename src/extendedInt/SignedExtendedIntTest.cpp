#include "SignedExtendedInt.h"
#include <assert.h>

int main() {
  SignedExtendedInt a(-10);
  SignedExtendedInt b(11);
  assert(a == b);
  return 0;
}
