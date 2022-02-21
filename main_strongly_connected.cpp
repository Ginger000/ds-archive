#include "wiki_graph/Graph.h"
#include "wiki_graph/StronglyConnected.h"
#include <iostream>

#include "util/util.h"

namespace opts {
bool help = false;
}

int main(int argc, const char **argv) {
  string inFile = "largeDatabase.txt";
  string nOutput = "0";
  string output = "";

  util::OptionsParser optsparse;
  optsparse.addArg(inFile);
  optsparse.addArg(nOutput);
  optsparse.addArg(output);
  optsparse.addOption("help", opts::help);
  optsparse.addOption("h", opts::help);
  optsparse.parse(argc, argv);

  if (opts::help) {
    cout << "Usage: " << argv[0]
         << " [input file] [n largest (0 for everything)] [output location (leave empty for console)]"
         << endl
         << "Usage (print to console):"
         << " largeDatabase.txt"
         << endl
         << "Usage (print to file):"
         << " largeDatabase.txt 10 output.txt"
         << endl;
    return 0;
  }

  Graph graph(inFile);

  StronglyConnected stronglyConnected(&graph);

  int n = std::stoi(nOutput);

  if (n == 0) {
    n = -1;
  }

  if (output.empty()) {
    stronglyConnected.printComponents(std::cout, n);
  } else {
    stronglyConnected.saveComponents(output, n);
  }

  return 0;
}