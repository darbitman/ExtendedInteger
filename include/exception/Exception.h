#pragma once

class Exception {
public:
  virtual void printError() const;
};


class StackEmptyException : public Exception {
public:
  virtual void printError() const;
};


class DivideByZeroException : public Exception {
public:
  virtual void printError() const;
};


class InputStringInvalidCharacterException : public Exception {
public:
  virtual void printError() const;
};
