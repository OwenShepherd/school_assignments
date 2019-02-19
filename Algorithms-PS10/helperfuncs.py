def Directed_To_Undirected(Edge_Matrix):
    DIM = len(Edge_Matrix)
    for row in range(DIM):
        for col in range(DIM):
            if (Edge_Matrix[row][col] == True):
                Edge_Matrix[col][row] = True

    return Edge_Matrix

def Ford_Fulkerson(Gf,s,t):
    sigma = Gf.DFS(s,t)


def ParseGraph(V1,V2,E):
    """ Parses a bipartite graph for max-flow stuff

    Parameters:
        G - The graph
        V1 - One set of vertices for the bipartite graph
        V2 - The other set of vertices

    Returns:
        meh - meh

    """

    MATRIX_DIM = len(V1) + len(V2)

    Start_VertexID = MATRIX_DIM # Want to add a starting vertex
    End_VertexID = Start_Vertex + 1 # Want to add an ending vertex

    Start_Vertex = vertex()
    End_Vertex = vertex()


    # Going to say that the source connects to all V1 vertices
    for i in range(len(V1)):
        Start_Vertex.Add_Edge(V1[i].ID)

    # Similarly going to say that all the V2 vertices end at the termination /
    # ending vertex.
    for i in range(len(V2)):
        V2[i].Add_Edge(End_Vertex)

    # Now we're going to remove unwanted edges from the edge matrix
    for row in range(MATRIX_DIM):
        for col in range(MATRIX_DIM):
            if (E[row][col] == 1):
                rowV1 = row in V1
                colV1 = col in V1
                rowV2 = row in V2
                colV2 = col in V2

                if (rowV1 and colV1):
                    E[row][col] == 0
                elif (rowV2 and colV2):
                    E[row][col] == 0
