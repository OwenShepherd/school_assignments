import pdb
from helperfuncs import *

class vertex:
    def __init__(self, VertexName):
        self.Out_Edges = []
        self.ID = VertexName
        self.Visited = False

    def Add_Edge(self, NextEdge):
        self.Out_Edges.append(NextEdge)

    def Remove_Edge(self, Edge):
        self.Out_Edges.remove(Edge)

class Edge:
    def __init__(self,tail,head,weight=1):
        self.Source = tail
        self.Destination = head
        self.Flow = 0
        self.Weight = weight


class Graph:
    def __init__(self, Adj_Mat=None):
        if (Adj_Mat == None):
            self.Adjacency_Matrix = []
        else:
            self.Adjacency_Matrix = Adj_Mat

        self.Edges = []

    def From_EdgeMatrix(self, EdgeMat, Directed=False):
        DIM = len(EdgeMat)
        if not Directed:
            EdgeMat = Directed_To_Undirected(EdgeMat)
        for row in range(DIM):
            self.Add_Vertex(row)

            for col in range(DIM):
                if (EdgeMat[row][col] == True):
                    if not Directed:
                        EdgeMat[col][row] = True
                        self.Edges.append(Edge(col,row))
                    self.Edges.append(Edge(row,col))
                    self.Adjacency_Matrix[row].Add_Edge(col)



    def Add_Vertex(self, ID, Adj_List=None):
        newVertex = vertex(ID)

        if (Adj_List != None):
            for edge in Adj_List:
                newVertex.Add_Edge(edge)

        self.Adjacency_Matrix.append(newVertex)

    def DFS_Clear(self):
        for Vertex in self.Adjacency_Matrix:
            Vertex.Visited = False

    def DFS(self, SearchVertex_ID,EndVertex=None):
        SearchVertex = self.Adjacency_Matrix[SearchVertex_ID]
        self.DFS_Recurse(SearchVertex,EndVertex)

    def DFS_Recurse(self, CurrentVertex,EndVertex):
        CurrentVertex.Visited = True
        print(CurrentVertex.ID)
        for Adj_Vertex in CurrentVertex.Out_Edges:
            if ((Adj_Vertex == EndVertex)):
                if (self.Adjacency_Matrix[Adj_Vertex].Visited == False):
                    print(Adj_Vertex)
                    self.Adjacency_Matrix[Adj_Vertex].Visited = True
                break
            if (self.Adjacency_Matrix[Adj_Vertex].Visited == False):
                self.DFS_Recurse(self.Adjacency_Matrix[Adj_Vertex],EndVertex)
