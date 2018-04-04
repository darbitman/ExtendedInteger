#ifndef _EXTENDEDINT_H_
#define _EXTENDEDINT_H_

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
    void addEdge(unsigned int v, unsigned int w);       // add edge (v --> w)

};

#endif