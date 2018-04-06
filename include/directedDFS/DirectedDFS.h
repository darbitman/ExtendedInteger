#pragma once

class DirectedDFS {
private:
    bool* marked;
    void dfs(Digraph G, unsigned int v);            // recursive call
public:
    DirectedDFS(Digraph* G, unsigned int src);
    ~DirectedDFS();
};
