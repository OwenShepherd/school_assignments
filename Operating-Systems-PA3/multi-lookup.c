#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include "multi-lookup.h"
#include "util.h"

#define FNAME_SIZE 50
#define HOSTNAME_SIZE 1025
#define MAX_HOSTNAMES 500
#define MAX_RESOLVERS 10

int main(int argc, char * argv[]) {

  clock_t start,end;

  start = clock();

  int numRequests;
  int numberFiles = argc-3; // Argv contains the prog, output file, and numReq


  sscanf(argv[argc-1],"%d",&numRequests);

  // Have to make some important threads...
  pthread_mutex_t mNames = PTHREAD_MUTEX_INITIALIZER; // Will control name storage
  pthread_mutex_t mFiles[numberFiles]; // Mutex for each input file
  pthread_mutex_t updateRR = PTHREAD_MUTEX_INITIALIZER; // Controls changing what file to handle next
  pthread_mutex_t updateCC = PTHREAD_MUTEX_INITIALIZER; // Controls updating of what files are complete
  pthread_mutex_t mOFile = PTHREAD_MUTEX_INITIALIZER; // Controls updating of the output file
  pthread_mutex_t dns = PTHREAD_MUTEX_INITIALIZER;
  pthread_mutex_t reader = PTHREAD_MUTEX_INITIALIZER;
  pthread_cond_t readReady = PTHREAD_COND_INITIALIZER; // Controls reading of the array
  pthread_cond_t writeReady = PTHREAD_COND_INITIALIZER; // Controls writing of the array
  pthread_t requesters[numRequests]; // Will contain all requester threads
  pthread_t resolvers[MAX_RESOLVERS]; // Will contain all resolver threads
  fileParams fileInfo[numberFiles]; // Will contain info for each file
  resolverParams resolverInfo[MAX_RESOLVERS]; // Will contain info for each resolver

  char currentFile[FNAME_SIZE];

  // Now I want to make a new array of char pointer pointers for round robin
  //char ** fileNames = malloc((argc-1) * sizeof *fileNames);
  char ** sharedArray = malloc(MAX_HOSTNAMES * HOSTNAME_SIZE);

  for (int i =0; i < MAX_HOSTNAMES; i++) {
    sharedArray[i] = malloc(HOSTNAME_SIZE);
  }

  // Initializing the file mutexes
  for (int i = 0; i < (numberFiles); i++) {
    pthread_mutex_init(&mFiles[i],NULL);
  }


  // The upcoming file index
  int upcoming = 0;

  // The upcoming shared array index to write
  int arrIndex = 0;

  int twrite = 0;
  int tread = 0;

  // Boolean that tracks whether or not all files have been read
  bool AREAD = false;

  // Boolean array that tracks the progress on each file
  bool finishedFiles[numberFiles];



  // I need to progogate the file params stuff
  for (int i = 0; i < (numberFiles); i++) {
    fileInfo[i].file = argv[i+1];
    fileInfo[i].index = i;
    fileInfo[i].nextFile = &upcoming;
    fileInfo[i].nextArray = &arrIndex;
    //fileInfo[i].lastLine = -1; // Last line just tells us what word was last read
    fileInfo[i].numFiles = numberFiles;
    fileInfo[i].mutex_file = &(mFiles[i]);
    fileInfo[i].mutex_index = &updateRR;
    fileInfo[i].mutex_array = &mNames;
    fileInfo[i].array = sharedArray;
    fileInfo[i].ffinished = finishedFiles;
    fileInfo[i].mutex_comp = &updateCC;
    fileInfo[i].cond_read = &readReady;

    // Creating a shared file stream
    fileInfo[i].inFile = NULL;
    fileInfo[i].inFile = fopen(fileInfo[i].file,"w");
    fileInfo[i].timesWritten = &twrite;
  }

  FILE * outputFile = NULL;
  outputFile = fopen(argv[argc-2],"w");

  // Now I want to propogate the resolverParams stuff
  for (int i = 0; i < MAX_RESOLVERS; i++) {
    resolverInfo[i].nextArray = &arrIndex; // We want to pull items from one less of this index
    resolverInfo[i].ffinished = finishedFiles; // Array of bools
    resolverInfo[i].outFile = argv[argc-2]; // CHANGE THIS
    resolverInfo[i].array = sharedArray;
    resolverInfo[i].numFiles = numberFiles;
    resolverInfo[i].mutex_array = &mNames;
    resolverInfo[i].mutex_output = &mOFile;
    resolverInfo[i].mutex_comp = &updateCC;
    resolverInfo[i].cond_read = &readReady;
    resolverInfo[i].mutex_dns = &dns;
    resolverInfo[i].oFile = outputFile;//fopen(resolverInfo[i].outFile,"a");
    resolverInfo[i].READ = &AREAD;
    resolverInfo[i].mutex_reader = &reader;
    resolverInfo[i].timesRead = &tread;
  }



  int success[numRequests];

  // Now I need to loop through each of the requester threads
  for (int i = 0; i < (numRequests); i++) {
    success[i] = pthread_create(&(requesters[i]), NULL, robinRequester, fileInfo);
  }



  for (int i = 0; i < MAX_RESOLVERS; i++) {
    pthread_create(&(resolvers[i]), NULL, dnsResolve, &(resolverInfo[i]));
  }


  //printf("First file name: %s\n",onlyFiles[1]);

  // Here I think I get it down on passing a pointer to an array of fileParams
  //fileParams theFiles[numberFiles];

  //currentFile = *argv[0];

  // Note: before passing a fileParams object, be sure to set lastLine to -1
  //int success = pthread_create(&(requesters[i]), NULL, readNameFile, (void *)currentFile);


  for(int i=0; i<(numRequests); i++){
	   int success = pthread_join(requesters[i], NULL);
  }
pthread_mutex_lock(&reader);
  AREAD = true;
pthread_mutex_unlock(&reader);

  for (int i = 0; i < MAX_RESOLVERS; i++) {
    int success = pthread_join(resolvers[i], NULL);
  }


  for (int i = 0; i < MAX_HOSTNAMES; i++) {
    printf("%s",sharedArray[i]);
  }

fclose(outputFile);



/*
  for (int i = 0; i < MAX_HOSTNAMES; i++) {

    free(sharedArray[i]);
  }
  free(sharedArray);
*/
  end = clock();

  printf("\nTime Elapsed: %d\n",(int)end-start);
  printf("\nTimes Written: %d\n",twrite);
  printf("Times Read: %d\n",tread);

}


