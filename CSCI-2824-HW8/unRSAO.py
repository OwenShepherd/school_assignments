"""
Author: Owen Shepherd
Date: 3-24-17
filename: unRSAO.py
purpose: Function will factor an input in the form of a multiple of two primes.
This function implements the skipping even number and skipping multiples of three
method described in the writeup.
"""

from math import sqrt

def findOneFactor(n):

    # we only have to check less than sqrt(n) primes
    m = int(sqrt(n))

    # Checking 2 before starting the loop
    if n % 2 == 0:
        return 2

    # Checking 3 before starting the loop
    if n % 3 == 0:
        return 3

    i = 5 # We have to start at 5 for this pattern to work
    k = 0 # k is simply used to alternate how many numbers are skipped

    # Looping through to find the first prime number
    while (i<=m):
        if n % i == 0:
            return i

        # How much we increment the loop
        i = i+2+2*k

        # Alternating the amount that has been iterated
        k = k*-1+1
