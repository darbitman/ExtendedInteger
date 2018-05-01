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


class IndexOutOfBoundsException : public Exception {
public:
  virtual void printError() const;
};

class MinArraySizeExceededException : public Exception {
public:
  virtual void printError() const;
};

class NegativeShiftValueException : public Exception {
public:
  virtual void printError() const;
};