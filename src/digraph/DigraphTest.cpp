#include "Digraph.h"
#include <iostream>


int main() {
    Digraph* g = new Digraph(10);
    g->addEdge(0, 7);
    g->addEdge(0, 9);
    g->addEdge(0, 2);
    std::cout << g->adj(0).size() << std::endl;
    g->V();
    g->E();
    return 0;
}