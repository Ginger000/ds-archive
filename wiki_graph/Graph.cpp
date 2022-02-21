#include "Graph.h"

/**
 * Create graph from data in file
 *
 * @param inputFile File to read graph data from
 */
Graph::Graph(std::string inputFile) : inputFile(inputFile) {
  createGraph();
}

/**
 * Default constructor for graph
 */
Graph::Graph(std::unordered_map < std::string, std::pair < int, std::vector < std::string
>>> wikiGraph) : inputFile("") ,
wikiGraph(wikiGraph) {

}

/**
 * Applies matrix transpose to graph adjacency matrix
 */
Graph *Graph::transpose() {
  std::unordered_map < std::string, std::pair < int, std::vector < std::string>>> transposed;
  transposed.reserve(wikiGraph.size());

  for (auto &elem : wikiGraph) {
    if (transposed.find(elem.first) == transposed.end()) {
      transposed[elem.first].first = 0;
    }

    for (auto &child: elem.second.second) {
      transposed[child].second.push_back(elem.first);
      ++transposed[child].first;
    }
  }

  return new Graph(transposed);
}

/**
 * Default destructor for graph
 */
Graph::~Graph() {
  /* Do nothing */
}

/**
 * Returns graph data as unordered map
 */
const std::unordered_map<std::string, std::pair<int, std::vector < std::string>>>

Graph::getGraph() {
  return wikiGraph;
}

/**
 * Return all vertices in graph
 */
std::unordered_set<std::string> Graph::getVertices() {
  std::unordered_set<std::string> all;
  all.reserve(size());

  for (auto const &pair : wikiGraph) {
    all.insert(pair.first);
  }
  return all;
}

/**
 * Parse input file, and create an unordered map
 */
void Graph::createGraph() {
  std::ifstream file(inputFile);

  std::string key, num, line, temp, totalLines;

  getline(file, totalLines);

  wikiGraph.clear();
  wikiGraph.reserve(std::stoi(totalLines));

  while (getline(file, line)) {
    std::stringstream ss(line);

    getline(ss, key, ',');
    getline(ss, num, ',');

    wikiGraph[key].first = std::stoi(num);
    wikiGraph[key].second.reserve(wikiGraph[key].first);

    //temp represents every string in the value vector of strings
    while (getline(ss, temp, ',')) {
      wikiGraph[key].second.push_back(temp);

      if (wikiGraph.find(temp) == wikiGraph.end()) {
        wikiGraph[temp].first = 0;
      }
    }
  }

}

/**
 * Insert vertex into graph
 *
 * @param key Vertex value
 */
void Graph::insertVertex(std::string key) {
  wikiGraph[key].first = 0;
}

/**
 * Insert edge between two vertices in graph
 *
 * @param from The vertex the edge exits from
 * @param to The vertex the edge enters
 */
void Graph::insertEdge(std::string from, std::string to) {
  wikiGraph[from].second.push_back(to);
}

/**
 * Return direct children of vertex in graph
 *
 * @param key Vertex to find children of
 */
const std::vector<std::string> Graph::getChildren(const std::string key) {
  if (wikiGraph.find(key) == wikiGraph.end()) {
    return std::vector<std::string>();
  }

  return wikiGraph[key].second;
}

/**
 * Return number of non-leaf vertices in graph
 */
size_t Graph::size() const {
  return wikiGraph.size();
}

/**
 * Return degree of vertex
 */
size_t Graph::getDegree(const std::string &vertex) const {
  return wikiGraph.at(vertex).first;
}
