#pragma once

#include "Traversal.h"
#include "heap/heap.h"

#include <vector>
#include <set>
#include <stack>
#include <string>

#include <limits>
#include <utility>
#include <algorithm>

#include <iostream>
#include <fstream>
#include <ctype.h>
#include <time.h>
#include <utility>

using std::string;
using std::vector;

/**
 * An implementation of Dijkstra's, modified to find the shortest path between two points.
 * Utilizes min priority queue (Implemented as heap) to achieve O(E log(V)) complexity.
 * Note that better runtime (O(E+VlogV)) is attainable via ues of a fibonacci heap.
 */
class Dijkstra {
 public:
  typedef std::pair<string, int> kvp;

  Dijkstra(Graph *graph);

  Dijkstra(Graph *graph, double (*weight)(string, string));

  void getPath(vector<string> &path, string start, string end);

  void setWeight(double (*weight)(string, string));

  void clearWeight();

 private:
  Graph *graph;

  double (*weight)(string, string);
};
