#include "Graphs.h"

Graphs::Graphs() {
  adjListGraph1.clear();
  adjListGraph2.clear();
  numNodes1 = 0;
  numEdges1 = 0;
  numNodes2 = 0;
  numEdges2 = 0;
}

Graphs::~Graphs() {
  adjListGraph1.clear();
  adjListGraph2.clear();
  numNodes1 = 0;
  numEdges1 = 0;
  numNodes2 = 0;
  numEdges2 = 0;
}

void Graphs::split(std::string line, std::vector<int> &res) {
  size_t strPos = line.find(" ");
  size_t lastPos = 0;
  while (strPos != std::string::npos) {
    res.push_back(stoi(line.substr(lastPos, strPos - lastPos)));
    lastPos = strPos + 1;
    strPos = line.find(" ", lastPos);
  }
  res.push_back(stoi(line.substr(lastPos, line.size() - lastPos)));
}

void Graphs::readGraph(std::istream &input) {
  std::string line;
  int i = 0, j = 0, u, v, weight;
  bool isDirected = false;

  while (getline(input, line)) {
    if (i == 0) {
      i++;
      continue;
    }
    if (i == 1) {
      std::vector<int> res;
      split(line, res);
      numNodes1 = res[0];
      numEdges1 = res[1];
      adjListGraph1.resize(numNodes1);

      for (int k = 0; k < numNodes1; k++) {
        std::list<std::pair<int, int>> tmpList;
        adjListGraph1[k] = tmpList;
      }
      i++;
      continue;
    }

    if (i == numEdges1 + 2) {
      std::vector<int> res;
      split(line, res);
      numNodes2 = res[0];
      numEdges2 = res[1];
      adjListGraph2.resize(numNodes2);

      for (int k = 0; k < numNodes2; k++) {
        std::list<std::pair<int, int>> tmpList;
        adjListGraph2[k] = tmpList;
      }
      isDirected = true;
      i++;
      continue;
    }

    std::vector<int> res;
    split(line, res);

    if (isDirected == true) {
      u = res[0] - 1; // convierte nodo a cero-basado
      v = res[1] - 1; // convierte nodo a cero-basado
      weight = res[2];

      adjListGraph2[u].push_back(std::make_pair(v, weight));

    } else {
      u = res[0] - 1; // convierte nodo a cero-basado
      v = res[1] - 1; // convierte nodo a cero-basado
      weight = res[2];

      adjListGraph1[u].push_back(std::make_pair(v, weight));
      adjListGraph1[v].push_back(std::make_pair(u, weight));
    }
    i++;
  }
}

// Imprime grafo por vertice
void Graphs::print() {
  std::cout << "No dirigido" << std::endl;
  for (int u = 0; u < numNodes1; u++) {
    std::cout << "vertex " << u + 1 << ":"; // convierte nodo a uno-basado
    std::list<std::pair<int, int>> g = adjListGraph1[u];
    std::list<std::pair<int, int>>::iterator it;
    for (it = g.begin(); it != g.end(); ++it) {
      std::pair<int, int> par = *it;
      // convierte nodo a uno-basado
      std::cout << '\t' << "{" << par.first + 1 << "," << par.second << "}";
    }
    std::cout << std::endl;
  }

  std::cout << "Dirigido: " << std::endl;

  for (int u = 0; u < numNodes2; u++) {
    std::cout << "vertex " << u + 1 << ":"; // convierte nodo a uno-basado
    std::list<std::pair<int, int>> g = adjListGraph2[u];
    std::list<std::pair<int, int>>::iterator it;
    for (it = g.begin(); it != g.end(); ++it) {
      std::pair<int, int> par = *it;
      // convierte nodo a uno-basado
      std::cout << '\t' << "{" << par.first + 1 << "," << par.second << "}";
    }
    std::cout << std::endl;
  }
}
