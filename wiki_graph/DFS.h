#pragma once

#include <string>
#include "Traversal.h"
#include <stack>

using std::string;

/**
 * A Depth-first wikipedia Graph.
 * Derived from base class Traversal
 */
class DFS : public Traversal {
 public:
  DFS(Graph *graph, string start);

  Traversal::Iterator begin();

  Traversal::Iterator end();

  void add(const string point);

  string pop();

  string peek();

  bool empty();

 protected:
  void push(string);

 private:
  std::stack<string> stack;
  const string start;
};

