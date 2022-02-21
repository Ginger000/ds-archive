#include "StronglyConnected.h"

/**
 * Default StronglyConnected graph constrctor
 * 
 * @param g The graph to find the strongly connected components of.
 */
StronglyConnected::StronglyConnected(Graph *g) : graph(g), transpose(g->transpose()) {

}

/**
 * Destructor of the StronglyConnected object instance
 */
StronglyConnected::~StronglyConnected() {
  delete transpose;
}

/**
 * Return component groups listed by size in descending order
 */
std::vector<std::vector<string>> StronglyConnected::process() {
  std::stack<string> stack;

  // Empty set of visited nodes
  std::unordered_set<string> visited;

  string key;

  // Go through each of the nodes inside the graph
  for (auto elems: graph->getGraph()) {
    // Get the node key
    key = elems.first;

    // If the node has not been visited
    if (visited.find(key) == visited.end()) {
      // Run a DFS on the graph all the while updating the visited nodes and the stack starting at key
      traverse(key, visited, stack);
    }
  }

  // Clear all the visited nodes
  visited.clear();

  string v;

  std::vector<std::vector<string>> output;

  // Iterate through stack group until there is nothing left
  while (!stack.empty()) {
    // Get the current top of stack
    v = stack.top();
    stack.pop();

    // If the node has note been visited
    if (visited.find(v) == visited.end()) {
      std::vector<string> current;

      // Run a DFS on the transverse of the graph on the current node all the while updating
      // the visited set and the adding the visited nodes to the components list
      smallDFS(v, visited, current);

      // Add the component group
      output.push_back(current);
    }
  }

  // Sort the component groups by their sizes. The largest is first and the smallest size is last
  std::sort(output.begin(), output.end(),
            [](std::vector<string> x1, std::vector<string> x2) { return x1.size() > x2.size(); });

  return output;
}

/**
 * Implement a recursive DFS on the Graph all the while adding the values traversed in post order format.
 * Adds the nodes to the visited set.
 * 
 * @param start the current node to traverse in DFS format
 * @param visited the hashset of visited nodes
 * @param stack the stack of nodes added in post traverse format.
 */
void StronglyConnected::traverse(string start, std::unordered_set<string> &visited, std::stack<string> &stack) {
  // Flag the current node as visited
  visited.insert(start);

  // Go through all the child nodes of the child
  for (auto i: graph->getChildren(start)) {
    // Check if the node has not been visited
    if (visited.find(i) == visited.end()) {
      // Recurse DFS of the children
      traverse(i, visited, stack);
    }
  }

  // Add the current node to the stack
  stack.push(start);
}

/**
 * Implement a recursive DFS on the transpose of the Graph all the while adding the values traversed in pre order format.
 * Adds the nodes to the visited set.
 * This DFS adds all the elements to components vector making all the components in that vector strongly connected
 * 
 * @param start the current node to traverse in DFS format
 * @param visited the hashset of visited nodes
 * @param fill the current component to add the elements to.
 */
void StronglyConnected::smallDFS(string start, std::unordered_set<string> &visited, std::vector<string> &fill) {
  // Set the current node as visited
  visited.insert(start);

  // Add the current node to the current component vector
  fill.push_back(start);

  // Traverse the transpose graph in a recursive DFS fashion
  for (auto i: transpose->getChildren(start)) {
    if (visited.find(i) == visited.end()) {
      smallDFS(i, visited, fill);
    }
  }
}

/**
 * Processes and prints the component groups in this format:
 * 
 * index, (number of items): item1, item2, ....
 * 
 * @param outStream Where to print the data to. Default std::cout (console)
 * @param n Number of components to print out, -1 to print all
 */
void StronglyConnected::printComponents(std::ostream &outStream, int n) {

  // Process the graph data
  std::vector<std::vector<string>> out = process();

  outStream << "Connected Components:" << std::endl;

  int i = 0;
  // Go through each processed component and print it out
  for (auto &comp: out) {
    if (n != -1 && i >= n) {
      break;
    }

    outStream << i << ", (" << comp.size() << "): ";

    for (auto &e: comp) {
      outStream << e << ", ";
    }
    outStream << std::endl;
    outStream.flush();

    ++i;
  }
}

/**
 * Runs printComponents but outputs the data to a file
 * 
 * @param str the file name to output to
 * @param n Number of components to print out, -1 to print all
 */
void StronglyConnected::saveComponents(const string &str, int n) {
  // The file stream object
  std::ofstream file;

  // Creating/Opening the file
  file.open(str.c_str());

  // Run the printComponents for the processing and the printing
  printComponents(file, n);

  // Closing file in order o avoid leaks
  file.close();
}
