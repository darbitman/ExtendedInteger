#include "DirectedDFS.h"


/**
Run DirectedDFS on graph g, from source vertex src
*/
DirectedDFS::DirectedDFS(Digraph* g, unsigned int src) {
  if (LOGGER_VERBOSITY == Logger::LogLevel::Verbose) {
    std::string s = "Creating an instance of DirectedDFS with graph g and running DFS from source: ";
    s = s + std::to_string(src);
    Logger::getInstance().addEntry(s.c_str());
  }
  marked = new bool[g->V()];
  for (unsigned int i = 0; i < g->V(); i++) {
    marked[i] = false;
  }
  dfs(g, src);
}


/**
Run DirectedDFS on graph g, from source vertices srcs
*/
DirectedDFS::DirectedDFS(Digraph* g, const Bag<unsigned int>& srcs) {
  if (LOGGER_VERBOSITY == Logger::LogLevel::Verbose) {
    std::string s = "Creating an instance of DirectedDFS with graph g and running DFS from sources:";
    for (Bag<unsigned int>::iterator iter = srcs.begin(); iter != srcs.end(); iter++) {
      s = s + " " + std::to_string(*iter);
    }
    Logger::getInstance().addEntry(s.c_str());
  }
  marked = new bool[g->V()];
  for (unsigned int i = 0; i < g->V(); i++) {
    marked[i] = false;
  }
  for (Bag<unsigned int>::iterator iter = srcs.begin(); iter != srcs.end(); iter++) {
    dfs(g, *iter);
  }
}


DirectedDFS::~DirectedDFS() {
  if (LOGGER_VERBOSITY == Logger::LogLevel::Verbose) {
    std::string s = "DirectedDFS destructor called";
    Logger::getInstance().addEntry(s.c_str());
  }
  delete[] marked;
}

/**
Run recusrive depth first search on graph g, from vertex v
*/
void DirectedDFS::dfs(Digraph* g, unsigned int v) {
  if (LOGGER_VERBOSITY == Logger::LogLevel::Verbose) {
    std::string s = "Running recursive dfs function from vertex: ";
    s = s + std::to_string(v);
    Logger::getInstance().addEntry(s.c_str());
  }
  marked[v] = true;
  for (Bag<unsigned int>::iterator iter = g->adj(v).begin(); iter != g->adj(v).end(); iter++) {
    if (!marked[*iter]) {
      dfs(g, *iter);
    }
  }
}


/**
Returns true if vertex v marked
*/
bool DirectedDFS::visited(unsigned int v) const {
  if (LOGGER_VERBOSITY == Logger::LogLevel::Verbose) {
    std::string s = "Is vertex v marked?";
    s = s + std::to_string(v);
    Logger::getInstance().addEntry(s.c_str());
  }
  return marked[v];
}