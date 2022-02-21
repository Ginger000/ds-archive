#include "../catch/catch.hpp"
#include "../wiki_graph/Graph.h"
#include <string>
#include "../wiki_graph/BFS.h"
#include "../wiki_graph/DFS.h"
#include "../wiki_graph/StronglyConnected.h"

TEST_CASE("Verify test compilation") {
  REQUIRE(true);
}

TEST_CASE("testReadGraph", "[Graph][timeout=4000]") {
  Graph graph("./tests/testDatabase.txt");

  REQUIRE(graph.size() == 9);

  std::unordered_map < std::string, std::pair < int, std::vector < std::string>>> expected;
  expected["0"].first = 1;
  expected["0"].second.push_back("3");

  expected["1"].first = 1;
  expected["1"].second.push_back("0");

  expected["2"].first = 1;
  expected["2"].second.push_back("1");

  expected["3"].first = 1;
  expected["3"].second.push_back("2");

  expected["4"].first = 2;
  expected["4"].second.push_back("2");
  expected["4"].second.push_back("6");

  expected["5"].first = 1;
  expected["5"].second.push_back("4");

  expected["6"].first = 2;
  expected["6"].second.push_back("5");

  expected["6"].second.push_back("7");

  expected["7"].first = 0;

  expected["8"].first = 1;
  expected["8"].second.push_back("7");

  REQUIRE(graph.getGraph() == expected);
}

TEST_CASE("testGraphTranspose", "[Graph][timeout=4000]") {
  Graph graph("./tests/testDatabase.txt");
  Graph *transpose = graph.transpose();

  std::unordered_map < std::string, std::pair < int, std::vector < std::string>>> expected;
  expected["0"].first = 1;
  expected["0"].second.push_back("1");

  expected["1"].first = 1;
  expected["1"].second.push_back("2");

  expected["2"].first = 2;
  expected["2"].second.push_back("4");
  expected["2"].second.push_back("3");

  expected["3"].first = 1;
  expected["3"].second.push_back("0");

  expected["4"].first = 1;
  expected["4"].second.push_back("5");

  expected["5"].first = 1;
  expected["5"].second.push_back("6");

  expected["6"].first = 1;
  expected["6"].second.push_back("4");

  expected["7"].first = 2;
  expected["7"].second.push_back("6");
  expected["7"].second.push_back("8");

  expected["8"].first = 0;

  REQUIRE(transpose->getGraph() == expected);

  delete transpose;
}

TEST_CASE("testGetChildren", "[Graph][timeout=4000]") {
  Graph graph("./tests/testDatabase.txt");

  std::unordered_map < std::string, std::pair < int, std::vector < std::string>>> expected;
  expected["0"].first = 1;
  expected["0"].second.push_back("3");

  expected["1"].first = 1;
  expected["1"].second.push_back("0");

  expected["2"].first = 1;
  expected["2"].second.push_back("1");

  expected["3"].first = 1;
  expected["3"].second.push_back("2");

  expected["4"].first = 2;
  expected["4"].second.push_back("2");
  expected["4"].second.push_back("6");

  expected["5"].first = 1;
  expected["5"].second.push_back("4");

  expected["6"].first = 2;
  expected["6"].second.push_back("5");

  expected["6"].second.push_back("7");

  expected["7"].first = 0;

  expected["8"].first = 1;
  expected["8"].second.push_back("7");

  for (auto &i : expected) {
    REQUIRE(graph.getChildren(i.first) == i.second.second);
  }

  REQUIRE(graph.getChildren("-1") == std::vector<std::string>());

}

TEST_CASE("testBFS", "[BFS][timeout=4000]") {
  Graph graph("./tests/testDatabase.txt");

  BFS bfs(&graph, "0");

  std::vector<string> expected = {"0", "3", "2", "1", "7", "5", "4", "6", "8"};

  std::vector<string> output;

  for (auto i = bfs.begin(); i != bfs.end(); ++i) {
    output.push_back(*i);
  }

  REQUIRE(expected == output);
}

TEST_CASE("testBFSSmall", "[BFS][timeout=4000]") {
  Graph graph("./tests/test-small.txt");

  BFS bfs(&graph, "a");

  std::vector<string> expected = {"a", "b", "c", "e"};

  std::vector<string> output;

  for (auto i = bfs.begin(); i != bfs.end(); ++i) {
    output.push_back(*i);
  }

  REQUIRE(expected == output);
}

