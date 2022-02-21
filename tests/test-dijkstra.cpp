#include "../catch/catch.hpp"
#include "../wiki_graph/Graph.h"
#include <iostream>
#include <string>
#include <vector>
#include "../wiki_graph/Dijkstra.h"

using std::vector;
using std::string;

/**
 * USAGE:
 * All dijkstra tests are flagged with [Dijkstra]
 */

/**
 * Compares result of dijkstra object's shortest path of vertices to expected shortest path of vertices
 */
void testShortestPath(Dijkstra *dij, string from, string to, vector<string> path) {

  vector<string> cur_path;
  dij->getPath(cur_path, from, to);

  REQUIRE(cur_path.size() == path.size());

  for (size_t i = 0; i < path.size(); i++) {
    REQUIRE(cur_path[i] == path[i]);
  }
}

/**
 * Run small test with time limit
 */
TEST_CASE("testDijkstraSmall", "[Dijkstra][timeout=2000]") {
  Graph g("./tests/test-small.txt");

  string from[] = {"a", "e", "a", "c"};
  string to[] = {"c", "c", "a", "b"};
  vector<string> path[] = {
      {"a", "b", "c"},
      {"e", "c"},
      {"a"},
      {"a"},
  };

  Dijkstra d = Dijkstra(&g);
  for (size_t i = 0; i < 3; i++) {
    testShortestPath(&d, from[i], to[i], path[i]);
  }
}

/**
 * Run medium test with time limit
 */
TEST_CASE("testDijkstraMed", "[Dijkstra][timeout=4000]") {
  Graph g("./tests/test-med.txt");

  string from[] = {"alpha", "lambda", "phi", "gamma"};
  string to[] = {"chi", "tau", "phi", "tau"};
  vector<string> path[] = {
      {"alpha", "tau", "chi",},
      {"lambda", "alpha", "tau",},
      {"phi"},
      {"gamma", "beta", "alpha", "tau",},
  };

  Dijkstra d = Dijkstra(&g);
  for (size_t i = 0; i < 3; i++) {
    testShortestPath(&d, from[i], to[i], path[i]);
  }
}

/**
 * Run small test on cyclic graph with time limit
 */
TEST_CASE("testDijkstraSelf", "[Dijkstra][timeout=4000]") {
  Graph g("./tests/test-self.txt");

  string from[] = {"a", "b", "a", "e"};
  string to[] = {"b", "a", "a", "b"};
  vector<string> path[] = {
      {"a", "b"},
      {"b", "a"},
      {"a"},
      {"e", "a", "b"},
  };

  Dijkstra d = Dijkstra(&g);
  for (size_t i = 0; i < 3; i++) {
    testShortestPath(&d, from[i], to[i], path[i]);
  }
}

// weight functions for use in custom weight function test
double testWeight1(string from, string to) {
  return (from == "lambda" && to == "psi") ? 999 : 1;
}

double testWeight2(string from, string to) {
  return ((from == "lambda" && to == "psi") || \
          (from == "alpha" && to == "tau")) ? 999 : 1;
}

/**
 * Test edge cases with custom weight functions
 */
TEST_CASE("testDijsktraWeight", "[Dijkstra][timeout=4000]") {
  Graph g("./tests/test-med.txt");

  string from[] = {"lambda", "lambda"};
  string to[] = {"chi", "chi"};
  vector<string> path[] = {
      {"lambda", "alpha", "tau", "chi"},
      {"lambda", "alpha", "gamma", "psi", "chi"},
  };
  double (*weights[])(string, string) = { &testWeight1, &testWeight2 };

  Dijkstra d = Dijkstra(&g);
  for (size_t i = 0; i < 2; i++) {
    d.setWeight(weights[i]);
    testShortestPath(&d, from[i], to[i], path[i]);
  }
}
