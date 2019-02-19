/**
Purpose: For CSCI 2824 HW5 Exercise 5.  Implementation of 
related functions.
Filename: hw5d.cpp
Date: 2-22-17
Author: Owen Shepherd.
*/

#include <iostream>
#include <cmath>
#include "hw5.h"
using namespace std;

double* evenArr(double arr[],int &N)
{
  // Creating a new array
  double *eArr = new double[1];
  int esize = 0;

  // Looping through
  for (int i = 0;i<N;i++)
  {
      // Checking evenness and adding it to the new array
      if (fmod(arr[i],2.0) == 0)
      {
        eArr[esize] = arr[i];
        esize = esize+1;
      }
  }
  N = esize;

  return eArr;

}



double* lucasNum(int N)
{
  // We want the N+1 lucas numbers
  N=N+1;

  // Array to contain Lucas numbers
  double *arr = new double[N+1];

  // First Values
  int l0 = 2;
  int l1 = 1;


  // Now we want to get the rest of the values
  for (int i = 0; i<N; i++)
  {
      if (i==0)
      {
        arr[i] = l0;
      }

      else if (i==1)
      {
        arr[i] = l1;
      }
      else
      {
      arr[i] = arr[i-1]+arr[i-2];
    }
  }

  return arr;
  delete []arr;
}

int findSum(double arr[],int N)
{
  // sum
  int sum = 0;

  // looping through
  for (int i = 0;i<N;i++)
  {
    sum = sum+arr[i];
  }

  return sum;
}


int evenLucasSum(int N)
{

  // Integer that will track the size of the even array
  int eN = N;

  // Calling all the functions to create the array, make it even, and find the
  // sum
  double *a = lucasNum(N);
  double *b = evenArr(a,eN);
  int sum = findSum(b,eN);

  cout<<"For N="<<N<<endl;

  // Outputting all the Even Array values
  cout<<"Even Lucas Array:"<<endl;
  for (int i = 0;i<eN;i++)
  {
    cout<<b[i]<<endl;
  }

  // Outputting the sum
  cout<<"Sum = "<<sum<<endl;

  return sum;
}

int* firstDDigitLucas(int D)
{

  int index;
  double value;

  // Here we have the number of digits
  double key = pow(10,D-1);

  // counter for loop
  int counter = 0;

  // Here we loop through looking for the time the Lucas number is that many
  // digits
  int check = 0;
  while(check == 0)
  {
    double*a = lucasNum(counter);
    cout<<a[counter]<<endl;
    if ((a[counter]-key) > 0 )
    {
      index = counter;
      value = a[counter];
      check = 1;

    }
    counter = counter+1;
  }

  cout<<"The First Lucas Number for D = "<<D<<endl;
  cout<<"Index:"<<endl;
  cout<<index<<endl;
  cout<<"Value:"<<endl;
  cout<<value<<endl;

  int *locs = new int[2];

  locs[0] = index;
  locs[1] = value;

  return locs;

}
