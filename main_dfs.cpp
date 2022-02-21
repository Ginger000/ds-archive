#include "wiki_graph/Graph.h"
#include "wiki_graph/DFS.h"
#include <iostream>
#include <fstream>

#include "util/util.h"

namespace opts {
bool help = false;
}

void printDFS(std::ostream &stream, DFS &dfs, int maxIterations) {
  int i = 0;

  for (auto it = dfs.begin(); i < maxIterations && it != dfs.end(); ++it, ++i) {
    stream << i << ": " << *it << std::endl;
  }
}

int main(int argc, const char **argv) {
  string inFile = "largeDatabase.txt";
  string start = "Cheese";
  string nOutput = "100";
  string output = "";

  util::OptionsParser optsparse;
  optsparse.addArg(inFile);
  optsparse.addArg(start);
  optsparse.addArg(nOutput);
  optsparse.addArg(output);
  optsparse.addOption("help", opts::help);
  optsparse.addOption("h", opts::help);
  optsparse.parse(argc, argv);

  if (opts::help) {
    cout << "Usage: " << argv[0]
         << " [input file] [start point] [max number of nodes to traverse (0 to iterate through everything)] [output location (empty for console)]"
         << endl
         << "Usage (print to console):"
         << " largeDatabase.txt Cheese 100"
         << endl
         << "Usage (print to file):"
         << " largeDatabase.txt Cheese -1 output.txt"
         << endl;
    return 0;
  }

  Graph graph(inFile);

  DFS bfs(&graph, start);

  int endIteration = std::stoi(nOutput);

  if (endIteration == 0) {
    endIteration = INT_MAX;
  }

  if (!output.empty()) {
    std::ofstream file;
    file.open(output);

    printDFS(file, bfs, endIteration);

    file.close();
  } else {
    printDFS(std::cout, bfs, endIteration);
  }

  return 0;
}