#include "wiki_graph/Graph.h"
#include "wiki_graph/PageRank.h"
#include <iostream>
#include "util/util.h"

namespace opts {
bool help = false;
}

using std::string;
using std::endl;
using std::cout;

int main(int argc, const char **argv) {
  string inFile = "largeDatabase.txt";
  string output = "";
  string nOutput = "100";

  util::OptionsParser optsparse;
  optsparse.addArg(inFile);
  optsparse.addArg(nOutput);
  optsparse.addArg(output);
  optsparse.addOption("help", opts::help);
  optsparse.addOption("h", opts::help);
  optsparse.parse(argc, argv);
  if (opts::help) {
    cout << "Usage: " << argv[0]
         << " [input file] [max number of nodes to print (0 to print everything)] [output location (leave empty for console)]"
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

  PageRank prg(graph);

  int endIteration = std::stoi(nOutput);

  if (endIteration == 0) {
    endIteration = INT_MAX;
  }

  if (!output.empty()) {
    std::ofstream file;
    file.open(output);

    prg.saveRankToFile(output, endIteration);

    file.close();
  } else {
    prg.printRanks(endIteration);
  }

  return 0;
}
