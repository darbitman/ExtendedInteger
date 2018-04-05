#ifndef _NFA_H_
#define _NFA_H_

#include "Digraph.h"
#include "Stack.h"

class NFA {
private:
    Digraph* graph;
public:
    NFA(const char* regExp, unsigned int numChars);
};

#endif