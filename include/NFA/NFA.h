#pragma once
#include "Digraph.h"

class NFA {
private:
  char* re;                                           // store reg exp
  Digraph* graph;                                     // create digraph for epsilon transitions
  unsigned int numChars;                              // reg exp length
  void buildEpsilonTransitionDigraph();
public:
  NFA(const char* regExp, unsigned int numChars);
  ~NFA();
  bool recognizes(const char* txt);
};
