#include "PageRank.h"

#define Max_Iteration (1000)
#define Default_Tolerence (10e-5)
#define Default_Alpha (0.85)

/**
 * Return Page Rank of a page.
 * 
 * @param vertex The vertex to get rank of
 */
double PageRank::getRank(std::string vertex) {
  return pageRank[vertex];
}

/**
 * Return Page Rank of all pages in an unordered_map.
 */
std::unordered_map<std::string, double> PageRank::getAllRank() {
  return pageRank;
}

/*
 * Default constructor of PageRank
 *
 * @param g the base graph 
 */
PageRank::PageRank(Graph &g) : PageRank(g, Default_Alpha, Default_Tolerence) {

}

/**
 * Customized constructor of PageRank
 * 
 * @param g the base graph 
 * @param alpha the dumping factor, representing the possibility for a user to keep browsing or open a new page
 * @param tol the tolerence for convergence
 */
PageRank::PageRank(Graph &g, double alpha, double tol) : graph(g) {
  constructDualGraph();
  calculateRank(alpha, tol);
}

/**
 * Created a new graph, based on the original one, with all arrows reversed.
 */
void PageRank::constructDualGraph() {
  std::unordered_set<std::string> vertices = graph.getVertices();
  dualWikiGraph.reserve(graph.size());
  for (auto source : vertices) {
    auto edges = graph.getChildren(source);
    for (auto &target : edges) {
      dualWikiGraph[target].second.push_back(source);
    }
  }
  for (auto &target : vertices) {
    std::pair<int, std::vector<std::string>> &children = dualWikiGraph[target];
    children.first = children.second.size();
  }
}

/**
 * Calculates pagerank of all pages. Page Rank is proportional to the posibility of a user browsing the wikipage via links in the page that stays at a particular webpage.
 * Iteratively, each page "votes" its rank to the pages that it has links pointing to, with a correction mimicing random browsing.
 *
 * @param alpha The dumping factor, representing the possibility for a user to keep browsing or open a new page
 * @param tol Tolerance for convergence.
 */

void PageRank::calculateRank(double alpha, double tol) {
  std::cout << "Start calculating Page Rank of the graph of size : " << graph.size() << std::endl;
  std::cout << "This may takes up to 1 minutes." << std::endl;

  auto vertices = graph.getVertices();

  pageRank.reserve(graph.size());

  // initalize the page rank, with all values = 1;
  auto buffer = pageRank;
  for (auto &vertex : vertices) {
    pageRank[vertex] = 1;
    buffer[vertex] = 0;
  }

  double differences = 1;
  int counter = 0;
  double totalCountOfVertices = (double) graph.size();


  // find all wiki page that has no links pointing outwards;
  std::unordered_set<std::string> leaves;
  leaves.reserve(graph.size());
  for (auto &vertex: vertices) {
    if (graph.getDegree(vertex) == 0) {
      leaves.emplace(vertex);
    }
  }

  // std::ofstream f;
  // f.open("testPageRank.txt");

  // page rank is calcualted iteratively, with each iteration representing the "voting" of possibilities of one page through its link pointing to others.
  // If a page has 3 links, it will contribute to the page rank of its children by dividing its rank into 3 even parts and adding them to the ranks of their children in the next iteration
  while (differences > tol && counter < Max_Iteration) {

    differences = 0;
    // the main "voting" procedure
    for (auto &vertex : vertices) {
      buffer[vertex] = 0;
      //f<<"Vertex :"<<vertex<<" has "<<dualWikiGraph[vertex].first<<" many parents"<<std::endl;
      auto parents = dualWikiGraph[vertex].second;
      for (auto &parent : parents) {
        double factor = graph.getDegree(parent);
        //f<<" "<<"It's parent : "<<parent<<" has "<<factor<<" many children."<<std::endl;
        buffer[vertex] += alpha * pageRank[parent] / factor;
      }
    }

    // corrections made to let leaf nodes spit out its rank, otherwise all non-leave pages will have rank 0
    double correction = 0;
    for (auto &leaf : leaves) {
      correction += pageRank[leaf] / totalCountOfVertices;
    }

    // corrections made to let the algorithms converge, with damping factor alpha.
    double sum = 0;
    for (auto &vertex :vertices) {
      sum += pageRank[vertex] / totalCountOfVertices;
    }

    // find the differences between two iterations for tolerence test
    for (auto &vertex : vertices) {
      buffer[vertex] = buffer[vertex] + alpha * correction + (1 - alpha) * sum;
      differences = std::max(differences, std::abs(pageRank[vertex] - buffer[vertex]));
    }

    pageRank = buffer;
    ++counter;
    std::cout << "Current iteration : " << counter << " with error :" << differences << std::endl;

    // f<<"Iterator : "<<counter<<", correction : "<<correction<<", sum : "<<sum<<std::endl;
    // for(auto& vertex : vertices){
    //     f<<vertex<<" has rank : "<<pageRank[vertex]<<std::endl;
    // }

  }

  //close();

  //convergency parameter
  iterations = counter;
  error = differences;
}

/**
 * Print rank to a file.
 * 
 * @param the output file name
 */
void PageRank::saveRankToFile(std::string output, int endIterationIdx) {
  std::ofstream f;
  f.open(output);
  auto vertices = graph.getVertices();
  int counter = 0;
  for (auto &vertex : vertices) {
    f << "The wiki page " << vertex << " has rank : " << pageRank[vertex] << ". " << std::endl;
    counter++;
    if (counter >= endIterationIdx) {
      break;
    }
  }
}

/**
 * Print rank to standard out.
 */
void PageRank::printRanks(int endIterationIdx) {
  std::cout << "Start printing page rank of all vertices :" << std::endl;

  auto vertices = graph.getVertices();
  int counter = 0;
  for (auto &vertex : vertices) {
    std::cout << "The rank of " << vertex << " is : " << pageRank[vertex] << ". " << std::endl;
    ++counter;
    if (counter >= endIterationIdx) {
      break;
    }
  }
}
