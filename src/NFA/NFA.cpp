#include "NFA.h"
#include "Stack.h"


NFA::NFA(const char* regExp, unsigned int numChars) {
    this->graph = new Digraph(numChars + 1);                // create digraph with numChars + 1 vertices. need extra vertex for "match" state
    this->numChars = numChars;
    this->re = new char[numChars];
    for (unsigned int i = 0; i < numChars; i++) {           // copy characters
        this->re[i] = regExp[i];
    }
    buildEpsilonTransitionDigraph();
}


void NFA::buildEpsilonTransitionDigraph() {
    Stack ops;
    for (unsigned int i = 0; i < numChars; i++) {
        unsigned int lp = i;
        if (re[i] == '(' || re[i] == '|') {
            ops.push(i);                                    // store index of left parantheses or OR character
        }
        else if (re[i] == ')') {                            // pop left parantheses or OR character if exists
            unsigned int or = ops.pop();                    // assume OR character, get its index
            if (re[or ] == '|') {                           
                lp = ops.pop();                             // if OR, then pop left parantheses position
                graph->addEdge(lp, or +1);                  // add directed edge from left parantheses to character immediately after OR
                graph->addEdge(or , i);                     // add directed edge from OR to right parantheses
            }
            else {                                          // if popped character was a left parantheses, then set accordingly
                lp = or;
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