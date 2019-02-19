# OS-PA4
Programming assignment for CSCI 3753 - Operating Systems at CU Boulder


## 1 - Introduction
In this assignment, we will look at various strategies of managing the system
page table.  In other words, we will handle what pages are swapped in and what
pages are swapped out.

## 2 - Your Task
A paging simulator has already been written for this program, we must only
write the paging strategy that the simulator uses.  We begin with a Least
Recently Used paging algorithm.

### 2.1 - The Simulator Environment
Simulator source code is included with the files:
```
simulator.c
simulator.h
```
The simulator will run random programs with a fixed virtual memory space.  All memory access is due to the need to load program code.  
Some default values:
- 20 virtual pages per process (MAXPROCPAGES)
- 100 physical pages (frames) total (PHYSICALPAGES)
- 20 simultaneous processes (MAXPROCESSES)
- 128 memory unit page size (PAGESIZE)
- 100 tick delay to swap a page (PAGEWAIT)

So, the simulator is constrained fairly heavily.  Sometimes, the performance restraints can result in a 200:1 page waiting : useful-tick ratios.

### 2.2 - The Simulator Interface
Simulator exports three functions.  First function to be examined is **pageit**, which is called whenever something 'interesting' happens, such as a memory access, page fault, etc.  
Pageit:  
- Passed an array of structs, with each struct containing some information about the process

The simulator also has the two functions **pagein** and **pageout**, which will be called whenever a page for a specific process needs to be swapped in or out.  Both return 1 on success.  Important note: no information on whether the page is currently being used by a process.  If this information is needed for implementation, it must be added by the user.

### 2.3 - The Simulated Programs
The programs just basically are loops that will probabilistically decide how many operations to perform.

## 3 - Some Implementation Ideas
See the flow char on page 5 for how to program pageit.  While there are processes running, just determine if the needed page is swapped in, if not call pagein and determine which page to swap out.  Call pageout, then check remaining processes.  If the page is swapped in, obviously this whole headache can be avoided.
**See pager-basic.c for simple examples with paging**.  Initial work on a LRU paging system has been completed within **pager-lru.c**  

To really perform well on this assignment, you will create a predictive paging system, initially done in **pager-predict.c**.  A good predictive paging algorithm will try to use how the program or program counter / PC behaves in order to predict what pages will be used (analyze the PC for common repeats...).

Also note that processes will release their pages when they complete.

## 4 - What's Included
- **Makefile**: GNU Make makefile to build listed code.
- **README**
- **simulator.c**: core simulator code.  For ref.
- **simulator.h**: simulator header file.
- **programs.c**: simulated programs for use by simulator.
- **pager-basic.c**: basic implementation.
- **pager-lru.c**: stub for LRU implementation.
- **pager-predict.c**:stub for predictive paging.
- **api-test.c**: pageit implementation that detects and prints simulator state pages.
- **test-***: Runs the simulator using the **paging-*.c** strategy and built using Makefile.  Try using help to see what tools are available to use.
- **test-api**: API test program
- **see.R**: R script for displaying a visualization of the process.  First run "./test-* -csv" to generate the trace files.  Launch R in windowed graphics mode.

## 5 - What Must Be Provided
- A copy of the LRU paging implementation
- A copy of the best predictive implementation
- A makefile to build the necessary code
- A README explaining how to build and run the code

## 6 - Grading
Near %40 of the grade will be based on the predictive implementation provided.  The performance must be <= 0.02 for a top score.  Also, the code must be compiled warning and error-free while compiling with the -Wall and -Wextra options enabled.
