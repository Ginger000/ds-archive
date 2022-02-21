#pragma once

#include "Graph.h"
#include <string>
#include <unordered_set>
#include <vector>

using namespace std;

/**
 * A base class for traversal algorithms on wikipedia graphs.
 *
 * BFS, DFS will inherit from this class
 * 
 * A derived class provides a traversal by returning instances of
 * Traversal::Iterator.
 */
class Traversal {
 public:
  class Iterator {
   public:
    Iterator();

    Iterator(Traversal *traversal);

    Iterator &operator++();

    string &operator*();

    bool operator!=(const Iterator &other);

   private:
    Traversal *traversal;
    string current;
  };

  /**
   * The begining of an iterator
   * Virtual function. Derived class need to implement this
  */
  virtual Iterator begin() = 0;

  /**
   * The end of an iterator
   * Virtual function. Derived class need to implement this
   */
  virtual Iterator end() = 0;

  /**
   * Return but not remove the next node of the traversal
   * Virtual function. Derived class need to implement this
   */
  virtual string peek() = 0;

  /**
   * Remove and return the next node of the traversal
   * Virtual function. Derived class need to implement this
   */
  virtual string pop() = 0;

  /**
   * Add new node to the traversal
   * Virtual function. Derived class need to implement this
   */
  virtual void add(const string) = 0;

  /**
   * To see if the traversal has no nodes left
   * Virtual function. Derived class need to implement this
   */
  virtual bool empty() = 0;

  const std::vector<std::string> getChildren(const string key);

  Traversal(Graph *&graph, string start);

  string getFirstRemaining();

  bool hasRemaining();

  void removeRemaining(string);

 private:
  Graph *graph; // The graph to traverse
  const string startLink; // The starting node
  std::unordered_set<string> visited; //The nodes that have been visited
  void visit(string node);

  bool hasVisted(string node);

  std::unordered_set<string> remaining;

 protected:
  virtual void push(string) = 0;
};
