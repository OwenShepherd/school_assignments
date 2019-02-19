/**
Purpose: For CSCI 2824 HW5 Exercise 5, part A. 
Definitions for related Functions.
Filename: hw5.h
Date: 2-22-17
Author: Owen Shepherd.
*/

/**
This is simply the  Lucas function by definition for N+1 integers
Inputs:
N - the integer argument for determining N+1 Lucas numbers
Outputs - pointer to first element of lucas number array
*/
double* lucasNum(int N);

/**
This gets rid of all the odd numbers in an array
Inputs:
arr - the array to be attenuated
N - the size of the array
Outputs - pointer to the first element of the even arary
*/
double * evenArr(double arr[],int &N);

/**
This finds the sum of an array
Inputs:
arr - the array to find the sum of
N - the size of the array
Outputs - the sum of the array
*/
int findSum(double,int);

/**
Finding the sum of the first N+1 even Lucas Numbers
Inputs:
N - the number of Lucas Numbers desired
*/
int evenLucasSum(int N);

/**
Finds the first lucas number with the specified number of digits
Inputs:
D - the number of digits
Outputs - array where first element is index, second element is value
*/
int *firstDDigitLucas(int);
