#include "SignedExtendedInt.h"


int main() {
  SignedExtendedInt a;
  for (unsigned int i = 0; i < a.getArraySize(); i++) {
    a.setValueAtIndex(0x80000000, i);
  }
  a.increaseArraySizeTo(8);
  a.setValueAtIndex(0, 4);
  a.setValueAtIndex(0x80000000, 5);
  a.clearUnusedMemory();
  return 0;
}
