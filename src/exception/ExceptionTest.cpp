#include "Exception.h"


int main() {
  try {
    throw DivideByZeroException();
  }
  catch (Exception& e) {
    e.printError();
  }
  return 0;
}