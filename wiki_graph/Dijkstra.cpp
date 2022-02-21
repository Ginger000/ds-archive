#include "Dijkstra.h"

/**
 * Initializes iterable traversal of the shortest path between a start and end vertex. Uses Dijkstra's algorithm to find shortest path.
 * 
 * @param g The graph to traverse
 * @param start The source vertex for Dijsktra's algorithm
 * @param end The target vertex
 */
Dijkstra::Dijkstra(Graph *graph) : graph(graph), weight(nullptr) {
  /* Nothing here */
}

/**
 * Constructor that takes pointer to custom weight function
 * 
 * @param g The graph to traverse
 * @param start The source vertex for Dijsktra's algorithm
 * @param end The target vertex
 * @param weight Function pointer for weighting function based on article key
 */
Dijkstra::Dijkstra(Graph *graph, double (*weight)(string, string)) : graph(graph), weight(*weight) {
  /* Nothing here */
}

/** 
 * Returns list of vertices comprising the shortest path between two vertices, in order of traversal 
 *
 * @param g The graph to traverse
 * @param start The source vertex for Dijsktra's algorithm
 * @param end The target vertex
 */
void Dijkstra::getPath(vector<string> &path, string start, string end) {
  const int n = graph->size();

  // Create vector to help with min priority queue constructor
  std::vector<kvp> init;
  init.reserve(n);

  // Create map of distances between start and vertices that can be accessed in O(1)
  std::unordered_map<string, double> dist;

  // Create map storing vertices and their direct predecessor according to Dijkstra's
  //Used to recover shortest path as a sequence of vertices.
  std::unordered_map<string, string> parent;

  // Initialize distance, parent map values
  const auto &all = graph->getVertices();
  for (string v : all) {
    parent[v] = ""; // Predecessor not known

    if (v == start)
      dist[v] = 0; // Mindist(X,X) = 0 for all vertices X
    else
      dist[v] = INT_MAX; // Unknown distance

    init.push_back(kvp(v, dist[v])); // Indirectly adding to priority queue
  }

  // Pair comparison functor use by minheap
  // By default pairs compare lexicographically with both first and second values
  struct comp {
    bool operator()(const kvp &lhs, const kvp &rhs) const {
      return lhs.second < rhs.second;
    }
  };

  // Finally, create min priority queue using helper vector
  heap<kvp, comp> minheap(init);

  // Main loop
  while (!minheap.empty()) {

    // Return and remove best vertex (based on distance)
    kvp min = minheap.pop();

    // Exit loop upon reaching target vertex
    if (min.first == end) {
      break;
    }

    // Visit all adjacent vertices
    std::vector<string> adj = graph->getChildren(min.first);
    double weight = 1.0 / ((double) adj.size() +
        1.0); // Use number of children for weight, to prioritize less link-heavy articles
    for (string vtx : adj) {
      if (this->weight != nullptr) {
        weight = this->weight(min.first, vtx);
      }

      // If comparison with current best is nontrivial and adjacent vertex is untravelled thus far
      if (dist[min.first] != INT_MAX && \
          weight + dist[min.first] < dist[vtx]) {

        // Update distance map, priority queue
        dist[vtx] = dist[min.first] + weight;
        minheap.push(kvp(vtx, dist[vtx]));

        // Update parent map
        parent[vtx] = min.first;
      }
    }
  }

  // Recover vertices of shortest path
  string tmp = end;
  while (tmp != "") {
    path.insert(path.begin(), tmp); // Store shortest path in object stack, used for iterator
    tmp = parent[tmp];
  }

  // Return nothing
}

/**
 * Set a new weight function for Dijkstra object
 *
 * @param weight Function pointer for weighting function based on article key
 */
void Dijkstra::setWeight(double (*weight)(string, string)) {
  this->weight = (*weight);
}

/**
 * Reset weight function for Dijsktra object to default
 */
void Dijkstra::clearWeight() {
  this->weight = nullptr;
}
