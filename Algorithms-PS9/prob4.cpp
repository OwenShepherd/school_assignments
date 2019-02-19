#include <iostream>
#include <list>
#include <math.h>

using namespace std;

struct vertex {
  bool visited; // Whether it has been visited yet
  bool visitedB; // Whether it has been visited by the backwards traverser
  int dist;  // Distance to the particular vertex
  int distB; // Distance to the vertex on the backwards search
  int id;  // Identifier for the vertex
};


class Graph {
  int V;
  int popCounter;
  list<int> *adj;
  vertex * vertices;
  int * returnVal;
  int intersect;

public:
  Graph(int V);
  ~Graph();
  void addEdge(int v, int w);

  void BFSSearcher(int s);

  void BFS(int s, int t, int &dist, int &popped);

  void BD_BFS(int s, int t, int &dist, int &popped);

  bool Intersection();

};

Graph::Graph(int V) {
  this->V = V;
  adj = new list<int>[V];
  vertices = (vertex*)malloc(sizeof(vertex)*V);
  returnVal = (int*)malloc(sizeof(int)*2);
}

Graph::~Graph() {
  free(vertices);
  free(returnVal);
}

void Graph::addEdge(int v, int w) {
  adj[v].push_back(w);
  adj[w].push_back(v);
}

bool Graph::Intersection() {

  for (int i = 0; i < V; i++) {
    if (vertices[i].visited && vertices[i].visitedB) {
      intersect = i;
      return true;
    }
  }

  return false;

}

void Graph::BFS(int s, int t, int &dist, int &popped) {
  BFSSearcher(s);
  dist = vertices[t].dist;
  popped = popCounter;
}

void Graph::BD_BFS(int s, int t, int &distance, int &popped) {
  popCounter = 0;

  vertex currentVertex;
  vertex currentVertexB;

  for (int i = 0; i < V; i++) {
    vertices[i].visited = false;
    vertices[i].visitedB = false;
    vertices[i].id = i;
  }

  list<vertex> searchQ;
  list<vertex> searchQB;

  // Doing the forwards search first
  vertices[s].visited = true;
  vertices[s].dist = 0;

  // Backwards Search stuff
  vertices[t].visitedB = true;
  vertices[t].distB = 0;

  searchQ.push_back(vertices[s]);
  searchQB.push_back(vertices[t]);

  while (!searchQ.empty() && !searchQB.empty()) {
    currentVertex = searchQ.front();
    searchQ.pop_front();
    popCounter++;
    int test;
    currentVertexB = searchQB.front();
    searchQB.pop_front();
    popCounter++;

    // list iterator
    list<int>::const_iterator it;

    for (it = adj[currentVertex.id].begin(); it != adj[currentVertex.id].end(); ++it) {
      if (!(vertices[*it].visited)) {
        vertices[*it].visited = true;
        vertices[*it].dist = currentVertex.dist + 1;
        searchQ.push_back(vertices[*it]);
      }
    }
    for (it = adj[currentVertexB.id].begin(); it != adj[currentVertexB.id].end(); ++it) {
      if (!(vertices[*it].visitedB)) {
        vertices[*it].visitedB = true;
        vertices[*it].distB = currentVertexB.distB+1;
        searchQB.push_back(vertices[*it]);

      }
    }

    if (Intersection()) {
      distance = vertices[intersect].dist + vertices[intersect].distB;
      popped = popCounter;
      break;
    }

  }

}


void Graph::BFSSearcher(int s) {
  popCounter = 0; // Initialize the popCounter to zero
  // Create an array of vertices
  vertex currentVertex;
  // Mark vertices as unvisited
  for (int i = 0; i < V; i++) {
    vertices[i].visited = false;
    vertices[i].id = i;
  }

  // The search queue
  list<vertex> searchQ;

  // Marking the start vertex as visited and with a distance of zero
  vertices[s].visited = true;
  vertices[s].dist = 0;

  searchQ.push_back(vertices[s]);

  while (!searchQ.empty()) {
    // Dequeue the next vertex
    currentVertex = searchQ.front();
    searchQ.pop_front();
    popCounter++;
    // Go through the adjacent vertices of the graph's vertex list
    for (list<int>::const_iterator iterator = adj[currentVertex.id].begin(); iterator != adj[currentVertex.id].end(); ++iterator) {
      if (!(vertices[*iterator].visited)) {
        vertices[*iterator].visited = true;
        vertices[*iterator].dist = currentVertex.dist + 1;
        searchQ.push_back(vertices[*iterator]);
      }
    }
  }


}

