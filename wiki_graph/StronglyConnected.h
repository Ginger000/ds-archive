#pragma once

#include "Graph.h"
#include <stack>
#include <string>
#include <unordered_set>
#include <vector>
#include "DFS.h"
#include <algorithm>

using std::string;

/**
 * A Kosaraju's implementation of the Strongly Connected graph. 
 * This implementation is similar to https://www.geeksforgeeks.org/strongly-connected-components/ and 
 * https://en.wikipedia.org/wiki/Kosaraju%27s_algorithm implementations
 */
class StronglyConnected {
 public:
  StronglyConnected(Graph *graph);

  ~StronglyConnected();

  std::vector<std::vector<string>> process();

  void printComponents(std::ostream &out = std::cout, int n = -1);

  void saveComponents(const string &str, int n = -1);

 private:
  Graph *graph;
  Graph *transpose;

  void traverse(string start, std::unordered_set<string> &visited, std::stack<string> &stack);

  void smallDFS(string start, std::unordered_set<string> &visited, std::vector<string> &fill);

  std::stack<string> stack;
};
