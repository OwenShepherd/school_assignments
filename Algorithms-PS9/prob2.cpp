#include <iostream>

struct edge;

struct vertex {
  vertex* prev; // The previous vertex
  bool visited;
  int dist; // The distance
  int counter;
  int connector;
};

struct edge {
  vertex* head;
  vertex* tail;
  int weight;
  int number;
};

edge * CreateGraph(int *weights) {
  edge * edges = (edge*)malloc(sizeof(edge)*12);

  for (int x = 0; x < 12; x++) {
    edges[x].weight = weights[x];
    edges[x].number = x;
  }

  return edges;

}

int * FindSSSP(vertex * start, edge * edges, vertex * vertices, int * numEdge) {
  (*start).dist = 0;

  int * ssEdges = (int*)malloc(sizeof(int)*12);
  int numSS = 0;


  // Next node to check
  vertex * tempNode = nullptr;
  vertex * nextNode = start;
  int min = 999;

  while (nextNode != nullptr) {
    //std::cout<<(*nextNode).counter<< "\n";
    for (int i = 0; i < 12; i++) {
      if (edges[i].head == nextNode) {
        vertex * newNode = edges[i].tail;
        int newDist = (*nextNode).dist + edges[i].weight;

        if (newDist < (*newNode).dist) {
          (*newNode).dist = newDist;
          (*newNode).prev = nextNode;
          (*newNode).connector = edges[i].number;
        }

      }

      if (edges[i].tail == nextNode) {
        vertex * newNode = edges[i].head;
        int newDist = (*nextNode).dist + edges[i].weight;

        if (newDist < (*newNode).dist) {
          (*newNode).dist = newDist;
          (*newNode).prev = nextNode;
          (*newNode).connector = edges[i].number;
        }
      }




    }

    min = 999;
    (*nextNode).visited = true;
    if (nextNode != start) {
      ssEdges[numSS] = (*nextNode).connector;
      numSS++;
    }

    nextNode = nullptr;
    int a;
    for (int i = 0; i < 7; i++) {
      if (((vertices[i].dist) < min) && (!(vertices[i].visited))) {
        nextNode = &(vertices[i]);
        min = vertices[i].dist;

      }
      //std::cout<<"Node: "<<vertices[i].counter<<"; Dist: "<<vertices[i].dist<<"\n";
    }
    //std::cout<<"Next Node: "<<(*nextNode).counter;
    //std::cin>>a;





  }
  *numEdge = numSS;
  //std::cout<<ssEdges<<"\n";
  for (int i = 0; i < numSS; i++) {
    std::cout<<ssEdges[i]<<std::endl;
  }
  return ssEdges;

}


int main() {
  int numNodes = 7; // Number of nodes in the graph
  int numEdges = 12; // Number of edges in the graph

  // First we want to initialize the graph
  vertex * graph = (vertex * )malloc(sizeof(vertex)*numNodes);

  // Looping through
  for (int i = 0; i < numNodes; i++) {
    graph[i].prev = nullptr;
    graph[i].dist = 999; // Some max to take the place of infinity
    graph[i].visited = false;
    graph[i].counter = i;
  }

  int weights[numEdges] = {1, 2, 3, 12, 6, 11, 7, 10, 8, 4, 9, 5};
  // Creating a list of edges
  edge * edges = CreateGraph(weights);
  edges[0].head = &(graph[0]);
  edges[0].tail = &(graph[1]);
  edges[1].head = &(graph[0]);
  edges[1].tail = &(graph[2]);
  edges[2].head = &(graph[0]);
  edges[2].tail = &(graph[3]);
  edges[3].head = &(graph[1]);
  edges[3].tail = &(graph[2]);
  edges[4].head = &(graph[1]);
  edges[4].tail = &(graph[4]);
  edges[5].head = &(graph[2]);
  edges[5].tail = &(graph[3]);
  edges[6].head = &(graph[2]);
  edges[6].tail = &(graph[6]);
  edges[7].head = &(graph[3]);
  edges[7].tail = &(graph[4]);
  edges[8].head = &(graph[3]);
  edges[8].tail = &(graph[5]);
  edges[9].head = &(graph[4]);
  edges[9].tail = &(graph[5]);
  edges[10].head = &(graph[4]);
  edges[10].tail = &(graph[6]);
  edges[11].head = &(graph[5]);
  edges[11].tail = &(graph[6]);

  int numSS;

  //int * holder = nullptr;
  int * holder = FindSSSP(&(graph[0]),edges,graph,&numSS);
  int * holder2 = FindSSSP(&(graph[1]),edges,graph,&numSS);
  // Creating lists of the neighbors
  /*
  vertex * Aneighbors = (vertex *)malloc(sizeof(vertex)*3);
  Aneighbors[0] = *(graph[1]);
  Aneighbors[1] = *(graph[2]);
  Aneighbors[2] = *(graph[3]);

  vertex * Bneighbors = (vertex *)malloc(sizeof(vertex)*3);
  Bneighbors[0] = *(graph[0]);
  Bneighbors[1] = *(graph[2]);
  Bneighbors[2] = *(graph[3]);

  vertex * Cneighbors = (vertex *)malloc(sizeof(vertex)*4);
  Cneighbors[0] = *(graph[0]);
  Cneighbors[1] = *(graph[1]);
  Cneighbors[2] = *(graph[3]);
  Cneighbors[3] = *(graph[6]);

  vertex * Dneighbors = (vertex *)malloc(sizeof(vertex)*4);
  Dneighbors[0] = *(graph[0]);
  Dneighbors[1] = *(graph[2]);
  Dneighbors[2] = *(graph[4]);
  Dneighbors[3] = *(graph[5]);

  vertex * Eneighbors = (vertex *)malloc(sizeof(vertex)*4);
  Eneighbors[0] = *(graph[1]);
  Eneighbors[1] = *(graph[3]);
  Eneighbors[2] = *(graph[5]);
  Eneighbors[3] = *(graph[6]);

  vertex * Fneighbors = (vertex *)malloc(sizeof(vertex)*3);
  Fneighbors[0] = *(graph[3]);
  Fneighbors[1] = *(graph[])

  vertex * Gneighbors = (vertex *)malloc(sizeof(vertex)*3);
  */







}
