/*
* File: pager-lru.c
* Author:       Andy Sayler
*               http://www.andysayler.com
* Adopted From: Dr. Alva Couch
*               http://www.cs.tufts.edu/~couch/
*
* Project: CSCI 3753 Programming Assignment 4
* Create Date: Unknown
* Modify Date: 2012/04/03
* Description:
* 	This file contains an lru pageit
*      implmentation.
*/

#include <stdio.h>
#include <stdlib.h>

#include "simulator.h"

void pageit(Pentry q[MAXPROCESSES]) {

  /* This file contains the stub for an LRU pager */
  /* You may need to add/remove/modify any part of this file */

  /* Static vars */
  static int initialized = 0; // Is this the first run?
  static int tick = 1; // artificial time
  static int timestamps[MAXPROCESSES][MAXPROCPAGES]; // I think this keeps track of time somehow?
                                                     // element one might id the process, element 2
                                                     // might id the page

  /* Local vars */
  // Loop iterators
  int proctmp;
  int pagetmp;
  int pc; // Program counter
  int proc; // Process iterator
  int page; // Page # storage
  int min;
  int EvictPage; // Page to evict
  int oldpage; // oldpage iterator


  /* initialize static vars on first run */
  if(!initialized){
    for(proctmp=0; proctmp < MAXPROCESSES; proctmp++){
      for(pagetmp=0; pagetmp < MAXPROCPAGES; pagetmp++){
        timestamps[proctmp][pagetmp] = 0;
      }
    }
    initialized = 1;
  }

  /* TODO: Make LRU work well */
  for (proc = 0; proc < MAXPROCESSES; proc++) {
    // Is the process active?
    if (q[proc].active) {

      pc = q[proc].pc; // Program counter
      page = pc/PAGESIZE; // page #
      timestamps[proc][page] = tick; // Marks the time at which this page was last used

      // Is the page not yet in memory
      if (!q[proc].pages[page]) {

        // If the page can't be swapped in
        if (!pagein(proc,page)) {

          // Want to loop through the pages in the process
          // Mark the min as the first page
          min = tick+1;

          // Loop through the process pages
          for (oldpage = 0; oldpage < MAXPROCPAGES; oldpage++) {
            if (q[proc].pages[oldpage]) {
              if (timestamps[proc][oldpage] < min) {
                min = timestamps[proc][oldpage];
                EvictPage = oldpage;

                if (min<=1) {
                  break;
                }
              }
            }

          }
          // Evict the selected page
          if (!pageout(proc,EvictPage)) {
              fprintf(stderr,"ERROR: Evicting page failure.\n");
              exit(EXIT_FAILURE);
          }

        }

      }
    }
  }
  /* advance time for next pageit iteration */
  tick++; // This is an artificial way for the simulator to keep track of timing / ticks
}
