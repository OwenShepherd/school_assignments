/* File: pager-basic.c
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

typedef struct {
  int ProgramID;
  int found;
  int prevpc;
} ProgramStruct;

static ProgramStruct *ProgramStructs[MAXPROCESSES];

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

void pagerAtor(int page, int pc, int proc, int maxPC) {
  int futurePage = page+2;
  if (((futurePage-1) * PAGESIZE) > maxPC) {
    pagein(proc,0); // Iterator has a restart coming up
  }
  else if ((futurePage * PAGESIZE)-2*PAGESIZE == pc) {
    pagein(proc,futurePage);
  }
}

void pagerAtor2(int page, int prevpc, int pc, int proc, int maxPC) {
  int futurePage = page+2;
  if ((prevpc == 1682) && (pc == 1166)) {
    pageout(proc,13);
    pagein(proc, 12);
  }
  else if ((futurePage * PAGESIZE)-(2*PAGESIZE) == pc) {
    pagein(proc,futurePage);
  }
}

void pageit(Pentry q[MAXPROCESSES]) {
  static int counter = 0;
  static int totCounter = 0;
  //static struct ProgramStruct ProgramStructs[MAXPROCESSES];
  static int initialized = 0;
  static int prevpc[MAXPROCESSES];
  static int programid[MAXPROCESSES];
  static int found[MAXPROCESSES];

  /* Local vars */
  int proc; // supplies the identity of the process in question
  int pc; // Stores the identification of the program counter
  int page; // Supplies the process page
  int oldpage;
  int foundProgram = 9;
  char foundString;


  if (!initialized) {
    for (int i = 0; i < MAXPROCESSES; i++) {
      programid[i] = 9;
      found[i] = 0;
      prevpc[i] = -1;
      pagein(i,0);
      pagein(i,1);
      pagein(i,2);
      pagein(i,3);
      pagein(i,10);
      // Loaded: 0 1 2 3 10
    }
    initialized = 1;
  }
  int maxPC;
  int innerPC;
  /* Trivial paging strategy */
  /* Select first active process */
  for(proc=0; proc<MAXPROCESSES; proc++) {

    /* Is process active? */
    if(q[proc].active) {

      /* Dedicate all work to first active process*/
      pc = q[proc].pc; 		        // program counter for process
      page = pc/PAGESIZE; 		// page the program counter needs
      foundProgram = programid[proc];


      //fprintf(stderr,"Proc: %d; PC: %d; PrevPC: %d; FoundProgram: %d\n",proc,pc,prevpc[proc],foundProgram);

      int ISFOUND = found[proc]; // Whether or not the program has been found

      if (foundProgram == 9) {
        foundProgram = programChecker(prevpc[proc],pc);

        programid[proc] = foundProgram;
      }
      foundString = programid[proc] + '0';

      //fprintf(stderr, "Process: %d; PC: %d; PrevPC: %d; Page: %d; Program: %c\n",proc,pc,prevpc,page,foundString);
      /*counter++;
      if (counter == 100) {
        getchar();
        counter = 0;
      }*/

      // If the processes program has yet to be found
      // NOTE OWEN REMEMBER TO SET ISFOUND TO TRUE AT SOME POINT

      // ---------Section Covers Paging Before Determining Programs------------
      // Covers Program 0 pt 1, Program 1, Program 2, and Program 3
      // Program 0 pt 2 and Program 4 are already found
      if (foundProgram == 3 && prevpc[proc] == 1911 && pc == 0) {
        pagein(proc,0);
        pagein(proc,1);
        pagein(proc,2);
        pagein(proc,3);
        pagein(proc,10);
      }
      if (page >= 4 && (foundProgram == 9 || foundProgram == 3)) {
        if (pageout(proc,1) && pageout(proc,2) && pageout(proc,3)) {
          if (page < 6) {
            pagein(proc,4);
            pagein(proc,5);
            pagein(proc,6);
          }
          // Loaded 0 4 5 6 10
        }
        if (page >= 6) {
          if (pageout(proc,4) && pageout(proc,5)) {
            if (page < 7) {
              pagein(proc,7);
              pagein(proc,8);
            }
          }
          if (page >= 7) {
            if (pageout(proc,6)) {
              if (page < 9) {
                pagein(proc,9);
              }
            }
            if (page >= 9) {
              if (pageout(proc,7) && pageout(proc,8)) {
                if (pc < 1534) {
                  pagein(proc,11);
                }
              }
              if (pc >= 1534) {
                if (pageout(proc,0)) {
                  if (pc < 1683) {
                    pagein(proc,12);
                    pagein(proc,13);
                  }
                }
                if (pc >= 1683) {
                  if (pageout(proc,9) && pageout(proc,10)) {
                    pagein(proc,0);
                    pagein(proc,14);
                  }
                }
              }
            }
          }
        }
      }
      /*
      if (pc == 504 &&  foundProgram == 9) {
        pageout(proc,1);
        pageout(proc,2);
        pagein(proc,4);
        pagein(proc,5);
        // Loaded: 0 3 4 5 10
      }

      // Covers Program 0 pt 1, Program 1, Program 2, and Program 3
      // Program 0 pt 2 and Program 4 are already found
      else if (pc == 512 &&  foundProgram == 9) {
        pageout(proc,3);
        pagein(proc, 6);
        // Loaded: 0 4 5 6 10
      }

      // Covers Programs 0 pt 1, Program 1, Program 2, and Program 3
      // Program 0 pt 2 and Program 4 are already found
      else if (pc == 768 &&  foundProgram == 9) {
        int rv = pageout(proc,4);
        rv = pageout(proc,5);
        rv = pagein(proc,7);
        rv = pagein(proc,8);
        // Loaded: 0 6 7 8 10
      }

      // Covers Programs 0 pt 1, Program 1, Program 2, and Program 3
      // Program 0 pt 2 and Program 4 are already found
      else if (pc == 896 &&  foundProgram == 9) {
        pageout(proc,6);
        pagein(proc,9);
        // Loaded: 0 7 8 9 10
      }

      // Covers Programs 0 pt 1, Program 2, and Program 3
      // Programs 0 pt 2, Program 4, and Program 1 are already found
      else if (pc == 1152 &&  foundProgram == 9) {
        pageout(proc,7);
        pageout(proc,8);
        pagein(proc,11);
        // Loaded: 0 9 10 11
      }

      // Covers Program 2 and Program 3
      // Program 0, Program 4, and Program 1 are already found
      else if (pc == 1534 &&  foundProgram == 9) {
        pageout(proc,0); // Won't need zero for a while
        pagein(proc,12);
        pagein(proc,13);
        // Loaded: 9 10 11 12 13
      }

      // Covers Program 3
      // Program 0, Program 1, Program 2, and Program 4 are already found
      else if (pc == 1683 &&  foundProgram == 9) {
        pageout(proc,9);
        pagein(proc,14);
        // Loaded: 10 11 12 13 14
      }
      // --------------------------------------------------------------------
      */
      /*
      if (foundProgram == 3) {
        //fprintf(stderr,"Found Program\n");
        if (page >= 0 ) {
          if (pageout(proc,14) && pageout(proc,13) && pageout(proc,11) && pageout(proc,12)) {
            if (page < 4) {
              pagein(proc,0);
              pagein(proc,1);
              pagein(proc,2);
              pagein(proc,3);
              pagein(proc,4);
              // Loaded 0 1 2 3 4
              //getchar();
            }
          }
          if (page >= 4) {
            if (pageout(proc,1) && pageout(proc,2) && pageout(proc,3)) {
              if (page < 6) {
                pagein(proc,10);
                pagein(proc,5);
                pagein(proc,6);
              }
              // Loaded 0 4 5 6 10
            }
            if (page >= 6) {
              if (pageout(proc,4) && pageout(proc,5)) {
                if (page < 7) {
                  pagein(proc,7);
                  pagein(proc,8);
                }
              }
              if (page >= 7) {
                if (pageout(proc,6)) {
                  if (page < 9) {
                    pagein(proc,9);
                  }
                }
                if (page >= 9) {
                  if (pageout(proc,7) && pageout(proc,8)) {
                    if (pc < 1534) {
                      pagein(proc,11);
                    }
                  }
                  if (pc >= 1534) {
                    if (pageout(proc,0)) {
                      if (pc < 1683) {
                        pagein(proc,12);
                        pagein(proc,13);
                      }
                    }
                    if (pc >= 1683) {
                      if (pageout(proc,9) && pageout(proc,10)) {
                        pagein(proc,0);
                        pagein(proc,14);
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
      */
      if (foundProgram == 0) {
        if (!ISFOUND) {
          if (prevpc[proc] == 500 && pc == 1402) {
            pageout(proc,3);
            pagein(proc,11);
            // Loaded: 0 1 2 10 11
          }
          else {
            pagein(proc,1);
            // Loaded: 0 1 9 10 11
          }
        }
        else {
          if (pc == 0) {
            if (!pageout(proc,9)) {
              pagein(proc,2);
            }
            pageout(proc,11);
            pagein(proc,3);
            // Loaded: 0 1 2 3 10
          }

          else if (page == 3) {
            pageout(proc,1);
            pageout(proc,2);
            pagein(proc,4);
            pagein(proc,11);
            // Loaded: 0 3 4 10 11
          }

          else if (page == 4) {
            pageout(proc,0);
            pageout(proc,3);
            // Loaded: 4 10 11
            pagein(proc,5);
            pagein(proc,6);
            // Loaded: 4 5 6 10 11
          }

          else if ( page == 6) {
            pageout(proc,4);
            pageout(proc,5);
            pagein(proc,7);
            pagein(proc,8);
            // Loaded: 6 7 8 10 11
          }

          else if (page == 7) {
            pageout(proc,6);
            pagein(proc,9);
            // Loaded: 7 8 9 10 11
          }
          else if (page == 10) {
            pageout(proc,7);
            pageout(proc,8);
            // Loaded: 9 10 11
            pagein(proc,0);
            pagein(proc,1);
          }

        }

      }

      if (foundProgram == 4) {
        if (!ISFOUND) {
          //pageout(proc,10);
          found[proc] = 1;
        }
        // Program 4 requires no pages outside of pages 0-3
        // So we do nothing.

      }
      //
      // if (foundProgram == 3) {
      //   // Program 3 will actually never be discovered by the program
      //   // It will automatically be covered by the final if statement of
      //   // the above section.
      // }

      if (foundProgram == 2) {
        if (pc == 1536) { // If we're getting close to a loop back to zero
          pageout(proc,11);
          pagein(proc,0);
          // Loaded: 0 9 10 12 13
        }
        if (ISFOUND) { // If we already found the program
          if (prevpc[proc] == 1682 && pc == 1166) {
            pageout(proc,0);
            pagein(proc,11);
            // Loaded: 9 10 11 12 13
          }
        }

        if (pc == 0) {
          pageout(proc,9);
          pageout(proc,10);
          pageout(proc,12);
          pageout(proc,13);
          pagein(proc,1);
          pagein(proc,2);
          pagein(proc,3);
          pagein(proc,4);
          // Loaded 0 1 2 3 4
        }
        else if (pc == 512) {
          pageout(proc,0);
          pageout(proc,1);
          pageout(proc,2);
          pageout(proc,3);
          pagein(proc,5);
          pagein(proc,6);
          pagein(proc,7);
          pagein(proc,8);
          // Loaded 4 5 6 7 8
        }
        else if (pc == 1024) {
          pageout(proc,4);
          pageout(proc,5);
          pageout(proc,6);
          pageout(proc,7);
          pagein(proc,9);
          pagein(proc,10);
          pagein(proc,11);
          pagein(proc,12);
          // Loaded 8 9 10 11 12
        }
        else if (pc == 1152) {
          pageout(proc,8);
          pagein(proc,11);
          // Loaded 9 10 11 12 13
        }
        found[proc] = 1;
      }

      if (foundProgram == 1) {
        if (!ISFOUND) {
          pageout(proc,7);
          pageout(proc,8);
          pageout(proc,9);
          pageout(proc,10);
          if (pagein(proc,1) && pagein(proc,2) && pagein(proc,3) && pagein(proc,4)) {
            found[proc] = 1;
            //getchar();
          }
        }
        else if (pc == 0) {
          pageout(proc,6);
          pageout(proc,7);
          pageout(proc,8);
          pagein(proc,1);
          pagein(proc,2);
          pagein(proc,3);
          // Loaded: 0 1 2 3 4
        }

        else if (pc == 512) {
          pageout(proc,1);
          pageout(proc,2);
          pageout(proc,3);
          pagein(proc,5);
          pagein(proc,6);
          pagein(proc,7);
          // Loaded: 0 4 5 6 7
        }
        else if (pc == 768) {
          pageout(proc,5);
          pagein(proc, 8);
          // Loaded: 0 4 6 7 8
        }

      }
      prevpc[proc] = pc;

      /* Is page swaped-out? */
      // If statement checks if the page is in memory
      if(!q[proc].pages[page]) {
        //fprintf(stderr,"Not in memory.\n");
        //getchar();
        /* Try to swap in */
        //Checks if pagein fails
        if(!pagein(proc,page)) {
          //fprintf(stderr,"Page not in memory and not waiting.\n");

          /* If swapping fails, swap out another page */
          // This will loop through pages listed in the process memory space
          for(oldpage=0; oldpage < q[proc].npages; oldpage++) {

            /* Make sure page isn't one I want */
            // Make sure we're not removing the page we want
            if(oldpage != page) {

              /* Try to swap-out */
              if(pageout(proc,oldpage)) {
                /* Break loop once swap-out starts*/
                // This program exits after the first process served
                //break;
              }
            }
          }
        }
      }
      /* Break loop after finding first active process */
      //break;
    } // End - If process active
  } // End - For loop
} // End - Program
