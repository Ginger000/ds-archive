#include "../catch/catch.hpp"
#include "../wiki_graph/Graph.h"
#include "../wiki_graph/PageRank.h"

#include <string>

#define TOL (10e-4)

static double mapDiff(std::unordered_map<std::string, double> &map1, std::unordered_map<std::string, double> &map2) {
  double differences = 0;
  for (auto &pair : map1) {
    std::string vertex = pair.first;
    differences = std::max(differences, std::abs(map1.at(vertex) - map2.at(vertex)));
  }
  return differences;
}

TEST_CASE("testPageRankMini", "[PageRank]") {
  Graph g("./tests/testMiniWiki.txt");
  PageRank prg(g);
  auto allRank = prg.getAllRank();
  std::unordered_map<std::string, double> expected;
  expected["Cheese"] = 0.8484;
  expected["One"] = 1.2273;
  expected["Two"] = 0.8613;
  expected["Five"] = 1.2145;
  expected["Size"] = 0.8484;
  double differences = mapDiff(expected, allRank);
  REQUIRE(differences < TOL);
}

TEST_CASE("testPageRankSmall", "[PageRank]") {
  Graph g("./tests/testDatabase.txt");
  PageRank prg(g);
  auto allRank = prg.getAllRank();
  std::unordered_map<std::string, double> expected;

  expected["0"] = 1.6902;
  expected["1"] = 1.7501;
  expected["2"] = 1.8208;
  expected["3"] = 1.6392;
  expected["4"] = 0.5291;
  expected["5"] = 0.3842;
  expected["6"] = 0.4274;
  expected["7"] = 0.5564;
  expected["8"] = 0.2025;
  double differences = mapDiff(expected, allRank);
  REQUIRE(differences < TOL);
}


