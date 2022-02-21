#pragma once

#include "Graph.h"
#include <unordered_set>

/*
 * Using Page Rank algorithm to calculate the weights of the edges. 
 */
class PageRank {
 public:
  double getRank(std::string link);

  PageRank(Graph &g);

  PageRank(Graph &g, double alpha, double tol);

  std::pair<int, double> precision() { return std::pair<int, double>(iterations, error); }

  double operator[](std::string link) { return pageRank[link]; }

  std::unordered_map<std::string, double> getAllRank();

  void saveRankToFile(std::string output, int endIterationIdx);

  void printRanks(int endIterationIdx);

 private:
  void constructDualGraph();

  void calculateRank(double alpha, double tol);

  Graph &graph;
  size_t iterations;
  double error;
  std::unordered_map<std::string, std::pair<int, std::vector < std::string>>>
  dualWikiGraph;
  std::unordered_map<std::string, double> pageRank;
};
