#include "Exception.h"
#include <iostream>


void Exception::printError() const {
  std::cout << "ERROR: General error" << std::endl;
}


void StackEmptyException::printError() const {
  std::cout << "ERROR: Popping from empty stack" << std::endl;
}


void DivideByZeroException::printError() const {
  std::cout << "ERROR: Dividing by zero" << std::endl;
}


void InputStringInvalidCharacterException::printError() const {
  std::cout << "ERROR: Input string contains an invalid character" << std::endl;
}