"""
Author: Owen Shepherd
Date: 3-24-17
filename: unRSA.py
purpose: Function will factor an input in the form of a multiple of two prime
numbers
"""


from math import sqrt

def findOneFactor(n):

    # Only have to check up to the sqrt(n)
    m = int(sqrt(n))

    # Checking 2 first before entering the loop
    if n % 2 == 0:
        return 2

    # starting the loop at 3
    i = 3

    while (i<=(m)):
        # checking if the factor has been found
        if n % i == 0:
            return i
        # We increment the loop by two to skip even numbers
        i = i+2
