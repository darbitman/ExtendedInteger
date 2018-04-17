#pragma once
#include <fstream>

class Logger {
public:
  static Logger& getInstance();
  Logger(const Logger&) = delete;
  void operator=(const Logger&) = delete;
  void addEntry(const char* s);
private:
  Logger();
  ~Logger();
  std::ofstream logFile;
};
