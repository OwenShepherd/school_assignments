#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define MAX_BUFFER 1024

char queryUser();

void readDevice(char *,int);

void printHeader() {
  printf("\n//-------------------------------------");
  printf("\n//-------------------------------------");
  printf("\n//-------------------------------------\n");
}

void writeDevice(int);

void seekDevice(int);

void closeDevice(int);

int main () {

  char userInput = 'a';
  char userBuff[MAX_BUFFER];

  int fd = open("/dev/simple_char_device", O_RDWR);

  while (userInput != 'e') {
    userInput = queryUser();

    switch (userInput) {
      case 'r':
        readDevice(userBuff, fd);
      break;

      case 'w':
        writeDevice(fd);
      break;

      case 's':
        seekDevice(fd);
      break;
    }
  }

  close(fd);
}


char queryUser() {

  char input[20];

  char uInput = 'q';

  while (!((uInput == 'e') || (uInput == 'r') || (uInput == 'w') || (uInput == 's'))) {
    printf("Device actions:\n");
    printf("\tPress r to read from device.\n");
    printf("\tPress w to write to the device.\n");
    printf("\tPress s to seek into the device.\n");
    printf("\tPress e to exit from the device.\n");
    printf("Enter Command: ");
    fgets(input,20,stdin);
    uInput = input[0];
  }

  return uInput;
}



void readDevice(char * buff, int fd) {

  int ret = read(fd,buff,MAX_BUFFER);

  printf("Data read from the device: %s",buff);
}

void writeDevice(int fd) {

  int inputLength;

  char inputBuff[500];

  printHeader();

  printf("Enter data you want to write to the device: \n");
  fgets(inputBuff,500,stdin);

  inputLength = strlen(inputBuff);

  write(fd, inputBuff, inputLength);
}

void seekDevice(int fd) {

  int offset;
  int whence;

  printHeader();



  printf("Enter an offset value: ");

  scanf("%d",&offset);

  printf("\nEnter a whence value: ");

  scanf("%d",&whence);

  lseek(fd,offset,whence);

}
