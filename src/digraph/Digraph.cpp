#include "Digraph.h"


Digraph::Digraph(unsigned int V) : totalVertices(V) {
    vertexArray = new Bag<unsigned int>[V];                // create an array of Bags
    totalVertices = V;
    totalEdges = 0;
}


Digraph::Digraph(const Digraph& rhs) {
    totalVertices = rhs.totalVertices;
    totalEdges = rhs.totalEdges;
    vertexArray = new Bag<unsigned int>[totalVertices];
    for (unsigned int i = 0; i < totalVertices; i++) {
        for (Bag<unsigned int>::iterator iter = vertexArray[i].begin(); iter != vertexArray[i].end(); iter++) {
            vertexArray[i].add(*iter);
        }
    }
}


Digraph::~Digraph() {
    delete[] vertexArray;
}


void Digraph::addEdge(unsigned int v, unsigned int w) {
    vertexArray[v].add(w);
}


Bag<unsigned int>& Digraph::adj(unsigned int v) {
    return vertexArray[v];
}


unsigned int Digraph::V() const {
    return totalVertices;
}


unsigned int Digraph::E() const {
    return totalEdges;
}