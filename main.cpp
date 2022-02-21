#include "wiki_graph/Graph.h"
#include "wiki_graph/Dijkstra.h"
#include "wiki_graph/PageRank.h"
#include <iostream>
#include "wiki_graph/BFS.h"
#include "wiki_graph/DFS.h"
#include "wiki_graph/StronglyConnected.h"

double weight(std::string s) { return 2.0; }

int main() {

  std::cout << "Hello" << std::endl;

  Graph g("database.txt");

  string targets[] = {
      "French_language", "Yunnan",
  };

  for (string target : targets) {
    auto d = Dijkstra(&g, &weight);

    std::vector<std::string> path;
    d.getPath(path, "Cheese", target);

    for (auto it : path) {
      std::cout << it << "->";
    }
    std::cout << "END" << std::endl;
  }




  /* test pageRank
  Graph g ("testDatabase.txt");
  ofstream f;
  f.open("testPageRank.txt");
  PageRank prg(g);
  for(auto & elem: g.getGraph()){
    string key = elem.first;
    std::vector<string> children = elem.second.second;
    f<<key<<" has rank : "<<prg[key]<<endl;
  }
  f.close();
*/

  // cout<<prg.precision().first<<" "<<prg.precision().second<<endl;


  // Graph g ("testDatabase.txt");

  // std::cout << g.getGraph().size() << std::endl;

  // auto d = Dijkstra(&g, "Cheese", "Size");

  // Graph* transpose = g.transpose();

  // BFS bfs(transpose, "Five");

  // auto it = bfs.begin();

  // for(auto i = 0; it != bfs.end() && i < 100; ++i, ++it){
  //   std::cout << *it << std::endl;
  // }

  // delete transpose;

  // StronglyConnected connected(&g);
  // connected.printComponents();

  return 0;
}