// ----------------- Helper Function Definitions ----------------------
// Resolver function handler
void * dnsResolve(void * arg) {
  resolverParams* currResolve = (resolverParams*) arg;

  // Must create a buffer for the hostname
  char hostname[HOSTNAME_SIZE];

  // Must keep track of what array index to write next
  int arrayRead;

  bool allRead;




  while (true) {

    pthread_mutex_lock(currResolve->mutex_array);
    pthread_mutex_lock(currResolve->mutex_reader);
    allRead = currResolve->READ;
    pthread_mutex_unlock(currResolve->mutex_reader);
    arrayRead = (*(currResolve->nextArray));
    // Need to check if the array is empty, and if so, if the requesters are done reading
    while (arrayRead == 0) {
      if (allRead) {
        pthread_mutex_unlock(currResolve->mutex_array);
        return NULL;
      }
      else {
        pthread_cond_wait(currResolve->cond_read,currResolve->mutex_array);
      }

      pthread_mutex_lock(currResolve->mutex_reader);
      allRead = currResolve->READ;
      pthread_mutex_unlock(currResolve->mutex_reader);

      // After waiting, we're going to check the current array read again
      arrayRead = *(currResolve->nextArray);
    }


    /*
    if (*(currResolve->READ)) {
      pthread_mutex_unlock(currResolve->mutex_array);
      pthread_mutex_unlock(currResolve->mutex_reader);
      return NULL;
    }
    */


    //pthread_mutex_unlock(currResolve->mutex_array);

    // As we are told to read the array, lets read it before letting others
    // unlock it (and also want to decrement the next index to write) and
    // nullify the current index for future writes
    strcpy(hostname, (currResolve->array)[arrayRead-1]);
    for (int i = 0; i < strlen((currResolve->array)[arrayRead-1]); i++) {
      (currResolve->array)[arrayRead-1][i] = '\0';
    }
    (*(currResolve->nextArray))--;
    //hostname[strlen(hostname)-1] = '\0';
    /*
    char * newhost = malloc(strlen(hostname)+1);
    for (int i = 0; i < strlen(hostname); i++) {
      newhost[i] = hostname[i];
    }
    */

    pthread_mutex_unlock(currResolve->mutex_array);



    // Now we want to resolve the domain names
    // creating an ip holder
    char currIP[INET6_ADDRSTRLEN];

    // Getting the domain name
    pthread_mutex_lock(currResolve->mutex_dns);
    int dnsResults = dnslookup(hostname,currIP,INET6_ADDRSTRLEN);
    pthread_mutex_unlock(currResolve->mutex_dns);

    if (dnsResults == UTIL_FAILURE) {
      strcpy(currIP,"");
    }

    // Now we just need to write to the specified file
    pthread_mutex_lock(currResolve->mutex_output);
    //oFile = fopen(currResolve->outFile,"a");
    int fpreturn = fprintf(currResolve->oFile,"%s,%s\n",hostname,currIP);
    (*(currResolve->timesRead))++;
    pthread_mutex_unlock(currResolve->mutex_output);
  }
}



