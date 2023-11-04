#ifndef _GRAPHS_H_
#define _GRAPHS_H_

#include <iostream>
#include <list>
#include <string>
#include <utility>
#include <vector>

class Graphs {
private:
  int numNodes1;
  int numEdges1;
  int numNodes2;
  int numEdges2;

  // vector de listas ligadas de pares (vertice, peso)
  std::vector<std::list<std::pair<int, int>>> adjListGraph1;
  std::vector<std::list<std::pair<int, int>>> adjListGraph2;

  void split(std::string line, std::vector<int> &res);

public:
  Graphs();
  ~Graphs();
  void readGraph(std::istream &input);
  void print();
};

#endif // _GRAPHS_H_
