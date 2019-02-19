from graph import *

def TestFuncs():

    Adj_List = []

    for i in range(3):
        Adj_List.append(vertex(i))

    Adj_List[0].Add_Edge(7)
    Adj_List[0].Add_Edge(8)
    Adj_List[1].Add_Edge(6)
    Adj_List[2].Add_Edge(10)
    Adj_List[0].Remove_Edge(7)
    G = Graph(Adj_List)

    return G

def TestEdges():
    DIM = 4
    E = [[False for x in range(DIM)] for y in range(DIM)]
    E[0][1] = True
    E[0][2] = True
    E[1][2] = True
    E[2][3] = True

    TestGraph = Graph()

    TestGraph.From_EdgeMatrix(E)

    return TestGraph

def TestProblem():
    V1 = [1,2,3,4,5,6]
    V2 = [7,8,9,10,11]


if __name__ == "__main__":
    G = TestEdges()
    for i in G.Adjacency_Matrix:
        print(i.Out_Edges)

    G.DFS(2,1)
