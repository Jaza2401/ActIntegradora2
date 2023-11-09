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

//----------------------------------------------------------------------------------------------------------------------

}


struct nodo {
    int lb;

    std::vector<int> path;
};

struct PriorityQueueEntry {
    nodo piece;

    // Custom comparison function for the priority queue
    bool operator>(const PriorityQueueEntry& other) const {
        // Comparison for min-heap, based on the priority
        return piece.lb > other.piece.lb;
    }
};

//Revisa si ha sido visitado
bool visited(int indice, std::vector<int> visitados){

    std::vector<int>::iterator check = std::find(visitados.begin(),visitados.end(),indice);

    if (check != visitados.end()) {
        //std::cout << "visited" << std::endl;
        return true;
    }
    else {
        //std::cout << "not visited" << std::endl;
        return false;
    }
}

//Calcula CA (suma de distancias entre vertices visitados + actual)
int calculateCA(std::vector<int> visitados, std::vector<std::list<std::pair<int, int>>> adjList){

    int i = 0;
    int j = 1;
    int ca = 0;

    while (i < visitados.size() and j < visitados.size()){

        std::list<std::pair<int, int>> g = adjList[visitados[i]];
        std::list<std::pair<int, int>>::iterator it;
        for (it = g.begin(); it != g.end(); ++it) {
            std::pair<int, int> par = *it;

            if (par.first == visitados[j]){
                ca += par.second;

            }

        }
        i++;
        j++;

    }
    //std::cout << "ca: " << ca << std::endl;
    return ca;
}

//Calcula lower bound
int calculateLB(std::vector<std::list<std::pair<int, int>>> adjList, std::vector<int> visitados, int num){

    int lb = calculateCA(visitados, adjList);

    int lowest = 0;

    for (int u = 0; u < num ; u++) {

        if (u == visitados.back() or !visited(u,visitados)){
            //std::cout << "node: " << u << std::endl;
            std::list<std::pair<int, int>> g = adjList[u];
            std::list<std::pair<int, int>>::iterator it;
            for (it = g.begin(); it != g.end(); ++it) {
                std::pair<int, int> par = *it;

                if (par.first == visitados.back() and visitados.size() > 1) {
                //skip
                }
                else if (lowest == 0){
                    lowest = par.second;
                    //std::cout <<par.first << " first lowest: " << par.second << std::endl;
                }
                else if(lowest > par.second){
                    lowest = par.second;
                    //std::cout <<par.first << " lowest: " << par.second << std::endl;
                }

            }

        }
        //std::cout << " lb before: " << lb << std::endl;
        lb += lowest;
        //std::cout << " lb after: " << lb << std::endl << std::endl;
        lowest = 0;

    }
    return lb;
}





