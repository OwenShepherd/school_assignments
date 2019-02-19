#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <sys/syscall.h>
#include "multi-lookup.h"
#include "util.c"

#define SIZE 10

#define HOSTNAME_SIZE 1025

int main() {

  char hostname[HOSTNAME_SIZE];
  char fakeInput[HOSTNAME_SIZE];
  char currIP[INET6_ADDRSTRLEN];
  char stupidTest[1][2];
  strcpy(fakeInput,"facebook.com\n");

  strcpy(hostname,fakeInput);

  for (int i = 0; i < strlen(fakeInput); i++) {
    fakeInput[i] = '\0';
  }

  strcpy(stupidTest[0],hostname);


  hostname[strlen(hostname)-1] = '\0';

  dnslookup(hostname,currIP,INET6_ADDRSTRLEN);

  printf("%s\n",currIP);

}
