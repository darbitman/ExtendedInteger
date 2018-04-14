#include "Exception.h"
#include <iostream>


void Exceptions::printError() {
  std::cout << "ERROR: General error" << std::endl;
}


void StackEmptyException::printError() {
  std::cout << "ERROR: Popping from empty stack" << std::endl;
}
