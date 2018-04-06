#pragma once

class Digraph {
private:
    unsigned int totalVertices;
    struct Vertex {
        unsigned int vertexNum;
        Vertex* nextVertexPtr;
        Vertex* lastVertexPtr;
    };
    Vertex** vertexPtrArray;
public:
    Digraph(unsigned int V);                            // construct new Digraph with total number of vertices V
    ~Digraph();
    void addEdge(unsigned int v, unsigned int w);       // add edge (v --> w)
    unsigned int V() const;								// return number of Vertices
};
