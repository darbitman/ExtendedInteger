#include "NFA.h"
#include <string>
#include <iostream>

int main() {
  std::string regExp = "((0x).(0|1|2|3|4|5|6|7|8|9)*)";
  NFA n(regExp.c_str(), regExp.length());
  std::cout << n.recognizes("0xx123") << std::endl;
  return 0;
}