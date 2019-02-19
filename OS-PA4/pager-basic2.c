/*
* File: pager-basic.c
* Author:       Andy Sayler
*               http://www.andysayler.com
* Adopted From: Dr. Alva Couch
*               http://www.cs.tufts.edu/~couch/
*
* Project: CSCI 3753 Programming Assignment 4
* Create Date: Unknown
* Modify Date: 2012/04/03
* Description:
* 	This file contains a simple pageit
*      implmentation at performs very poorly, but
*      provided a basic idea of how to user the
*      simulator interface. Your job is to improve
*      upon this implmentation.
*/

#include "simulator.h"
#include <stdio.h>

struct ProgramStruct {
  int ProgramID;
};


// This program evaluates what program the process is running
int programChecker(int prevpc, int pc) {
  int program; // The program number
  if (((prevpc == 503) && (pc == 0)) || ((prevpc == 501) && (pc == 0))) {
    program = 4;
    return program;
  }
  if (((prevpc == 1401) && (pc == 1533)) || ((prevpc == 500) && (pc == 1402))) {
    program = 0;
    return program;
  }
  if (((prevpc == 1129) && (pc == 0))) {
    program = 1;
    return program;
  }
  if ((prevpc == 1911) && (pc == 0)) {
    program = 3;
    return program;
  }
  if ((prevpc == 1682) && (pc == 1166)) {
    program = 2;
    return program;
  }
  program = 9;
  return program;
}

void pageit(Pentry q[MAXPROCESSES]) {

  /* Local vars */
  int proc; // supplies the identity of the process in question
  int pc; // Stores the identification of the program counter
  int page; // Supplies the process page
  int oldpage;
  int foundProgram = 9;
  static int counter = 0;
  static int totCounter = 0;
  static int prevpc = -1;
  static int prevpcs[MAXPROCESSES];
  static struct ProgramStruct ProgramStructs[MAXPROCESSES];
  char foundString;

  static int initialized = 0;

  if (!initialized) {
    for (int i = 0; i < MAXPROCESSES; i++) {
      ProgramStructs[i].ProgramID = 9;
      prevpcs[i] =
      pagein(i,0);
      pagein(i,1);
      pagein(i,2);
      pagein(i,3);
    }
    initialized = 1;
    fprintf(stderr,"Finished loading in pages.\n");
  }
/*
  /* Trivial paging strategy */
  /* Select first active process */
  for(proc=0; proc<MAXPROCESSES; proc++) {

    /* Is process active? */
    if(q[proc].active) {

      /* Dedicate all work to first active process*/
      pc = q[proc].pc; 		        // program counter for process
      //fprintf(stderr,"PrevPC: %d; PC: %d\n",prevpc,pc);
      page = pc/PAGESIZE; 		// page the program counter needs

      if (ProgramStructs[proc].ProgramID == 9) {
        foundProgram = programChecker(prevpc,pc);
        ProgramStructs[proc].ProgramID = foundProgram;
      }
      /*
      foundString = ProgramStructs[proc].ProgramID + '0';

      fprintf(stderr, "Process: %d; PC: %d; Page: %d; Program: %c\n",proc,pc,page,foundString);
      counter++;
      if (counter == 100) {
        getchar();
        counter = 0;
      }
      */
      prevpc = pc;
              //totCounter++;



      /* Is page swaped-out? */
      // If statement checks if the page is in memory
      if(!q[proc].pages[page]) {
        fprintf(stderr,"Not in memory.\n");
        //getchar();
        /* Try to swap in */
        // Checks if pagein fails
        if(!pagein(proc,page)) {
          fprintf(stderr,"Page not in memory and not waiting.\n");

          // /* If swapping fails, swap out another page */
          // // This will loop through pages listed in the process memory space
          // for(oldpage=0; oldpage < q[proc].npages; oldpage++) {
          //
          //   /* Make sure page isn't one I want */
          //   // Make sure we're not removing the page we want
          //   if(oldpage != page) {
          //
          //     /* Try to swap-out */
          //     if(pageout(proc,oldpage)) {
          //       /* Break loop once swap-out starts*/
          //       // This program exits after the first process served
          //       //break;
          //     }
          //   }
          // }
        }
      }
      /* Break loop after finding first active process */
      //break;
    }
  }

}
