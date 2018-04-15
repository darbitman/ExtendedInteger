#pragma once


class Digraph;


class NFA {
private:
  char* rePtr;                                        // store reg exp
  Digraph* graphPtr;                                  // create digraph for epsilon transitions
  unsigned int numChars;                              // reg exp length
  void buildEpsilonTransitionDigraph();
  bool recognizes(const char* txt, unsigned int txtLength);
public:
  NFA(const char* regExp, unsigned int numChars);
  NFA(const NFA& rhs);
  ~NFA();
  bool validateTxt(const char* txt);
  bool validateTxt(const char* txt, unsigned int txtLength);
};
