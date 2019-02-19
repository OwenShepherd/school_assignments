"""
Author: Owen Shepherd
Date: 3-24-17
filename: main.py
purpose: will take a user input from the command line, where the input is
assumed to be a product of two prime numbers, and finds the prime factors
"""
# Importing necssary libraries
from unRSA import *
import sys
import time

# Want to record the total time elapsed
start_time = time.time()

# Grabbing the user input from the command line
inInput = map(long,sys.argv[1:])
inInput = inInput[0]
print inInput

# Reading in the test file
with open("testlist.txt", 'r') as f:
    data = f.readlines()

# Here the text file data is mapped correctly
data = map(int,data)

# Calling the find factor function to find the first factor
p = findOneFactor(inInput)

# Dividing the number by the factor found above to find the second factor
q = inInput/p

# Printing and calculated the elapsed time
print "We have p = ",p," and q = ",q
elapsed_time = time.time()-start_time
print "The elapsed time is: "
print elapsed_time
