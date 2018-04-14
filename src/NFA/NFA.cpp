#include "NFA.h"
#include "Stack.h"
#include "Bag.h"
#include "DirectedDFS.h"
#include "Exception.h"


NFA::NFA(const char* regExp, unsigned int numChars) {
  this->graph = new Digraph(numChars + 1);                // create digraph with numChars + 1 vertices. need extra vertex for "match" state
  this->numChars = numChars;
  this->re = new char[numChars];
  for (unsigned int i = 0; i < numChars; i++) {           // copy characters
    this->re[i] = regExp[i];
  }
  buildEpsilonTransitionDigraph();
}


NFA::~NFA() {
  delete graph;
  delete[] re;
}


void NFA::buildEpsilonTransitionDigraph() {
  Stack<unsigned int> ops;
  Stack<unsigned int> orOps;
  for (unsigned int i = 0; i < numChars; i++) {
    unsigned int lp = i;
    if (re[i] == '(' || re[i] == '|') {
      ops.push(i);                                      // store index of left paranthesis or OR character
    }
    else if (re[i] == ')') {                            // process closing paranthesis: search for OR characters and opening paranthesis
      unsigned int orOp = 0;
      while (!ops.isEmpty()) {                          // extract all possible OR characters
        try {
          if (re[ops.peek()] == '|') {
            orOp = ops.pop();
            orOps.push(orOp);                           // create OR stack to use later for endpoint of directed edge
            graph->addEdge(orOp, i);                    // add edge from OR vertex to closing paranthesis
          }
          else {                                        // break out of while loop if opening paranthesis
            break;
          }
        }
        catch (StackEmptyException e) {
          e.printError();
        }
      }
      try {
        if (re[ops.peek()] == '(') {
          unsigned int orOp = 0;
          lp = ops.pop();
          while (!orOps.isEmpty()) {
            orOp = orOps.pop();
            graph->addEdge(lp, orOp + 1);
          }
        }
      }
      catch (StackEmptyException e) {
        e.printError();
      }
      if (re[i + 1] == '*' && i < numChars - 1) {       // if closing paranthesis and next character is ASTERISK, need epsilon transition between it and opening paranthesis
        graph->addEdge(lp, i + 1);
        graph->addEdge(i + 1, lp);
      }
      if (re[i + 1] == '.' && i < numChars - 1) {       // if closing paranthesis and next character is a PERIOD need epsilon transition from opening paranthesis to it, and from it to next
        graph->addEdge(lp, i + 1);                      // add edge from opening paranthesis to PERIOD
      }
    }
    if (re[i + 1] == '*'                                // one character lookahead for ASTERISK character, but also make sure current character is not a metacharacter
      && i < numChars - 1                               // make sure re[] isn't accessed past the end
      && re[i] != ')'
      && re[i] != '*'
      && re[i] != '(') {
      graph->addEdge(i, i + 1);                         // add loop edges
      graph->addEdge(i + 1, i);
    }
    if (re[i] == '(' ||
        re[i] == '*' ||
        re[i] == ')' ||
        re[i] == '.') {                                 // add epsilon transition to next state if metacharacter
      graph->addEdge(i, i + 1);
    }
  }
}


bool NFA::recognizes(const char* txt) {
  unsigned int txtLength = 0;
  while (txt[txtLength] != 0) {                                   // compute string length
    txtLength++;
  }
  Bag<unsigned int>* reachableStates = new Bag<unsigned int>();   // declare a bag that will be used for all reachable states via epsilon transitions
  DirectedDFS* dfs = new DirectedDFS(graph, 0);                   // find all reachable states starting from state 0
  for (unsigned int i = 0; i < graph->V(); i++) {
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
      if (txt[i] == re[*iter]) {                        // if input txt character at pos i matches the character at any of the states...
        match.add(*iter + 1);                           // reachable via epsilon transitions, add a match transition to the state after...
      }                                                 // the reachable state
    }
    delete dfs;
    delete reachableStates;
    dfs = new DirectedDFS(graph, match);                // run DirectedDFS using the states found by match transitions (if any)
    reachableStates = new Bag<unsigned int>();
    for (unsigned int i = 0; i < graph->V(); i++) {     // new reachable states from the match states
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
