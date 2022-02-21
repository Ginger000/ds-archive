/**
 * @file Graph.h
 *
 */

#pragma once

#include <string>
#include <vector>
#include <map>
#include <set>
#include <iterator>
#include <iostream>
#include <unordered_map>
#include <cmath>
#include <algorithm>
#include <sstream>
#include <fstream>
#include <unordered_set>

/**
 * Implementation Notes
 * Graph implemented as Adjacency List
 * Map used to keep track of weighted connection vectors
 * PRO:
 * - Should use O(|V|+|E|) space, vs. O(|V|^2) in the alternate adjacency matrix method.
 * - Easy to add to graph
 * CON:
 * - Checking adjacency between vertices is not efficient (worst case O(|V|))
 */
class Graph {
 public:
  Graph(std::string inputFile);

  Graph(std::unordered_map<std::string, std::pair<int, std::vector < std::string>>

  > wikiGraph);

  ~Graph();

  void insertVertex(std::string);

  void insertEdge(std::string from, std::string to);

  void removeVertex(std::string);

  void removeEdge(std::string from, std::string to);

  size_t size() const;

  size_t getDegree(const std::string &vertex) const;

  //Utility functions
  bool areAdjacent(std::string v1, std::string v2);

  void save(std::string outputFile);

  const std::unordered_map<std::string, std::pair<int, std::vector < std::string>>>

  getGraph();

  std::unordered_set<std::string> getVertices();

  const std::vector<std::string> getChildren(const std::string key);

  Graph *transpose();

 protected:
  // Helper methods here (consider rule of 3)
  void createGraph();

  const std::string inputFile;
  std::unordered_map<std::string, std::pair<int, std::vector < std::string>>>
  wikiGraph;

  friend class PageRank;

};
