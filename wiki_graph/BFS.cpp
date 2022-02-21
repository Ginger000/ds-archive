#include "BFS.h"

/**
 * Initializes a breadth-first of the wikipedia graph start at `start`
 * @param graph The graph this BFS is going to traverse
 * @param start The start point of this BFS
 */
BFS::BFS(Graph *graph, string start) : Traversal(graph, start) {
  // Passes intial values to the BFS
  queue.push(start);
}

/**
 * Returns an iterator for the traversal starting at the first point.
 */
Traversal::Iterator BFS::begin() {
  // Returns an iterator that represents the start
  return Traversal::Iterator(this);
}

/**
 * Returns an iterator for the traversal one past the end of the traversal.
 */
Traversal::Iterator BFS::end() {
  // Returns an iterator that represents the end
  return Traversal::Iterator();
}

/**
 * Adds a string vertex for the traversal to visit at some point in the future.
 * @param point the graph vertex point to get the children from and add.
 */
void BFS::add(const string point) {
  // Gets the current children vertices from the directed graph
  std::vector<std::string> temp = getChildren(point);

  // Adds all the children the next queue
  for (auto i: temp)
    queue.push(i);
}

/**
 * Removes and returns the current Point in the traversal.
 */
string BFS::pop() {
  // Get the top of the queue
  string top = queue.front();

  queue.pop();

  return top;
}

/**
 * Returns the current graph vertex in the traversal.
 */
string BFS::peek() {
  // Return nothing if empty otherwise print the front
  return empty() ? "" : queue.front();
}

/**
 * Returns true if the traversal is empty.
 */
bool BFS::empty() {
  // If there are no more vertices in the queue return true
  return queue.empty();
}

/**
 * Add a single element to the current queue (this is useful for when you have run out 
 * of vertices in the current component but there are still componenets left unexplored)
 *
 * @param push The element to add to the current queue
 */
void BFS::push(string push) {
  queue.push(push);
}
