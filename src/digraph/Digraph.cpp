#include "Digraph.h"
#include "Logger.h"

/**
Create an empty digraph with V vertices
*/
Digraph::Digraph(unsigned int V): totalVertices(V) {
  if (LOGGER_VERBOSITY == Logger::LogLevel::Verbose) {
    std::string s = "Creating digraph with ";
    s = s + std::to_string(V) + " vertices";
    Logger::getInstance().addEntry(s.c_str());
  }
  vertexArray = new Bag<unsigned int>[V];                // create an array of Bags
  totalVertices = V;
  totalEdges = 0;
}


/**
Digraph copy constructor
*/
Digraph::Digraph(const Digraph& rhs) {
  if (LOGGER_VERBOSITY == Logger::LogLevel::Verbose) {
    std::string s = "Digraph copy constructor called";
    Logger::getInstance().addEntry(s.c_str());
  }
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
  if (LOGGER_VERBOSITY == Logger::LogLevel::Verbose) {
    std::string s = "Digraph destructor called";
    Logger::getInstance().addEntry(s.c_str());
  }
  delete[] vertexArray;
}


/**
Add edge from vertex v to vertex w
*/
void Digraph::addEdge(unsigned int v, unsigned int w) {
  if (LOGGER_VERBOSITY == Logger::LogLevel::Verbose) {
    std::string s = "Adding digraph edge: ";
    s = s + std::to_string(v) + "  ->  " + std::to_string(w);
    Logger::getInstance().addEntry(s.c_str());
  }
  vertexArray[v].add(w);
}


/**
Returns a bag of all the adjacent vertices to vertex v
*/
Bag<unsigned int>& Digraph::adj(unsigned int v) {
  if (LOGGER_VERBOSITY == Logger::LogLevel::Verbose) {
    std::string s = "Getting digraph's adjacency list from vertex: ";
    s = s + std::to_string(v);
    Logger::getInstance().addEntry(s.c_str());
  }
  return vertexArray[v];
}


/**
Returns the number of vertices
*/
unsigned int Digraph::V() const {
  if (LOGGER_VERBOSITY == Logger::LogLevel::Verbose) {
    std::string s = "Getting number of vertices in digraph";
    Logger::getInstance().addEntry(s.c_str());
  }
  return totalVertices;
}


/**
Returns the number of edges
*/
unsigned int Digraph::E() const {
  if (LOGGER_VERBOSITY == Logger::LogLevel::Verbose) {
    std::string s = "Getting number of edge in digraph";
    Logger::getInstance().addEntry(s.c_str());
  }
  return totalEdges;
}