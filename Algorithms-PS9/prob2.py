#!/usr/bin/env python3

"""
a - b - 0
a - c - 1
a - d - 2
b - c - 3
b - e - 4
c - d - 5
c - g - 6
d - e - 7
d - f - 8
e - f - 9
e - g - 10
f - g - 11

Node a: 0-

"""
def CreateGraph(a, b, c, d, e, f, g, h, i, j, k, l):
    W = [0]*12
    W[0] = a
    W[1] = b
    W[2] = c
    W[3] = d
    W[4] = e
    W[5] = f
    W[6] = g
    W[7] = h
    W[8] = i
    W[9] = j
    W[10] = k
    W[11] = l
    return W

def Relax(u,v):
    print("hellow world")

# W is the weights of the edges
def GetSSSP(W):
    # Starting at source A
    nodeA = W[0:3]
    nodeB = W[3:5]
    nodeC = W[5:7]
    nodeD = W[7:9]
    print (nodeD)



def main():
    W = CreateGraph(1,2,3,4,5,6,7,8,9,10,11,12)
    GetSSSP(W)


if __name__ == "__main__":
    main()