void Grids(int, int&, int&, int&, int&);

int main() {

  int d1 = 0;
  int k1 = 0;
  int d2 = 0;
  int k2 = 0;

  int n = 3;

  Grids(n, d1, k1, d2, k2);

  cout<<"Single BFS: "<<endl;
  cout<<"Distance: "<<d1<<endl;
  cout<<"Num. Popped: "<<k1<<"\n"<<endl;

  cout<<"Bi-BFS: "<<endl;
  cout<<"Distance: "<<d2<<endl;
  cout<<"Num. Popped: "<<k2<<endl;

  return 0;
}

int gcalc(int i, int j, int n) {
  return n*i+j;
}


void Grids(int n, int & distance, int & numPopped, int & distanceB, int & numPoppedB) {
  Graph grid(n*n); // Grid with nxn vertices

  int u;
  int v;

  // Iterating over the grid
  // i - rows; j - columns
  // i = 0: First row / top row
  // j = 0: First col / far-left col
  // Counting:
  // 0, 1, 2, 3, 4, 5, ...n-1
  // n, n+1, n+2, n+3, ...2n-1
  for (int i = 0 ; i < n; i++) {
    for (int j = 0; j < n; j++) {
      u = gcalc(i,j,n); // Our current node

      // If we're in the top row
      if (i == 0) {
        // If we're in the top-left corner
        if (j == 0) {
          v = gcalc(i+1,j,n);
          grid.addEdge(u,v);
          v = gcalc(i,j+1,n);
          grid.addEdge(u,v);
        }
        // If we're not in a corner
        else if (j != (n-1)) {
          v = gcalc(i,j-1,n);
          grid.addEdge(u,v);
          v = gcalc(i,j+1,n);
          grid.addEdge(u,v);
          v = gcalc(i+1,j,n);
          grid.addEdge(u,v);
        }

        else {
          v = gcalc(i,j-1,n);
          grid.addEdge(u,v);
          v = gcalc(i+1,j,n);
          grid.addEdge(u,v);
        }

      }

      // If we're in the bottom row
      else if (i == (n-1)) {
        // If we're in the bottom-left corner
        if (j == 0) {
          v = gcalc(i,j+1,n);
          grid.addEdge(u,v);
          v = gcalc(i-1,j,n);
          grid.addEdge(u,v);
        }
        // If we're not in a corner
        else if (j != (n-1)) {
          v = gcalc(i,j-1,n);
          grid.addEdge(u,v);
          v = gcalc(i,j+1,n);
          grid.addEdge(u,v);
          v = gcalc(i-1,j,n);
          grid.addEdge(u,v);
        }
        // If we're in the bottom-right corner
        else {
          v = gcalc(i,j-1,n);
          grid.addEdge(u,v);
          v = gcalc(i-1,j,n);
          grid.addEdge(u,v);
        }
      }

      // If we're along the left side
      else if (j == 0) {
        v = gcalc(i,j+1,n);
        grid.addEdge(u,v);
        v = gcalc(i+1,j,n);
        grid.addEdge(u,v);
        v = gcalc(i-1,j,n);
        grid.addEdge(u,v);
      }

      else if (j == (n-1)) {
        v = gcalc(i,j-1,n);
        grid.addEdge(u,v);
        v = gcalc(i+1,j,n);
        grid.addEdge(u,v);
        v = gcalc(i-1,j,n);
        grid.addEdge(u,v);
      }

      else {
        v = gcalc(i,j-1,n);
        grid.addEdge(u,v);
        v = gcalc(i,j+1,n);
        grid.addEdge(u,v);
        v = gcalc(i-1,j,n);
        grid.addEdge(u,v);
        v = gcalc(i+1,j,n);
        grid.addEdge(u,v);
      }
    }
  }

  // Calculate the starting and ending vertex
  int x = ceil((n-1)/2.0);
  int y = 0;
  int y2 = n-1;
  int s = gcalc(x,y,n);
  int t = gcalc(x,y2,n);



  grid.BFS(s, t, distance, numPopped);
  grid.BD_BFS(s, t, distanceB, numPoppedB);
}
