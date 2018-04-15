#pragma once
#include "Bag.h"


class Digraph {
private:
  unsigned int totalVertices;
  unsigned int totalEdges;
  Bag<unsigned int>* vertexArray;
public:
  Digraph(unsigned int V);                        // construct new Digraph with total number of vertices V
  Digraph(const Digraph& rhs);
  ~Digraph();
  void addEdge(unsigned int v, unsigned int w);   // add edge (v --> w)
  Bag<unsigned int>& adj(unsigned int v);         // return a bag of adjacent vertices to vertex v
  unsigned int V() const;								          // return number of vertices
  unsigned int E() const;                         // return number of edges
};
