#!/usr/bin/env python3

from random import *

# Collects substrings in x that align exactly to y and are at least L units long
def commonSubstrings(x,L,a):
    insertCounts = 0 # Inserts inflate the length of a.  Otherwise len(a)==len(x)
    pipeCounts = 0 # Need to keep track of current pipe count
    pipeTracker = [] # Will hold indices of the found pipes in a
    subCounts = 0 # Current length of the substring
    fIndex = len(a)-1 # The last index in a

    # Initialization
    substring = []
    currString = ""

    # Loop through our array, a
    for i in range(0,fIndex+1):
        if (a[i]=="i"):
            insertCounts += 1 # Any insert increments a's length past x
        if (a[i]=="|"):
            pipeCounts += 1 # How many pipes have been read in the current substring
            currString += x[i-insertCounts] # Add the char in x to the current substring
        else:
            # So, if the index is not a pipe / no-op, check first if our
            # current substring is greater than L; if so, append to the curr string
            if (pipeCounts >= L):
                substring.append(currString)
            # Reset pipe count and substring after the current substring ends
            pipeCounts = 0
            currString = ""
    # If the string ends with no-ops, then we collect that substring here
    if (pipeCounts >= L):
        substring.append(currString)

    return substring



def extractAlignment(S,x,y):
    # Lengths
    nx = len(x)
    ny = len(y)

    # Initialization
    a = []
    count = 0
    [i,j] = [nx,ny]

    # While we're not at the base case
    while ((i > 0) or (j > 0)):
        a.append(determineOptimalOp(S,i,j,x,y)) # Append the next op
        [i,j] = updateIndices(S,i,j,a[count]) # Set new indices
        count += 1 # Just for keeping track of a's current index

    # Want to reverse the order of operations for better printing, as we
    # went backwards from the end
    return list(reversed(a))

def updateIndices(S,i,j,a):
    # If we did a swap
    if (a=="tt"):
        i = i-2
        j = j-2
    # If we did a sub or no-op
    elif (a=="s" or a=="|"):
        i = i-1
        j = j-1

    # If we did a deletion
    elif (a=="d"):
        i = i-1

    # If we did an insertion
    else:
        j = j-1
    return i,j

def determineOptimalOp(S,i,j,x,y):
    # Best path is the minimum of (costOption + costOp)
    # starting from the lower right node

    # Setting a value for infinity
    infin = float("inf")

    # Pre-allocating important variables
    # Initialize with the identifiers in the array 'a' for each op, then
    # initialize the values with infinity
    dd = move("tt",infin) # double diagonal move indicates swap
    sd = move("s",infin) # single diagonal move indicates sub
    no = move("|",infin) # noop
    dl = move("d",infin) # deletion
    it = move("i",infin) # insertion

    # Booleans first check that the following operations can be performed
    # Subs and no-ops operate on the same indices
    canDelete = ((i-1)>=0)
    canSwap = ((i-2)>=0 and (j-2)>=0)
    canSub = ((i-1)>=0 and (j-1)>=0)
    canInsert = ((j-1)>=0)

    # Now start checking the neighboring "nodes" in our DAG
    if (canDelete):
        dl.value = S[i-1][j] + indel()
    if (canSwap):
        dd.value = S[i-2][j-2] + swap()
    if (canSub):
        sd.value = S[i-1][j-1] + sub()
        # If a noop can be performed
        if (x[i-1]==y[j-1]):
            no.value = S[i-1][j-1] + noop()

    if (canInsert):
        it.value = S[i][j-1] + indel()

    # Pass all movement structs
    return opExtractor(dd,sd,no,dl,it)


# opExtractor simply takes the structs, and determines which move
# is the most cost-effective move to make
def opExtractor(op1,op2,op3,op4,op5):
    possiblePaths = [] # will hold all operations that give min path

    # Find the operation with the optimal cost
    s = min([op1.value,op2.value,op3.value,op4.value,op5.value])

    # Append any operation with the optimal cost
    if (s==op1.value):
        possiblePaths.append(op1.name)
    if (s==op2.value):
        possiblePaths.append(op2.name)
    if (s==op3.value):
        possiblePaths.append(op3.name)
    if (s==op4.value):
        possiblePaths.append(op4.name)
    if (s==op5.value):
        possiblePaths.append(op5.name)

    # Randomized tiebreaker will choose from possible paths randomly
    # if only one path, then it just returns that index
    tieBreak = randint(0,(len(possiblePaths)-1))

    return possiblePaths[tieBreak]

# Identfies the cost and name (array identifier) for each movment
class move():
    def __init__(self,name,value):
        self.name = name # Name of move
        self.value = value # The real cost of the move

def alignStrings(x,y):
    # Want to set the lengths of each of the input strings
    # Note that the matrix includes zeroth rows / columns, nx and ny
    # should actually be one more than the length for proper matrix building
    nx = len(x)+1
    ny = len(y)+1

    # Want to initialize S to some holder variable -1
    S = [-1] * (nx)
    for i in range(nx):
        S[i] = [-1] * (ny)

    # Need to set the base cases for S. Includes S(0,0), S(:,0), and S(0,:)
    # This is more efficient to do first, as otherwise the computational cost
    # for each iteration of the N^2 loop would increase
    S[0][0] = 0
    for i in range(1,nx):
        S[i][0] = S[i-1][0] + sub() # We know to sub from null strings to
                                    # each substring is a sequence of subs

    for i in range(1,ny):
        S[0][i] = S[0][i-1] + sub() # Same as previous

    # Looping through all rows and columns
    for i in range(1,nx):
        for j in range(1,ny):
            if (x[i-1] == y[j-1]):
                # No-ops are always the most cost-effective if possible
                S[i][j] = S[i-1][j-1] + noop()
            else:
                # If not a no-op, starts the cost function
                S[i][j] = cost(i,j,S)

    return S

def cost(i,j,S):
    # initializing some variables
    costSwap = 0
    costIndel1 = 0
    costIndel2 = 0
    costSub = 0

    # Calculating the costs, bottom-up style
    costIndel1 = S[i-1][j] + indel() # Delete
    costIndel2 = S[i][j-1] + indel() # Insertion
    costSub = S[i-1][j-1] + sub() # Substitution

    # If we're working on the second rows / columns then swap is NA
    if ((i==1) or (j==1)):
        return min([costIndel1, costIndel2, costSub])

    # But otherwise, swap should be included
    else:
        costSwap = S[i-2][j-2] + swap()
        return min([costIndel1,costIndel2,costSub,costSwap])

# Cost of a swap
def swap():
    return 13

# Cost of a sub
def sub():
    return 12

# Cost of a insertion / delete
def indel():
    return 1

# Cost of a no-op (no operation)
def noop():
    return 0

def mainTesting():
    # Just Some Testing
    y = "EXPONENTIAL"
    x = "POLYNOMIAL"

    S = alignStrings(x,y)
    a = extractAlignment(S,x,y)
    s = commonSubstrings(x,1,a)

    print(S)
    print(a)
    print(s)

def mainPartD():
    input1 = ""
    input2 = ""
    with open ("csci3104_PS7_data_string_x.txt") as myfile:
        input1 = myfile.readlines()

    with open ("csci3104_PS7_data_string_y.txt") as myfile:
        input2 = myfile.readlines()

    x = input1[0]
    y = input2[0]

    S = alignStrings(x,y)
    a = extractAlignment(S,x,y)
    #   print(a)
    c = commonSubstrings(x,9,a)

    for i in range(0,len(c)):
        print(c[i]+"\n")

if __name__== "__main__":
    mainPartD()