// Requester Function handler
// Had to add new function to handle round-robin stuff
void * robinRequester(void * arg) {

  bool isDone = false;

  // Keeps track of number of files serviced
  int filesServiced;

  // Extracting our array of file params
  fileParams* args = (fileParams *)arg;
  int numFiles = args[0].numFiles;

  bool *completed = malloc(sizeof(*completed) * args[0].numFiles);


  while(!isDone) {


    pthread_mutex_lock(args[0].mutex_comp);
    for (int i =0; i < numFiles; i++) {
      completed[i] = (args[0].ffinished)[i];

    }
    pthread_mutex_unlock(args[0].mutex_comp);


    // Getting what the next file assignment should be
    pthread_mutex_lock(args[0].mutex_index);

    // Checking if there are any files left to read
    isDone = FinishedReading(completed,args[0].numFiles);

    // Grabbing the up-next file index
    int fileIndex = (*(args[0].nextFile));

    // Setting the next file index
    if (!isDone) {
      (*(args[0].nextFile)) = fileSelector(fileIndex, numFiles,completed);

    // Copying the fileParams structure
    fileParams* currParams = &(args[fileIndex]);

    pthread_mutex_unlock(args[0].mutex_index);

    // Now calling the read file with the current fileparams structure
    readNameFile(currParams);
    filesServiced++;
  }

  else {
    pthread_mutex_unlock(args[0].mutex_index);
  }
  }
  free(completed);
  FILE* serviceFile = NULL;
  serviceFile = fopen("serviced.txt","w");
  fprintf(serviceFile,"Thread %d serviced %d files\n",syscall(SYS_gettid),filesServiced);
  fclose(serviceFile);
  return NULL;

}


// Read file function
void readNameFile(fileParams *args) {

  // Now we're going to open the file
  //FILE* inputFile = NULL;
  //inputFile = fopen(args->file, "r");

  // Create an array for reading the file
  char hostname[HOSTNAME_SIZE];

  // Creating a proper buffer for storing
  int hostSize;
  char hostBuff[HOSTNAME_SIZE];
  char localChar = 's';
  char * localp = &localChar;

  // Before doing file checks, want to lock current file mutex
  pthread_mutex_lock(args->mutex_file);
  int r = fscanf(args->inFile,"%s\n",hostname);
  pthread_mutex_unlock(args->mutex_file);

  // Now we're (hopefully) going to read the file
  while (r != EOF) {
    pthread_mutex_lock(args->mutex_file);

    // Check to see if the current line has already been handled
    // Implement adding to a shared array...
    // Need to dynamically create some space for the hostname size

    strcpy(hostBuff, hostname);

    //printf("Adding hostname: %s to shared array by thead: %d.\n",hostBuff,syscall(SYS_gettid));

    // In this event we should update the last line read

    pthread_mutex_lock(args->mutex_array);
    strcpy((args->array)[(*(args->nextArray))], hostBuff);
    (*(args->nextArray))++;
    (*(args->timesWritten))++;
    pthread_mutex_unlock(args->mutex_array);

    pthread_cond_signal(args->cond_read);

    // Unlocking
    r = fscanf(args->inFile,"%s\n",hostname);
    pthread_mutex_unlock(args->mutex_file);


  }

  pthread_mutex_lock(args->mutex_comp);
  args->ffinished[args->index] = true;
  pthread_mutex_unlock(args->mutex_comp);

}


// We have to keep switching the next file in the "round-robin" fashion
// But also don't want to assign
int fileSelector(int index, int numFiles, bool * fArray) {

  index = index + 1;

  /*

  if (index == numFiles) {
    return 0;
  }
  else {
    return index;
  }
  */

  if (index == numFiles) {
    index = 0;
  }

  if (fArray[index]) {
    return fileSelector(index, numFiles, fArray);
  }
  else {
    return index;
  }


}

// Simply sets whether or not all files have been read based on array
bool FinishedReading(bool * fArray, int numFiles) {
  bool alldone = true;

  for (int i = 0; i < numFiles; i++) {
    alldone = alldone && fArray[i];
  }

  return alldone;

}
