#include "NFA.h"
#include "Stack.h"
#include "Bag.h"
#include "DirectedDFS.h"
#include "Exception.h"
#include "Digraph.h"
#include "Logger.h"


/**
Create an NFA to represent a regular expression
*/
NFA::NFA(const char* regExp, unsigned int numChars) {
  if (LOGGER_VERBOSITY == Logger::LogLevel::Verbose) {
    std::string s = "Creating an NFA with reg exp: ";
    s = s + regExp;
    Logger::getInstance().addEntry(s.c_str());
  }
  graphPtr = new Digraph(numChars + 1);                 // create digraph with numChars + 1 vertices. need extra vertex for "match" state
  this->numChars = numChars;
  rePtr = new char[numChars];
  for (unsigned int i = 0; i < numChars; i++) {         // copy characters
    this->rePtr[i] = regExp[i];
  }
  buildEpsilonTransitionDigraph();
}


NFA::NFA(const NFA& rhs) {
  if (LOGGER_VERBOSITY == Logger::LogLevel::Verbose) {
    std::string s = "Calling the NFA copy constructor";
    Logger::getInstance().addEntry(s.c_str());
  }
  numChars = rhs.numChars;
  rePtr = new char[numChars];
  for (unsigned int i = 0; i < numChars; i++) {         // copy characters
    rePtr[i] = rhs.rePtr[i];
  }
  graphPtr = new Digraph(*rhs.graphPtr);
}


NFA::~NFA() {
  if (LOGGER_VERBOSITY == Logger::LogLevel::Verbose) {
    std::string s = "Calling the NFA destructor";
    Logger::getInstance().addEntry(s.c_str());
  }
  delete graphPtr;
  delete[] rePtr;
}


/**
Build epsilond transition digraph given regular expression
*/
void NFA::buildEpsilonTransitionDigraph() {
  if (LOGGER_VERBOSITY == Logger::LogLevel::Verbose) {
    std::string s = "Building the epsilon transition graph using Digraph class";
    Logger::getInstance().addEntry(s.c_str());
  }
  Stack<unsigned int> ops;
  Stack<unsigned int> orOps;
  for (unsigned int i = 0; i < numChars; i++) {
    unsigned int lp = i;
    if (rePtr[i] == '(' || rePtr[i] == '|') {
      ops.push(i);                                      // store index of left paranthesis or OR character
    }
    else if (rePtr[i] == ')') {                         // process closing paranthesis: search for OR characters and opening paranthesis
      unsigned int orOp = 0;
      while (!ops.isEmpty()) {                          // extract all possible OR characters
        try {
          if (rePtr[ops.peek()] == '|') {
            orOp = ops.pop();
            orOps.push(orOp);                           // create OR stack to use later for endpoint of directed edge
            graphPtr->addEdge(orOp, i);                 // add edge from OR vertex to closing paranthesis
          }
          else {                                        // break out of while loop if opening paranthesis
            break;
          }
        }
        catch (const Exception& e) {
          e.printError();
        }
      }
      try {
        if (rePtr[ops.peek()] == '(') {
          unsigned int orOp = 0;
          lp = ops.pop();
          while (!orOps.isEmpty()) {
            orOp = orOps.pop();
            graphPtr->addEdge(lp, orOp + 1);
          }
        }
      }
      catch (const Exception& e) {
        e.printError();
      }
      if (rePtr[i + 1] == '*' && i < numChars - 1) {    // if closing paranthesis and next character is ASTERISK, need epsilon transition between it and opening paranthesis
        graphPtr->addEdge(lp, i + 1);
        graphPtr->addEdge(i + 1, lp);
      }
      if (rePtr[i + 1] == '.' && i < numChars - 1) {    // if closing paranthesis and next character is a PERIOD need epsilon transition from opening paranthesis to it, and from it to next
        graphPtr->addEdge(lp, i + 1);                   // add edge from opening paranthesis to PERIOD
      }
    }
    if (rePtr[i + 1] == '*'                             // one character lookahead for ASTERISK character, but also make sure current character is not a metacharacter
      && i < numChars - 1                               // make sure re[] isn't accessed past the end
      && rePtr[i] != ')'
      && rePtr[i] != '*'
      && rePtr[i] != '(') {
      graphPtr->addEdge(i, i + 1);                      // add loop edges
      graphPtr->addEdge(i + 1, i);
    }
    if (rePtr[i] == '(' ||
      rePtr[i] == '*' ||
      rePtr[i] == ')' ||
      rePtr[i] == '.') {                                // add epsilon transition to next state if metacharacter
      graphPtr->addEdge(i, i + 1);
    }
  }
}


/**
Returns true if string txt matches reg exp
*/
bool NFA::validateTxt(const char* txt) {
  if (LOGGER_VERBOSITY == Logger::LogLevel::Verbose) {
    std::string s = "Checking if string (";
    s = s + txt;
    s = s + ") matches regular expression";
    Logger::getInstance().addEntry(s.c_str());
  }
  unsigned int txtLength = 0;
  while (txt[txtLength] != 0) {                         // compute string length
    txtLength++;
  }
  return recognizes(txt, txtLength);
}


bool NFA::validateTxt(const char* txt, unsigned int txtLength) {
  if (LOGGER_VERBOSITY == Logger::LogLevel::Verbose) {
    std::string s = "Checking if string (";
    s = s + txt;
    s = s + ") matches regular expression";
    Logger::getInstance().addEntry(s.c_str());
  }
  return recognizes(txt, txtLength);
}



/**
Returns true if string txt matches reg exp
*/
bool NFA::recognizes(const char* txt, unsigned int txtLength) {
  Bag<unsigned int>* reachableStates = new Bag<unsigned int>();   // declare a bag that will be used for all reachable states via epsilon transitions
  DirectedDFS* dfs = new DirectedDFS(graphPtr, 0);                // find all reachable states starting from state 0
  for (unsigned int i = 0; i < graphPtr->V(); i++) {
    if (dfs->visited(i)) {
      reachableStates->add(i);
    }
  }

  for (unsigned int i = 0; i < txtLength; i++) {        // scan char by char through input string
    Bag<unsigned int> match;

    // go through every reachable state via epsilon transition and check if input txt matches character at those reachable states
    for (Bag<unsigned int>::iterator iter = reachableStates->begin(); iter != reachableStates->end(); iter++) {
      if (*iter == numChars) {                          // accept state is one of the reachable states
        continue;
      }
      if (txt[i] == rePtr[*iter]) {                     // if input txt character at pos i matches the character at any of the states...
        match.add(*iter + 1);                           // reachable via epsilon transitions, add a match transition to the state after...
      }                                                 // the reachable state
    }
    delete dfs;
    delete reachableStates;
    dfs = new DirectedDFS(graphPtr, match);             // run DirectedDFS using the states found by match transitions (if any)
    reachableStates = new Bag<unsigned int>();
    for (unsigned int i = 0; i < graphPtr->V(); i++) {  // new reachable states from the match states
      if (dfs->visited(i)) {
        reachableStates->add(i);
      }
    }
  }
  // Search for accept state once all input chars have been examined
  for (Bag<unsigned int>::iterator iter = reachableStates->begin(); iter != reachableStates->end(); iter++) {
    if (*iter == numChars) {
      return true;
    }
  }
  return false;
}
