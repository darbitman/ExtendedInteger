#include "NFA.h"
#include <string>
#include <iostream>

int main() {
  std::string regExp = "(((-).(0|1|2|3|4|5|6|7|8|9)*)|((0x)(0|1|2|3|4|5|6|7|8|9|A|B|C|D|E|F)*))";
  NFA n(regExp.c_str(), regExp.length());
  std::cout << n.validateTxt("0x123456789ABCEDFFFFABDED") << std::endl;
  std::cout << n.validateTxt("12345678901234569870321657489") << std::endl;
  std::cout << n.validateTxt("-1234567890") << std::endl;
  std::cout << n.validateTxt("0-12345678901234569870321657489") << std::endl;
  std::cout << n.validateTxt("asdfbnkle") << std::endl;
  std::cout << n.validateTxt("-0x1234567890ABCDEF") << std::endl;
  std::cout << n.validateTxt("") << std::endl;
  return 0;
}