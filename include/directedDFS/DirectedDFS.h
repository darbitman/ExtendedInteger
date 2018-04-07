#pragma once


#include "Digraph.h"


class DirectedDFS {
private:
    bool* marked;
    void dfs(Digraph* g, unsigned int v);            // recursive depth first search call
public:
    DirectedDFS(Digraph* g, unsigned int src);
    ~DirectedDFS();
    bool visited(unsigned int v) const;
};
