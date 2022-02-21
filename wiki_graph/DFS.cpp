#include "DFS.h"

/**
 * Initializes a depth-first of the wikipedia graph start at `start`
 * @param graph The graph this DFS is going to traverse
 * @param start The starting point of this DFS
 */
DFS::DFS(Graph *graph, string start) : Traversal(graph, start) {
  // Passes intial values to the BFS
  stack.push(start);
}

/**
 * Returns an iterator for the traversal starting at the first vertex.
 */
Traversal::Iterator DFS::begin() {
  // Returns an iterator that represents the start
  return Traversal::Iterator(this);
}

/**
 * Returns an iterator for the traversal one past the end of the traversal.
 */
Traversal::Iterator DFS::end() {
  // Returns an iterator that represents the end
  return Traversal::Iterator();
}

/**
 * Adds a string vertex for the traversal to visit at some point in the future.
 * @param point the graph vertex to get the children from and add.
 */
void DFS::add(const string point) {
  // Gets the current children vertices from the directed graph
  std::vector<std::string> temp = getChildren(point);

  // Adds all the children the next stack
  for (auto i: temp)
    stack.push(i);
}

/**
 * Removes and returns the current vertex in the traversal.
 */
string DFS::pop() {
  // Get the top of the queue
  string top = stack.top();

  stack.pop();

  return top;
}

/**
 * Returns the current graph vertex in the traversal.
 */
string DFS::peek() {
  // Return nothing if empty otherwise print the front
  return empty() ? "" : stack.top();
}

/**
 * Returns true if the traversal is empty.
 */
bool DFS::empty() {
  // If there are no more vertices in the queue return true
  return stack.empty();
}

/**
 * Add a single element to the current stack (this is useful for when you have run out 
 * of vertices in the current component but there are still componenets left unexplored)
 *
 * @param push The element to add to the current queue
 */
void DFS::push(string push) {
  stack.push(push);
}
