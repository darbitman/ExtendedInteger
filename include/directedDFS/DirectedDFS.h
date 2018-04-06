#pragma once


#include "Digraph.h"


class DirectedDFS {
private:
    bool* marked;
    void dfs(Digraph* g, unsigned int v);            // recursive call
public:
    DirectedDFS(Digraph* g, unsigned int src);
    ~DirectedDFS();
};
