#include "NFA.h"
#include <string>
#include <iostream>

int main() {
  std::string regExp = "((A*B|AC)D)";
  NFA n(regExp.c_str(), regExp.length());
  std::cout << n.recognizes("AABD") << std::endl;
  return 0;
}