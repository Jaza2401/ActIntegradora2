#ifndef _GRAPHS_H_
#define _GRAPHS_H_

#include <iostream>
#include <list>
#include <string>
#include <utility>
#include <vector>
#include <queue>
#include <algorithm>

class Graphs {
private:
  int numNodes1, numEdges1, numNodes2, numEdges2, start, end;

  // vector de listas ligadas de pares (vertice, peso)
  std::vector<std::list<std::pair<int, int>>> adjListGraph1;
  std::vector<std::list<std::pair<int, int>>> adjListGraph2;

  void split(std::string line, std::vector<int> &res);

public:
  Graphs();
  ~Graphs();
  void readGraph(std::istream &input);
  void print();
  void TSP();
};

#endif // _GRAPHS_H_
