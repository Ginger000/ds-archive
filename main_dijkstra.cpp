#include "wiki_graph/Graph.h"
#include "wiki_graph/Dijkstra.h"
#include <iostream>
#include <fstream>

#include "util/util.h"

namespace opts {
bool help = false;
}

void printDijkstra(std::ostream &stream, std::vector<std::string> path) {
  for (auto it : path) {
    stream << it << "->";
  }
  stream << "END" << std::endl;
}

int main(int argc, const char **argv) {
  string inFile = "largeDatabase.txt";
  string start = "Cheese";
  string end = "Cheese";
  string output = "";

  util::OptionsParser optsparse;
  optsparse.addArg(inFile);
  optsparse.addArg(start);
  optsparse.addArg(end);
  optsparse.addArg(output);
  optsparse.addOption("help", opts::help);
  optsparse.addOption("h", opts::help);
  optsparse.parse(argc, argv);

  if (opts::help) {
    cout << "Usage: " << argv[0]
         << " [input file] [start] [end] [output location (empty for console)]"
         << endl
         << "Usage (print to console):"
         << " largeDatabase.txt Cheese Cheese"
         << endl
         << "Usage (print to file):"
         << " largeDatabase.txt Cheese Cheese output.txt"
         << endl;
    return 0;
  }

  Graph graph(inFile);

  Dijkstra d(&graph);

  std::vector<std::string> path;
  d.getPath(path, start, end);

  if (!output.empty()) {
    std::ofstream file;
    file.open(output);

    printDijkstra(file, path);

    file.close();
  } else {
    printDijkstra(std::cout, path);
  }

  return 0;
}
