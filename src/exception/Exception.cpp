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


void IndexOutOfBoundsException::printError() const {
  std::cout << "ERROR: Index out of bounds" << std::endl;
}


void MinArraySizeExceededException::printError() const {
  std::cout << "ERROR: Attempted to set array size less than 4" << std::endl;
}