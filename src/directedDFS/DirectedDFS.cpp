#include "DirectedDFS.h"


DirectedDFS::DirectedDFS(Digraph* g, unsigned int src) {
  marked = new bool[g->V()];
  for (unsigned int i = 0; i < g->V(); i++) {
    marked[i] = false;
  }
  dfs(g, src);
}


DirectedDFS::DirectedDFS(Digraph* g, const Bag<unsigned int>& srcs) {
  marked = new bool[g->V()];
  for (unsigned int i = 0; i < g->V(); i++) {
    marked[i] = false;
  }
  for (Bag<unsigned int>::iterator iter = srcs.begin(); iter != srcs.end(); iter++) {
    dfs(g, *iter);
  }
}


DirectedDFS::~DirectedDFS() {
  delete[] marked;
}


void DirectedDFS::dfs(Digraph* g, unsigned int v) {
  marked[v] = true;
  for (Bag<unsigned int>::iterator iter = g->adj(v).begin(); iter != g->adj(v).end(); iter++) {
    if (!marked[*iter]) {
      dfs(g, *iter);
    }
  }
}


bool DirectedDFS::visited(unsigned int v) const {
  return marked[v];
}