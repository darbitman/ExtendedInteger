#pragma once
class Digraph;
/*

*/
/**
Nondeterministic finite state automata
*/
class NFA {
private:
  /* Regular expression rules
   * Supports regular expressions to check for decimal (pos/neg) or hex input
   * Rules for writing such a regular expression:
   * Regular expression MUST be enclosed by parantheses
   * PERIOD means 0 or 1
   * ASTERISK means 0 or more
   * VERTICAL BAR means logical OR
  */
  char* rePtr;                                        // store reg exp
  Digraph* graphPtr;                                  // create digraph for epsilon transitions
  unsigned int numChars;                              // reg exp length

  /**
  Build a Digraph of epsilon transitions (i.e. those transitions that are based on metacharacters)
  */
  void buildEpsilonTransitionDigraph();

  /**
  Check if regular expression recognizes input string
  */
  bool recognizes(const char* txt, unsigned int txtLength);
public:
  /**
  Create an NFA to represent a regular expression
  */
  NFA(const char* regExp, unsigned int numChars);

  /**
  NFA copy constructor
  */
  NFA(const NFA& rhs);

  /**
  Clean up NFA memory
  */
  ~NFA();

  /**
  Returns true if string matches regular expression
  */
  bool validateTxt(const char* txt);

  /**
  Returns true if string matches regular expression
  */
  bool validateTxt(const char* txt, unsigned int txtLength);
};
