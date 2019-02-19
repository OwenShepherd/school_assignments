#include<queue>
#include<iostream>
#include<time.h>

using namespace std;

int* soErat(int);

int* sumCount(queue<int>);

int* soErat(int N)
{
  // queue will keep track of primes collected
  queue<int> primes;

  int p; // the current prime number
  int mp; // the current prime multiple
  int counter; // keeps track of what prime multiple we're on
  int pIndex; // Keeps track of prime index
  bool DONE; // Determines whether or not the prime loop has finished

  // Initial prime number is 2
  p = 2;

  // Adding the inital prime number
  primes.push(p);

  // Array that will keep track of what primes
  bool *isPrime = new bool[N];

  // Looping through and defaulting values to true
  for (int i = 0; i<N; i++)
    isPrime[i] = true;



  // Filling the array with all numbers less than 500
  while (p<=N)
  {
    // Initially we look for when the multiple is simply the prime
    counter = 1;
    mp = counter*p;

    for (int i = 0; i<N; i++)
    {
      if (mp == (i+1))
      {
        // If we find the prime, we set that array index to false, increment
        // counter, and look for the next multiple
        isPrime[i] = false;
        counter++;
        mp = counter*p;
      }
    }

    // Here we need to start testing for the next prime number
    DONE = false;
    pIndex = p; // we start at the index one above the current prime number

    while (!DONE)
    {
        // If we've found the next prime number
        if (isPrime[pIndex] && pIndex<N)
        {
          // we set the next prime, put it in the queue
          p = pIndex+1;
          primes.push(p);
          DONE = true;
        }
        else
        {
          // If we don't find a prime, and we're not outside our bounds, then we
          // look at the next index
          pIndex++;
          DONE = pIndex>N;
          if (DONE)
            p = N+1;
        }


  }
}

// Determining sum anc number of primes
return sumCount(primes);

}

int* sumCount(queue<int> primes)
{
  int sum = 0; // Keeping track of sum
  int counter = 0; // Number of primes
  int* sumCo = new int[2]; // Array to be returned


  // Need to loop through as long as the queue is empty
  bool isEmpty = primes.empty();

  // Summing up all queue elements
  while (!isEmpty)
  {
    sum+=primes.front();
    primes.pop();
    isEmpty = primes.empty();
    counter++;
  }

  sumCo[0] = counter;
  sumCo[1] = sum;

  return sumCo;
}

int main()
{

    // keeps track of how many clock tics have elapsed
    clock_t t1,t2;
    t1=clock();


  int N = 500000;
  int* sumCo;

  sumCo = soErat(N);

  cout<<"For N = "<<N<<":"<<endl;
  cout<<"Num. Primes = "<<sumCo[0]<<endl;
  cout<<"Sum = "<<sumCo[1]<<endl;

  t2=clock();
  float diff ((float)t2-(float)t1);
  cout<<diff/CLOCKS_PER_SEC<<endl;


  return 0;

}
