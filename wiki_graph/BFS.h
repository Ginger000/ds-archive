#pragma once

#include <string>
#include "Traversal.h"
#include <queue>

using std::string;

/**
 * A breadth-first wikipedia Graph.
 * Derived from base class Traversal
 */
class BFS : public Traversal {
 public:
  BFS(Graph *graph, string start);

  Traversal::Iterator begin();

  Traversal::Iterator end();

  void add(const string point);

  string pop();

  string peek();

  bool empty();

 protected:
  void push(string);

 private:
  std::queue<string> queue;
  const string start;
};

