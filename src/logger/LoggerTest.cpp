#include "Logger.h"
#include <string>


int main() {
  for (unsigned int i = 0; i < 3; i++) {
    if (Logger::LogLevel::Error != i) {
      std::string s = "Entry ";
      s = s + std::to_string(LOGGER_VERBOSITY);
      Logger::getInstance().addEntry(s.c_str());
    }
  }
  return 0;
}