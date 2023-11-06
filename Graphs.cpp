#include "Graphs.h"

Graphs::Graphs() {
  adjListGraph1.clear();
  adjListGraph2.clear();
  numNodes1 = 0;
  numEdges1 = 0;
  numNodes2 = 0;
  numEdges2 = 0;
  start = 0;
  end = 0;
}

Graphs::~Graphs() {
  adjListGraph1.clear();
  adjListGraph2.clear();
  numNodes1 = 0;
  numEdges1 = 0;
  numNodes2 = 0;
  numEdges2 = 0;
  start = 0;
  end = 0;
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
      start = res[2];
      end = res[3];
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

//El codigo se baso en el proporcionado por GeeksforGeeks y ademas de videos como apoyo
//de la misma logica

void Graphs::KruskalMST() {
  std::vector<std::pair<int, std::pair<int, int>>> edges;
  int contador = 0;

  for (int u = 0; u < numNodes1; u++) {
    for (const auto &edge : adjListGraph1[u]) {
      int v = edge.first;
      int weight = edge.second;
      edges.push_back({weight, {u, v}});
    }
  }

  // Ordenar el vector de aristas por peso en orden ascendente
  // Por si solo el contenedor sort ya tiene una complejidad O(nlogn)
  std::sort(edges.begin(), edges.end());

  std::vector<int> parent(numNodes1);
  for (int i = 0; i < numNodes1; i++) {
    parent[i] = i;
  }

  std::vector<std::pair<int, std::pair<int, int>>> mst;

  for (const auto &edge : edges) {
    int weight = edge.first;
    int u = edge.second.first;
    int v = edge.second.second;

    // Comprobar si agregar esta arista crea un ciclo en el MST actual
    int uParent = u;
    int vParent = v;

    while (parent[uParent] != uParent) {
      uParent = parent[uParent];
    }

    while (parent[vParent] != vParent) {
      vParent = parent[vParent];
    }

    if (uParent != vParent) {
      mst.push_back({weight, {u, v}});
      contador += weight;
      parent[uParent] = vParent;
    }
  }

  // Imprimir el MST resultante
  std::cout << "Problema 1" << std::endl;
  std::cout << "MST edges:" << std::endl;
  for (const auto &edge : mst) {
    int weight = edge.first;
    int u = edge.second.first;
    int v = edge.second.second;
    std::cout << "(" << u + 1 << ", " << v + 1 << ", " << weight << ")" << std::endl;
  }
  std::cout << "MST cost: " << contador << std::endl;
}

