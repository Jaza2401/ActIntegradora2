#ifndef _GRAPHS_H_
#define _GRAPHS_H_

#include <algorithm>
#include <climits>
#include <iostream>
#include <list>
#include <queue>
#include <set>
#include <string>
#include <utility>
#include <vector>

class Graphs {
private:
  int numNodes1, numEdges1, numNodes2, numEdges2, start, end;

  // vector de listas ligadas de pares (vertice, peso)
  std::vector<std::list<std::pair<int, int>>> adjListGraph1;
  std::vector<std::list<std::pair<int, int>>> adjListGraph2;

  void split(std::string line, std::vector<int> &res);

  std::vector<std::list<std::pair<std::pair<int, int>, std::pair<int, int>>>>
      levelGraph;
  std::vector<int> level;

public:
  Graphs();
  ~Graphs();
  void readGraph(std::istream &input);
  void print();
  void KruskalMST();
  void DinicsMaxFlow();
  int dfs(int, int, std::vector<std::list<std::pair<int, int>>> &rg);
};

#endif // _GRAPHS_H_
