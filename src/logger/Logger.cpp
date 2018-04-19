#include "Logger.h"
#include <string>


Logger& Logger::getInstance() {
  static Logger instance;
  return instance;
}


Logger::Logger() {
  std::string logFileName = "log.txt";
  logFile.open(logFileName.c_str(), std::ofstream::out);
}


Logger::~Logger() {
  logFile.flush();
  logFile.close();
}


void Logger::addEntry(const char* s) {
  unsigned int strLength = 0;
  while (s[strLength] != 0) {           // compute string length
    strLength++;
  }
  logFile.write(s, strLength);
  logFile.put('\n');
}