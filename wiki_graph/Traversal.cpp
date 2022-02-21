#include "Traversal.h"

/**
 * Default constructor for Traversal
 * 
 * @param graph the graph to traverse through
 * @param start the starting node of the traversal  
 */
Traversal::Traversal(Graph *&graph, string start) : graph(graph), startLink(start) {
  // Add all current nodes in graph to untraversed list
  remaining.reserve(graph->size());
  for (auto &i : graph->getGraph()) {
    remaining.insert(i.first);
  }
}

/**
 * Flags the node to have been visited
 * 
 * @param node the node to set as visited
 */
void Traversal::visit(string node) {
  visited.insert(node);
}

/**
 * Checks if the node has been visited already
 * 
 * @param node the node to check if it has been visited
 */
bool Traversal::hasVisted(string node) {
  return visited.find(node) != visited.end();
}

/**
 * Returns all the avaliable children of the key from the pass in Graph
 * 
 * @param key the node key to get the children from
 */
const std::vector<string> Traversal::getChildren(const string key) {
  return graph->getChildren(key);
}

/**
 * Default iterator constructor.
 */
Traversal::Iterator::Iterator() : traversal(NULL) {

}

/**
 * Iterator constructor for graph traversal
 * 
 * @param traversal The traversal function type to use to traverse through the graph
 */
Traversal::Iterator::Iterator(Traversal *traversal) : traversal(traversal) {
  current = traversal->peek();
}

/**
 * Iterator increment operator.
 *
 * Advances the traversal of the graph.
 */
Traversal::Iterator &Traversal::Iterator::operator++() {
  // If check if there is nothing left to traverse
  if (traversal->empty()) {
    // If there are still some untraversed nodes from another component
    if (traversal->hasRemaining()) {
      // Get the first untraversed node
      current = traversal->getFirstRemaining();
      // Add it to the traversal
      traversal->push(current);
    } else {
      // If there is absolutely nothing left to traverse you have finished and just return the current
      return *this;
    }
  }

  string c = current;

  // Remove the current node as we
  traversal->removeRemaining(c);

  // Add the children of the current node to be traversed next
  traversal->add(current);

  bool hasVisited;

  // Set the current node to be visited
  traversal->visit(current);

  do {
    // Check if there are still nodes to traverse
    if (traversal->empty()) {
      // If there are still some untraversed nodes from another component
      if (traversal->hasRemaining()) {
        // Get the first untraversed node
        c = traversal->getFirstRemaining();
        // Add it to the traversal
        traversal->push(c);
      } else {
        // If there is absolutely nothing left to traverse you have finished and just return the current
        return *this;
      }
    } else {
      // Get the current top node
      c = traversal->peek();
    }

    traversal->removeRemaining(c);

    // Check if node has been visited
    hasVisited = traversal->hasVisted(c);

    if (hasVisited) {
      // If it has been visted then remove it
      traversal->pop();
    }

    // Continue to search for an unvisited node
  } while (hasVisited);

  // Set the new current node
  current = traversal->peek();

  return *this;
}

/**
 * Iterator accessor opreator.
 *
 * Accesses the current wikipedia node in the Traversal.
 */
string &Traversal::Iterator::operator*() {
  return current;
}

/**
 * Iterator inequality operator.
 *
 * Determines if two iterators are not equal.
 *
 * @param other Comparison object
 */
bool Traversal::Iterator::operator!=(const Iterator &other) {
  bool thisEmpty = false;
  bool otherEmpty = false;

  if (traversal == NULL) { thisEmpty = true; }
  if (other.traversal == NULL) { otherEmpty = true; }

  if (!thisEmpty) { thisEmpty = traversal->empty(); }
  if (!otherEmpty) { otherEmpty = other.traversal->empty(); }

  if (thisEmpty && otherEmpty) return false; // both empty then the traversals are equal, return true
  else if ((!thisEmpty) && (!otherEmpty))
    return (traversal != other.traversal); //both not empty then compare the traversals
  else return true; // one is empty while the other is not, return true
}

/**
 * Return the first un traversed node
 */
string Traversal::getFirstRemaining() {
  return *remaining.begin();
}

/**
 * If this is empty then all the nodes have been traversed
 */
bool Traversal::hasRemaining() {
  return !remaining.empty();
}

/**
 * Remove this from the untravered nodes
 * @param key the node to remove
 */
void Traversal::removeRemaining(string key) {
  remaining.erase(key);
}
