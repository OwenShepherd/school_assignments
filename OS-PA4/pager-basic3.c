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
#include <stdio.h>
#include "simulator.h"

void pageit(Pentry q[MAXPROCESSES]) {

  static int testing[MAXPROCESSES];
  static int initialized = 0;
  static int counter = 0;

  if (!initialized) {
    initialized = 1;
    for (int i = 0; i < MAXPROCESSES; i++) {
      testing[i] = 0;
      pagein(i,0);
      pagein(i,1);
      pagein(i,2);
      pagein(i,3);
      pagein(i,4);
    }
  }

  /* Local vars */
  int proc;
  int pc;
  int page;
  int oldpage;

  /* Trivial paging strategy */
  /* Select first active process */
  for(proc=0; proc<MAXPROCESSES; proc++) {

    /* Is process active? */
    if(q[proc].active) {
      /* Dedicate all work to first active process*/
      pc = q[proc].pc; 		        // program counter for process
      page = pc/PAGESIZE; 		// page the program counter needs


      if (page >= 0) {

        if (pageout(proc,6) && pageout(proc,7) && pageout(proc,8)) {
          if (page < 3) {
            pagein(proc,2);
            pagein(proc,3);
            pagein(proc,4);
          }
        }
        if (page >= 3) {
          if (pageout(proc,0) && pageout(proc,1) && pageout(proc,2)) {
            if (page < 6) {
              pagein(proc,5);
              pagein(proc,6);
              pagein(proc,7);
            }
          }
          // 3 4 5 6 7

          if (page >= 6) {
            if (pageout(proc,3) && pageout(proc,4) && pageout(proc,5)) {
              pagein(proc,8);
              pagein(proc,0);
              pagein(proc,1);
            }
            // 0 1 6 7 8
          }
        }
      }

      /*
      // 0 1 2 3 4
      if (page >= 2) {
        if (pageout(proc,0) && pageout(proc,1)) {
          if (page < 8) {
            pagein(proc,5);
            pagein(proc,6);
          }
        }
        // 2 3 4 5 6
        if (page >= 5) {
          if (pageout(proc,2) && pageout(proc,3) && pageout(proc,4)) {
            if (page < 8) {
              pagein(proc,7);
            pagein(proc,8);
            pagein(proc,9);
          }
          }
          // 5 6 7 8 9
          if (page >= 8) {
            if (pageout(proc,5) && pageout(proc,6) && pageout(proc,7)) {
              pagein(proc,10);
              pagein(proc,11);
              pagein(proc,12);
            }
            // 8 9 10 11 12
            if (page >= 10) {
              if (pageout(proc,8) && pageout(proc,9)) {
                pagein(proc,13);
                pagein(proc,14);
              }
            }
          }
        }
      }
      */


      /*
      counter++;
      fprintf(stderr,"Proc: %d; PC: %d; Page: %d\n",proc,pc,page);
      if (counter == 100) {
        getchar();
        counter = 0;
      }*/


      /* Is page swaped-out? */
      if(!q[proc].pages[page]) {
        /* Try to swap in */
        if(!pagein(proc,page)) {
          /* If swapping fails, swap out another page */
          for(oldpage=0; oldpage < q[proc].npages; oldpage++) {
            /* Make sure page isn't one I want */
            if(oldpage != page) {
              /* Try to swap-out */
              if(pageout(proc,oldpage)) {
                /* Break loop once swap-out starts*/
                //break;
              }
            }
          }
        }
      }
      /* Break loop after finding first active process */
      //break;

    }
  }
}
