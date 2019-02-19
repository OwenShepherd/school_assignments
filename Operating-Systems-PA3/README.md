# Operating-Systems-PA3
Author: Owen Shepherd  
Date: March 11th, 2018  
Purpose: To work with pthreads and understanded multi-threaded programming.  
For University of Colorado - Boulder, CSCI 3753 - Operating Systems.

## Use
I was unable to get the output file writing done, as the dns lookup functions were not working.  In particular, "getaddrinfo.c" was constantly crashing / halting my program with error "getaddrinfo.c: no such file or directory" and I could not figure out how to fix this in time.  Also, the round robin file scheduling addendum took me much longer than the "30 min" my TA promised...

## Input
Input: <file names> <output file> <number of requester streams>


# Assignment Information
## Introduction
- Application is composed of two sub-systems with their own thread pools: requests and resolvers
- Subsystems communicate using a bounded array
- We want to supply a list of IP addresses matching each hostname
- Program will process a number of files containing a list of hostnames
- A requester thread to process each file (don't have one thread per file?)
- General workflow: each requester thread parses the hostname, stores it in a shared data area, finds the IP address, and writes results to a file
- Status information recorded for the requester will be stored in **serviced.txt** whereas resolver info will be written to **results.txt**

## Description
### Input: Name Files
- Program will take name files as input, which contain a single hostname per line
- The number of requester threads is greater than or equal to the number of input files (avoid equal to?)

### Requester Threads
- If the array is full when a requester thread attempts to write, it should block until space opens up
- Take as input the number of requester threads
- If a thread finishes its file and there are files left, it will then request one of the remaining files
- If a thread finishes with no file left, it will write the following to **serviced.txt**:
```
Thread <thread id> serviced ### files
```

### Resolver Threads
- Resolver threads take names and resolve IP addresses
- If there is no name left in the shared array, the thread will block until there is a new item, or until every file has been resolved
- Resolver threads should write to **results.txt** in the following format:
```
www.google.com, 74.125.224.81
```

### Synchronization and Deadlock
- Application should synchronize shared resources and avoid deadlock or busy-wait using **mutexes** and **conditional variables**
- There are at least three shared resources: the name array, serviced.txt, and results.txt
- Program must print total run-time

## Additional Specifications
### Error Handling
- Bogus Hostname: ip address is resolved to an empty string and the alert should be printed to stderr
- Bogus Output File Path
- Bogus Input File Path

## What you must provide
- multi-lookup.c: the program
- multi-lookup.h: prototypes for any function provided
- README.md
- performance.txt: see pdf

## Recitation Tips
- Don't use globals, use pthread's 4th input parameter
- If you have five files, make an array of five mutexes
- Don't need a condition variable for the shared array
