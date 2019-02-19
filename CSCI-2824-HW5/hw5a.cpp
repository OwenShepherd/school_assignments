/**
Purpose: For CSCI 2824 HW5 Exercise 5, part A.  Computes the sum of the first N+1 
Even Lucas Numbers given a user defined N.
Filename: hw5a.cpp
Date: 2-22-17
Author: Owen Shepherd.
*/
#include <iostream>
#include "hw5.h"
using namespace std;

int main()
{
  // Pre-allocating
  int sum;
  int N;

  // Number of Lucas Numbers to calculate and then 
  // Calculating the even Lucas sum.
  N = 50;
  sum = evenLucasSum(N);

}