void Graphs::TSP() {

    //WE INITIALIZE THE PRIORITY QUEUE
    std::priority_queue<PriorityQueueEntry, std::vector<PriorityQueueEntry>, std::greater<PriorityQueueEntry>> pq;

    //INITIALIZED KEY VARIABLES
    int optCost = 10000000;
    int ca;
    int neoLb;
    std::vector<int> neoPath;
    std::vector<int> optPath;

    //WE CALCULATE THE INITIAL POSSIBLE COST
    int initialCost = calculateLB(adjListGraph1, {0}, numNodes1);

    //WE CREATE THE FIRST NODE AND PUSH IT INTO THE PRIORITY QUEUE
    nodo inicial({initialCost,{0}});

    pq.push({inicial});


    //THIS IS THE MAIN LOOP OF THE CODE, WERE AS LONG AS WE HAVE NODES IN THE PRIORITY QUEUE,
    //THEN WE STILL HAVE PATHS TO EXPLORE
    while (!pq.empty()){

        //WE SAVE THE TOP NODE OF THE PRIORITY QUEUE IN A TEMPORARY VARIABLE
        //AND THEN POP THE NODE FROM THE PRIORITY QUEUE
        nodo currNode = pq.top().piece;
        pq.pop();


        //WE CHECK IF THE LOWER BOUND OF THE NODE IS LOWER THAN THE CURRENT OPTIMAL
        //COST, THEN WE SHOULD LOOK INTO IT BECAUSE THERE IS THE POSSIBILITY IT
        //COULD GIVE US A BETTER OPTIMAL COST
        if (currNode.lb <= optCost){

            //WE IMPLEMENT A FOR ON THE ADJLIST OF THE INDEX OF THE NODE, WHICH
            //IS THE LAST INDEX IN THE LIST OF VISITED IN OUR NODE STRUCT.
            //WE DO THIS TO ACCESS ALL THE PATHS THAT CAN BE TAKEN FROM OUR CURRENT POINT
            std::list<std::pair<int, int>> g = adjListGraph1[currNode.path.back()];
            std::list<std::pair<int, int>>::iterator it;
            for (it = g.begin(); it != g.end(); ++it) {
                std::pair<int, int> par = *it;

                //WE CHECK IF THE NODE HAS BEEN VISITED BEFORE CHECKING WITH THE
                //VISITED LIST FROM THE NODE TO AVOID REPEATING NODES
                if (!visited(par.first, currNode.path)) {
                    //WE CREATE THE NEW NODE
                    neoPath = currNode.path;
                    neoPath.push_back(par.first);
                    neoLb = calculateLB(adjListGraph1, neoPath, numNodes1);
                    nodo neo({neoLb, neoPath});

                    //WE CHECK THE SIZE OF VISITED TO SEE IF WE ARE ON THE LAST STEP OF THE PATH
                    //SINCE THE PATH NEEDS TO GO THROUGH ALL THE NODES 1 TIME.
                    if (neoPath.size() == numNodes1){

                        //WE CHECK THE ADJLIST OF THE LAST INDEX IN THE PATH TO SEE IF IT CONNECTS
                        //TO THE FIRST INDEX, SINCE WE NEED IT TO START AND END IN THE SAME POINT
                        //FOR THE PATH TO BE ELIGIBLE
                        std::list<std::pair<int, int>> g = adjListGraph1[neoPath.back()];
                        std::list<std::pair<int, int>>::iterator it;
                        for (it = g.begin(); it != g.end(); ++it) {
                            std::pair<int, int> par = *it;

                            //CHECK IF FIRST INDEX IS CONNECTED TO THE LAST ONE
                            if (par.first == neoPath[0]){
                                neoPath.push_back(neoPath[0]);
                                //WE CALCULATE THE ACTUAL ACCUMULATED COST OF THIS PATH
                                ca = calculateCA(neoPath, adjListGraph1);
                                //WE UPDATE THE OPTIMAL COST AND PATH IF THE CA IS LOWER THAN THE
                                //OPTIMAL COST, GIVING US A BETTER PATH.
                                if (ca < optCost){

                                    optCost = ca;
                                    optPath = neoPath;

                                }

                            }

                        }
                    }
                    //WE PUSH THE NEW NODE TO THE PRIORITY QUEUE TO EXPLORE ITS REMAINING
                    //CHILDRENS LATER
                    else {
                        pq.push({neo});
                    }

                }
            }


        }
        //IN THIS CASE IF THE VALUE POPPED FROM THE PRIORITY QUEUE IS NOT LOWER THAN OPTIMAL COST,
        //THEN ALL THE REMAINING NODES INSIDE ARE HIGHER AND SHOULDNT BE EXPLORED ANYMORE SINCE WE WONT
        //GET A BETTER VALUE, SO WE EMPTY THE PRIORITY QUEUE.
        else {

            pq = {};
        }
    }

    //PRINTING THE FINAL RESULT
    std::cout << "Path: " << std::endl;
    for (int i = 0; i < optPath.size(); i++){
        std::cout << optPath[i] + 1 << " ";
    }
    std::cout << std::endl;
    std::cout << "Optimal cost: " << optCost << std::endl;



}
