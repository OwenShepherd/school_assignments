#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <sys/syscall.h>
typedef int bool;
#define true 1
#define false 0

typedef struct {
  bool * ffinished; // Each index indicates whether that file is finished being read
  int index; // The index of the current file params
  char * file; // The file name
  char ** array; // The shared array
  int * nextFile; // Keeps track of what the next file should be
  int * nextArray; // Keeps track of where to write in the array
  FILE * inFile; // File stream to be shared amongst readers
  //int lastLine; // The last line that was read in the file
  int numFiles; // The number of files
  int * timesWritten;
  pthread_mutex_t * mutex_file; // The mutex for this specific file
  pthread_mutex_t * mutex_index; // The mutex for the file index
  pthread_mutex_t * mutex_array; // the mutex for the shared array
  pthread_mutex_t * mutex_comp; // the mutex for the completed files
  pthread_cond_t * cond_read; // Conditional for reading the array
} fileParams;

typedef struct {
  int * nextArray; // Index to the final position,n, plus one
  bool * READ;
  bool * ffinished; // Indexes indicate whether that file is finished
  char * outFile; // The string that holds the file to write to
  char ** array; // The shared array
  int numFiles; // Number of files
  FILE * oFile;
  int * timesRead;
  pthread_mutex_t * mutex_array; // The mutex for the shared array
  pthread_mutex_t * mutex_output; // The mutex for the output file
  pthread_mutex_t * mutex_comp; // Mutex for setting completed files
  pthread_mutex_t * mutex_dns;
  pthread_mutex_t * mutex_reader;
  pthread_cond_t * cond_read; // Conditional for reading the array
} resolverParams;

void readNameFile(fileParams*);

void * robinRequester(void*);

void * dnsResolve(void*);

int fileSelector(int, int, bool *);

bool FinishedReading(bool*, int);