TEST_CASE("testBFSMedium", "[BFS][timeout=4000]") {
  Graph graph("./tests/test-med.txt");

  BFS bfs(&graph, "alpha");

  std::vector<string> expected = {"alpha", "beta", "gamma", "lambda", "tau", "phi", "psi", "chi"};

  std::vector<string> output;

  for (auto i = bfs.begin(); i != bfs.end(); ++i) {
    output.push_back(*i);
  }

  REQUIRE(expected == output);
}

TEST_CASE("testDFS", "[DFS][timeout=4000]") {
  Graph graph("./tests/testDatabase.txt");

  DFS dfs(&graph, "4");

  std::vector<string> expected = {"4", "6", "7", "5", "2", "1", "0", "3", "8"};

  std::vector<string> output;

  for (auto i = dfs.begin(); i != dfs.end(); ++i) {
    output.push_back(*i);
  }

  REQUIRE(output == expected);
}

TEST_CASE("testDFSSmall", "[DFS][timeout=4000]") {
  Graph graph("./tests/test-small.txt");

  DFS dfs(&graph, "a");

  std::vector<string> expected = {"a", "b", "c", "e"};

  std::vector<string> output;

  for (auto i = dfs.begin(); i != dfs.end(); ++i) {
    output.push_back(*i);
  }

  REQUIRE(output == expected);
}

TEST_CASE("testDFSMedium", "[DFS][timeout=4000]") {
  Graph graph("./tests/test-med.txt");

  DFS dfs(&graph, "alpha");

  std::vector<string> expected = {"alpha", "tau", "chi", "lambda", "psi", "gamma", "phi", "beta"};

  std::vector<string> output;

  for (auto i = dfs.begin(); i != dfs.end(); ++i) {
    output.push_back(*i);
  }

  REQUIRE(output == expected);
}

TEST_CASE("testStronglyConnectedProcess", "[StronglyConnected][timeout=4000]") {
  Graph graph("./tests/testDatabase.txt");
  StronglyConnected connected(&graph);

  std::vector<std::vector<std::string>> connections = connected.process();

  std::vector<std::vector<std::string>> expected;

  std::vector<std::string> one;
  one.push_back("0");
  one.push_back("1");
  one.push_back("2");
  one.push_back("3");
  std::vector<std::string> two;
  two.push_back("4");
  two.push_back("5");
  two.push_back("6");
  std::vector<std::string> three;
  three.push_back("8");
  std::vector<std::string> four;
  four.push_back("7");

  expected.push_back(one);
  expected.push_back(two);
  expected.push_back(three);
  expected.push_back(four);

  REQUIRE(expected == connections);
}

TEST_CASE("testStronglyConnectedProcessSmall", "[StronglyConnected][timeout=4000]") {
  Graph graph("./tests/test-small.txt");
  StronglyConnected connected(&graph);

  std::vector<std::vector<std::string>> connections = connected.process();

  std::vector<std::vector<std::string>> expected;

  std::vector<std::string> one;
  one.push_back("e");
  std::vector<std::string> two;
  two.push_back("a");
  std::vector<std::string> three;
  three.push_back("b");
  std::vector<std::string> four;
  four.push_back("c");

  expected.push_back(one);
  expected.push_back(two);
  expected.push_back(three);
  expected.push_back(four);

  REQUIRE(expected == connections);
}

TEST_CASE("testStronglyConnectedProcessMed", "[StronglyConnected][timeout=4000]") {
  Graph graph("./tests/test-med.txt");
  StronglyConnected connected(&graph);

  std::vector<std::vector<std::string>> connections = connected.process();

  std::vector<std::vector<std::string>> expected;

  std::vector<std::string> one;
  one.push_back("alpha");
  one.push_back("lambda");
  one.push_back("beta");
  one.push_back("gamma");
  std::vector<std::string> two;
  two.push_back("tau");
  std::vector<std::string> three;
  three.push_back("psi");
  std::vector<std::string> four;
  four.push_back("chi");
  std::vector<std::string> five;
  five.push_back("phi");

  expected.push_back(one);
  expected.push_back(two);
  expected.push_back(three);
  expected.push_back(four);
  expected.push_back(five);

  REQUIRE(expected == connections);
}
