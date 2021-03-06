#include "DirectedDFS.h"
#include <iostream>


int main() {
    Digraph g(10);
    g.addEdge(0, 1);
    g.addEdge(0, 5);
    g.addEdge(7, 9);
    Bag<unsigned int> match;
    match.add(2);
    match.add(6);
    DirectedDFS dfs(&g, match);
    match.add(7);
    return 0;
}