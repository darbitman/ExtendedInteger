#pragma once
#include "Digraph.h"


class DirectedDFS {
private:
  bool* marked;
  void dfs(Digraph* g, unsigned int v);             // recursive depth first search call
public:
  DirectedDFS(const DirectedDFS& rhs) = delete;     // forbid copy constructor
  DirectedDFS(Digraph* g, unsigned int src);
  DirectedDFS(Digraph* g, const Bag<unsigned int>& srcs);
  ~DirectedDFS();
  bool visited(unsigned int v) const;
};
