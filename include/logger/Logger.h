#pragma once


class Logger {
public:
  static Logger& getInstance();
  Logger(const Logger&) = delete;
  void operator=(const Logger&) = delete;
};
