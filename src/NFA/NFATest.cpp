#include "NFA.h"
#include <string>

int main() {
    std::string regExp = "((A*B|AC)D)";
    NFA n(regExp.c_str(), regExp.length());
    return 0;
}