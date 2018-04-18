#pragma once
#include <fstream>

class Logger {
public:
  static Logger& getInstance();
  Logger(const Logger&) = delete;
  void operator=(const Logger&) = delete;
  void addEntry(const char* s);
  enum LogLevel {
    None = 0,         // don't log anything
    Error = 1,        // log only errors
    Verbose = 2       // log every action
  };
private:
  Logger();
  ~Logger();
  std::ofstream logFile;
};
