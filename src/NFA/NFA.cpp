#include "NFA.h"
#include "Stack.h"
#include "Bag.h"
#include "DirectedDFS.h"


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
    Stack ops;
    for (unsigned int i = 0; i < numChars; i++) {
        unsigned int lp = i;
        if (re[i] == '(' || re[i] == '|') {
            ops.push(i);                                    // store index of left parantheses or OR character
        }
        else if (re[i] == ')') {                            // pop left parantheses or OR character if exists
            unsigned int orChar = ops.pop();                // assume OR character, get its index
            if (re[orChar] == '|') {
                lp = ops.pop();                             // if OR, then pop left parantheses position
                graph->addEdge(lp, orChar +1);              // add directed edge from left parantheses to character immediately after OR
                graph->addEdge(orChar, i);                  // add directed edge from OR to right parantheses
            }
            else {                                          // if popped character was a left parantheses, then set accordingly
                lp = orChar;
            }
        }
        if (re[i + 1] == '*' && i < numChars - 1) {         // one character lookahead for ASTERISK character
            graph->addEdge(i, i + 1);                       // add loop edges
            graph->addEdge(i + 1, i);
        }
        if (re[i] == '(' || re[i] == '*' || re[i] == ')') { // add epsilon transition to next state if metacharacter
            graph->addEdge(i, i + 1);
        }
    }
}

bool NFA::recognizes(const char* txt) {
    unsigned int txtLength = 0;
    while (txt[txtLength] != 0) {             // compute string length
        txtLength++;
    }
    Bag<unsigned int>* reachableStates = new Bag<unsigned int>();   // declare a bag that will be used for all reachable states via epsilon transitions
    DirectedDFS* dfs = new DirectedDFS(graph, 0);                   // find all reachable states starting from state 0
    for (unsigned int i = 0; i < graph->V(); i++) {
        if (dfs->visited(i)) {
            reachableStates->add(i);
        }
    }

    for (unsigned int i = 0; i < txtLength; i++) {          // scan char by char through input string
        Bag<unsigned int> match;

        // go through every reachable state via epsilon transition and check if input txt matches character at those reachable states
        for (Bag<unsigned int>::iterator iter = reachableStates->begin(); iter != reachableStates->end(); iter++) {
            if (*iter == numChars) {                        // accept state is one of the reachable states
                continue;
            }
            if (txt[i] == re[*iter]) {                      // if input txt character at pos i matches the character at any of the states...
                match.add(*iter + 1);                       // reachable via epsilon transitions, add a match transition to the state after...
            }                                               // the reachable state
        }
        delete dfs;
        delete reachableStates;
        dfs = new DirectedDFS(graph, match);                    // run DirectedDFS using the states found by match transitions (if any)
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
