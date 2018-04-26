#include "SignedExtendedInt.h"


int main() {
  SignedExtendedInt a;
  for (unsigned int i = 0; i < a.getArraySize(); i++) {
    a.setValueAtIndex(0x80000000, i);
  }
  a.increaseArraySizeTo(6);
  a.decreaseArraySizeTo(3);
  return 0;
}
